// Copyright (C) 2019-2020 star.engine at outlook dot com
//
// This file is part of StarEngine
//
// StarEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// StarEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with StarEngine.  If not, see <https://www.gnu.org/licenses/>.

#include "SAssetFactory.h"
#include <Star/Core/SProducer.h>
#include <Star/Core/SResourceUtils.h>
#include "SAssetTypes.h"
#include "SAssetUtils.h"
#include "SAssetFbxImporter.h"
#include "SAssetTexture.h"
#include <Star/Graphics/SContentSerialization.h>
#include <Star/AssetFactory/SAssetSerialization.h>
#include <StarCompiler/ShaderGraph/SShaderModules.h>
#include <StarCompiler/ShaderGraph/SShaderDatabase.h>
#include <StarCompiler/RenderGraph/SRenderGraphFactory.h>
#include <StarCompiler/ShaderWorks/SShaderAssetBuilder.h>
#include <Star/Graphics/SContentUtils.h>
#include <Star/Graphics/SRenderFormatUtils.h>

namespace Star::Asset {

using namespace Graphics::Render;
using namespace Graphics::Render::Shader;
using std::filesystem::path;

struct AssetFactory::Impl final : public Core::Producer {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept {
        return mResources.get_allocator();
    }
    Impl(const std::filesystem::path& assetPath, const std::filesystem::path& libPath, const allocator_type& alloc)
        : mThreadID(std::this_thread::get_id())
        , mFolder(assetPath)
        , mLibrary(libPath)
        , mResources(alloc)
        , mFlattenedFbx(std::pmr::get_default_resource())
    {
        mResources.mSettings.mVertexLayouts.emplace_back();
        mResources.mSettings.mVertexLayoutIndex.emplace("", 0);

        auto& meshLayout = mResources.mSettings.mVertexLayouts.emplace_back();
        auto& desc = meshLayout.mBuffers.emplace_back();
        desc.mElements = {
            { SV_Position, 0, Format::R32G32B32_SFLOAT },
            { NORMAL, 12, Format::R32G32B32_SFLOAT },
            { TANGENT, 24, Format::R32G32B32A32_SFLOAT },
            { TEXCOORD, 40, Format::R32G32_SFLOAT },
        };
        desc.mVertexSize = 48;
        meshLayout.mIndex = {
            { "vertex", { 0, 0 } },
            { "normal", { 0, 1 } },
            { "tangent", { 0, 2 } },
            { "uv", { 0, 3 } },
        };
        mResources.mSettings.mVertexLayoutIndex.emplace("StaticMesh", 1);
    }
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;
private:
    std::pair<MetaID, bool> try_readAssetMetaID(std::string_view assetPath) const {
        MetaID id{};
        Expects(id.is_nil());
        auto filename = mFolder / (str(assetPath) + ".meta");
        return try_readMetaIDFile(filename);
    }

    std::pair<MetaID, bool> try_createAssetMetaID(std::string_view assetPath) const {
        MetaID metaID{};
        bool hasMetaId = false;
        std::tie(metaID, hasMetaId) = try_readAssetMetaID(assetPath);
        if (hasMetaId) {
            return { metaID, false };
        }
        metaID = safe_generateMetaID();
        Ensures(!metaID.is_nil());
        auto filename = mFolder / (str(assetPath) + ".meta");
        if (!exists(filename.parent_path())) {
            create_directories(filename.parent_path());
        }
        writeMetaIDFile(filename, metaID);
        return { metaID, true };
    }

    template<class T>
    bool updateResource(std::string_view assetName, const T& value, bool create = false) const {
        auto filename = mLibrary / assetName;
        if (create && exists(filename)) {
            return false;
        }

        auto folder = filename.parent_path();
        if (!exists(folder)) {
            create_directories(folder);
        }

        auto content0 = readBinary(filename);
        std::ostringstream oss;
        {
            boost::archive::binary_oarchive oa(oss);
            oa << value;
        }
        auto content = oss.str();
        if (content != content0) {
            std::ofstream ofs(filename, std::ios::binary);
            ofs.exceptions(std::ostream::failbit);
            ofs.write(content.data(), content.size());
            return true;
        }
        return false;
    }

    template<class T>
    bool updateAsset(std::string_view assetName, const char* name, const T& value, bool create = false) const {
        auto filename = mFolder / assetName;
        if (create && exists(filename)) {
            return false;
        }
        if (create) {
            auto folder = filename.parent_path();
            if (!exists(folder)) {
                create_directories(folder);
            }
        }
        auto content0 = readBinary(filename);
        std::ostringstream oss;
        {
            boost::archive::xml_oarchive oa(oss);
            oa << boost::serialization::make_nvp(name, value);
        }
        auto content = oss.str();
        if (content != content0) {
            std::ofstream ofs(filename, std::ios::binary);
            ofs.exceptions(std::ostream::failbit);
            ofs.write(content.data(), content.size());
            return true;
        }
        return false;
    }

    bool updateAsset(std::string_view assetName, const char* name, const ShaderInfo& value, bool create = false) const {
        auto filename = mFolder / assetName;
        if (create && exists(filename)) {
            return false;
        }
        if (create) {
            auto folder = filename.parent_path();
            if (!exists(folder)) {
                create_directories(folder);
            }
        }
        auto content0 = readBinary(filename);
        const auto& content = value.mContent;
        if (content != content0) {
            std::ofstream ofs(filename, std::ios::binary);
            ofs.exceptions(std::ostream::failbit);
            ofs.write(content.data(), content.size());
            return true;
        } else {
            if (create && content.empty()) {
                std::ofstream ofs(filename, std::ios::binary);
                ofs.exceptions(std::ostream::failbit);
                ofs.write(content.data(), content.size());
                return true;
            }
        }
        return false;
    }
    
    bool updateAsset(std::string_view assetName, const char* name, const ContentInfo& value, bool create = false) const {
        auto filename = mFolder / assetName;
        if (create && exists(filename)) {
            return false;
        }

        if (create) {
            auto folder = filename.parent_path();
            if (!exists(folder)) {
                create_directories(folder);
            }
        }

        std::ostringstream oss;
        boost::archive::binary_oarchive oa(oss);
        ContentData data(std::pmr::get_default_resource());
        oa << data;

        const auto& content = oss.str();
        auto content0 = readBinary(filename);

        if (content != content0) {
            std::ofstream ofs(filename, std::ios::binary);
            ofs.exceptions(std::ostream::failbit);
            ofs.write(content.data(), content.size());
            return true;
        } else {
            if (create && content.empty()) {
                std::ofstream ofs(filename, std::ios::binary);
                ofs.exceptions(std::ostream::failbit);
                ofs.write(content.data(), content.size());
                return true;
            }
        }
        return false;
    }

    bool updateAsset(std::string_view assetName, const char* name, const ContentInfo& value, const ContentData& data) const {
        auto filename = mFolder / assetName;

        std::ostringstream oss;
        boost::archive::binary_oarchive oa(oss);
        oa << data;

        const auto& content = oss.str();
        auto content0 = readBinary(filename);

        if (content != content0) {
            std::ofstream ofs(filename, std::ios::binary);
            ofs.exceptions(std::ostream::failbit);
            ofs.write(content.data(), content.size());
            return true;
        }
        return false;
    }

    template<class T>
    bool try_createResourceBinary(std::string_view assetName, const T& value) const {
        return updateResource(assetName, value, true);
    }
private:
    void removeRedundantMetaFiles() const {
        const std::string_view extMeta(".meta");
        for (const auto& p : std::filesystem::recursive_directory_iterator(mFolder)) {
            if (isMeta(p.path().extension())) {
                auto filepath = p.path();
                filepath.replace_extension("");
                if (!exists(filepath)) {
                    remove(p);
                }
            }
        }
    }

    void createMetaFiles() const {
        std::map<std::filesystem::path, std::string> metaFiles;

        for (const auto& p0 : std::filesystem::recursive_directory_iterator(mFolder)) {
            auto p = p0.path();
            if (isAsset(p.extension())) {
                auto metaPath = p;
                metaPath += ".meta";

                auto [metaID, succeeded] = try_readMetaIDFile(metaPath);
                if (succeeded)
                    continue;

                if (metaID.is_nil())
                    metaID = safe_generateMetaID();

                std::ostringstream oss;
                oss << "guid: " << metaID << "\n";
                std::string content = oss.str();
                boost::algorithm::replace_all(content, "-", "");
                metaFiles.emplace(std::move(metaPath), content);
            }
        }

        for (const auto& [path, content] : metaFiles) {
            updateFile(path, content);
        }
    }

    void validateMeta(std::string_view assetPath) const {
        auto metaPath = str(assetPath) + ".meta";
        if (exists(mFolder / metaPath) && !exists(mFolder / assetPath)) {
            throw std::runtime_error("meta found, asset not found: " + str(assetPath));
        }
        if (exists(mFolder / assetPath) && !exists(mFolder / metaPath)) {
            throw std::runtime_error("asset found, meta not found: " + str(assetPath));
        }
    }

    void readAllAssetInfo() {
        std::string_view extMeta(".meta");
        for (const auto& p0 : std::filesystem::recursive_directory_iterator(mFolder)) {
            auto p = std::filesystem::path(boost::algorithm::to_lower_copy(p0.path().string()));
            const auto& ext = p.extension().string();
            if (boost::algorithm::iequals(ext, extMeta)) {
                auto filepath = p;
                filepath.replace_extension("");
                if (!exists(filepath)) {
                    throw std::runtime_error("asset not found: " + filepath.string());
                }

                readAssetInfo(filepath, p);
            }
        }
    }

    template<class Info>
    auto& readExternalAsset(std::string_view assetPath, Info& info) {
        auto [metaID, succeeded] = try_readAssetMetaID(assetPath);
        Ensures(succeeded);
        auto res = info.emplace(metaID, assetPath);
        Ensures(res.second);
        auto res2 = mUnique.emplace(metaID);
        Ensures(res2.second);
        return *res.first;
    }

    template<class Info>
    auto& readAsset(std::string_view assetPath, Info& info) {
        auto [metaID, succeeded] = try_readAssetMetaID(assetPath);
        Ensures(succeeded);

        typename Info::value_type v{};
        {
            std::ifstream ifs(mFolder / assetPath, std::ios::binary);
            ifs.exceptions(std::istream::failbit);
            boost::archive::xml_iarchive ia(ifs);
            ia >> boost::serialization::make_nvp("value", v);
        }
        v.mName = assetPath;
        v.mMetaID = metaID;
        auto res = info.emplace(std::move(v));
        Ensures(res.second);

        auto res2 = mUnique.emplace(metaID);
        Ensures(res2.second);

        return *res.first;
    }

    auto& readAsset(std::string_view assetPath, MetaIDNameIndex<ShaderInfo>& info) {
        auto [metaID, succeeded] = try_readAssetMetaID(assetPath);
        Ensures(succeeded);

        ShaderInfo v{};
        v.mMetaID = metaID;
        v.mName = assetPath;

        {
            auto content = readFile(mFolder / assetPath);
            std::istringstream iss(content);
            std::string line;
            while (std::getline(iss, line)) {
                auto pos = line.find("Shader");
                if (pos != std::string::npos) {
                    auto beg = line.find("\"", pos);
                    Ensures(beg != std::string::npos);
                    beg += 1;
                    auto end = line.find("\"", beg);
                    Ensures(end != std::string::npos);
                    Ensures(end > beg);
                    v.mShaderName = line.substr(beg, end - beg);
                    break;
                }
            }
            v.mContent = content;
        }

        auto res = info.emplace(std::move(v));
        Ensures(res.second);

        auto res2 = mUnique.emplace(metaID);
        Ensures(res2.second);

        return *res.first;
    }

    auto& readAsset(std::string_view assetPath, MetaIDNameIndex<ContentInfo>& info) {
        auto [metaID, succeeded] = try_readAssetMetaID(assetPath);
        Ensures(succeeded);

        ContentInfo v{};
        v.mMetaID = metaID;
        v.mName = assetPath;

        auto res = info.emplace(std::move(v));
        Ensures(res.second);

        auto res2 = mUnique.emplace(metaID);
        Ensures(res2.second);

        {
            auto res3 = mResources.mContents.try_emplace(metaID);
            Ensures(res3.second);

            std::ifstream ifs(mFolder / assetPath, std::ios::binary);
            ifs.exceptions(std::istream::failbit);
            boost::archive::binary_iarchive ia(ifs);
            ia >> res3.first->second;
        }

        return *res.first;
    }

    void readAssetInfo(const std::filesystem::path& file0, const std::filesystem::path& meta) {
        auto ext = file0.extension().string();
        auto name = getAssetNameFromFullPath(file0, mFolder);
        if (boost::algorithm::iequals(ext, ".fbx")) {
            const auto& info = readExternalAsset(name, mDatabase.mFbxInfo);
            AssetFbxImporter importer{};
            auto pScene = importer.read(file0.string());
            AssetFbxScene fbx(std::move(pScene), info.mMetaID, mFolder, file0);
            fbx.readInfo(info, mDatabase.mMeshInfo, mUnique);
        } else if (boost::algorithm::iequals(ext, ".render")) {
            readAsset(name, mDatabase.mRenderGraphInfo);
        } else if (boost::algorithm::iequals(ext, ".content")) {
            readAsset(name, mDatabase.mContentInfo);
        } else if (boost::algorithm::iequals(ext, ".material")) {
            readAsset(name.c_str(), mDatabase.mMaterialInfo);
        } else if (boost::algorithm::iequals(ext, ".shader")) {
            readAsset(name, mDatabase.mShaderInfo);
        } else if (isImage(ext)) {
            readExternalAsset(name, mDatabase.mTextureInfo);
        } else {
            Expects(false);
        }
    }

    template<class Info>
    auto try_createAsset(std::string_view assetPath, const char* name, Info& db) {
        auto [metaID, succeeded] = try_createAssetMetaID(assetPath);
        // if mUnique.emplace failed, factory.scan operation might failed first
        auto res = mUnique.emplace(metaID);
        Ensures(succeeded == res.second);

        auto res1 = db.emplace(metaID, getAssetName(assetPath));
        Ensures(succeeded == res1.second);

        if (succeeded) {
            auto res2 = updateAsset(assetPath, name, *res1.first, true);
            Ensures(res2);
        }

        validateMeta(assetPath);
        return res1;
    }

    template<class Info, class Container>
    std::pair<typename Container::value_type&, bool> try_createResource(std::string_view assetPath, Info& db, Container& resources) {
        auto iter = db.get<Index::Name>().find(assetPath);
        Expects(iter != db.get<Index::Name>().end());

        const auto& metaID = iter->mMetaID;
        auto iter2 = mUnique.find(metaID);
        Expects(iter2 != mUnique.end());

        bool succeeded = false;

        auto iter3 = resources.find(metaID);
        if (iter3 == resources.end()) {
            std::tie(iter3, succeeded) = resources.try_emplace(metaID);
            Ensures(succeeded);
        }
        return { *iter3, succeeded };
    }

    template<class Info, class Resource>
    void clearResource(std::string_view assetPath, const Info& info, Resource& resources) {
        auto iter = info.get<Index::Name>().find(sv(getAssetName(assetPath)));
        Expects(iter != info.get<Index::Name>().end());
        resources.erase(iter->mMetaID);
        resources.try_emplace(iter->mMetaID);
    }

    template<class Info, class Resource>
    const auto& getResource(std::string_view assetPath, const Info& info, const Resource& resources) const {
        auto iter = info.get<Index::Name>().find(sv(getAssetName(assetPath)));
        Expects(iter != info.get<Index::Name>().end());
        return resources.at(iter->mMetaID);
    }

    template<class Info, class Resource>
    auto& getResource(std::string_view assetPath, const Info& info, Resource& resources) {
        auto iter = info.get<Index::Name>().find(sv(getAssetName(assetPath)));
        Expects(iter != info.get<Index::Name>().end());
        return resources.at(iter->mMetaID);
    }

    template<class Info>
    const typename Info::value_type& getAsset2(std::string_view assetPath, const Info& info) const {
        auto iter = info.get<Index::Name>().find(sv(getAssetName(assetPath)));
        Expects(iter != info.get<Index::Name>().end());
        return *iter;
    }

    template<class Info>
    const MetaID& getAssetMetaID(std::string_view assetPath, const Info& info) const {
        auto iter = info.get<Index::Name>().find(sv(getAssetName(assetPath)));
        Expects(iter != info.get<Index::Name>().end());
        return iter->mMetaID;
    }

    void createShaders(const RenderGraphFactory& factory,
        const Shader::AttributeDatabase& attrs, RenderGraphData& rg
    ) {
        const auto& shaderFolder = factory.mFolder;
        if (!exists(mFolder / shaderFolder)) {
            create_directories(mFolder / shaderFolder);
        }
        for (const auto& [prototypeName, prototype] : factory.mShaderDatabase.mPrototypes) {
            if (prototype.mAssetPath.empty()) {
                throw std::invalid_argument("shader path not specified in shader graph");
            }
            auto assetPath = boost::algorithm::to_lower_copy((shaderFolder / prototype.mAssetPath).generic_string());

            ShaderData prototypeData(std::pmr::get_default_resource());
            prototypeData.mName = prototypeName;
            buildShaderData(prototype, mShaderModules, factory.mShaderGroups, attrs, prototypeData, false);

            std::ostringstream oss;
            buildShaderText2(oss, prototypeData);

            auto res = try_createAsset(assetPath, "shader", mDatabase.mShaderInfo);

            auto res2 = mDatabase.mShaderInfo.modify(res.first, [&](ShaderInfo& asset) {
                if (res.second) {
                    asset.mShaderName = prototypeData.mName;
                }
                asset.mContent = oss.str();
            });
            Ensures(res2);
            updateAsset(assetPath, "shader", *res.first);

            auto res3 = try_createResource(assetPath, mDatabase.mShaderInfo, mResources.mShaders);
            Ensures(res3.second);
            auto& prototypeResource = res3.first.second;
            buildShaderData(prototype, mShaderModules, factory.mShaderGroups, attrs, prototypeResource);

            rg.mShaderIndex.emplace(prototypeName, res.first->mMetaID);
        }
    }
public:
    void cleanup() const {
        Expects(std::this_thread::get_id() == mThreadID);
        removeRedundantMetaFiles();
        createMetaFiles();
    }

    void scan() {
        Expects(std::this_thread::get_id() == mThreadID);
        readAllAssetInfo();
    }

    void processAssets() {
        processAllAssets();
    }

    void build() {
        updateResource("settings.star", mResources.mSettings);

        // build shader attributes
        Shader::AttributeDatabase attributes;
        for (const auto& renderGraphInfo : mDatabase.mRenderGraphInfo) {
            const auto& rg = at(mRenderGraphs, renderGraphInfo.mName);
            rg.buildAttributeDatabase(attributes);
        }
        for (const auto& attr : attributes.mAttributes) {
            auto id = attributes.mIndex.size();
            attributes.mIndex.emplace(attr.mName, gsl::narrow<uint32_t>(id));
        }

        // build render graph and shaders
        for (const auto& renderGraphInfo : mDatabase.mRenderGraphInfo) {
            auto& renderGraphData = mResources.mRenderGraphs.at(renderGraphInfo.mMetaID);
            auto& renderSwapChain = renderGraphData.mRenderGraph;
            
            const auto& rg = at(mRenderGraphs, renderGraphInfo.mName);
            createShaders(rg, attributes, renderGraphData);

            renderSwapChain.mNumBackBuffers = 3;

            std::ostringstream oss;
            uint32_t count = 0;
            auto fileRSG = mFolder / renderGraphInfo.mName;
            for (auto& [solutionName, factory] : rg.mSolutionFactories) {
                auto& solutionData = renderSwapChain.mSolutions.at(at(renderSwapChain.mSolutionIndex, solutionName));

                if (count++)
                    oss << "\n";

                factory.build(attributes, solutionName, solutionData, oss);
                fileRSG.replace_extension(".rsg");
                renderSwapChain.mNumReserveFramebuffers = std::max(renderSwapChain.mNumReserveFramebuffers, gsl::narrow<uint32_t>(solutionData.mFramebuffers.size()));
                renderSwapChain.mNumReserveCBV_SRV_UAVs = std::max(renderSwapChain.mNumReserveCBV_SRV_UAVs,
                    gsl::narrow<uint32_t>(solutionData.mCBVs.size() + solutionData.mSRVs.size() + solutionData.mUAVs.size()));
                renderSwapChain.mNumReserveDSVs = std::max(renderSwapChain.mNumReserveDSVs, gsl::narrow<uint32_t>(solutionData.mDSVs.size()));
                renderSwapChain.mNumReserveRTVs = std::max(renderSwapChain.mNumReserveRTVs, gsl::narrow<uint32_t>(solutionData.mRTVs.size()));
            }
            updateFile(fileRSG, oss.str());

            updateResource(renderGraphInfo.mName, mResources.mRenderGraphs.at(renderGraphInfo.mMetaID));
        }

        auto meshFolder = mLibrary / "star_meshes";
        if (!mDatabase.mMeshInfo.empty()) {
            create_directories(meshFolder);
        }
        for (const auto& meshAsset : mDatabase.mMeshInfo) {
            auto iter = mResources.mMeshes.find(meshAsset.mMetaID);
            if (iter == mResources.mMeshes.end()) {
                AssetFbxImporter importer{};
                Expects(meshAsset.mFbx);
                auto fbxPath = meshAsset.mFbx->mName;
                auto filePath = (mFolder / fbxPath).generic_string();
                auto pScene = importer.read(filePath);
                AssetFbxScene fbx(std::move(pScene), meshAsset.mFbx->mMetaID, mFolder, filePath);
                fbx.readMeshes("StaticMesh", mResources);
            }

            std::filesystem::path filename;
            {
                std::ostringstream oss;
                oss << meshAsset.mMetaID << ".mesh";
                filename = meshFolder / oss.str();
            }
            const auto& meshData = mResources.mMeshes.at(meshAsset.mMetaID);
            std::ostringstream oss;
            boost::archive::binary_oarchive oa(oss);
            oa << meshData;
            updateBinary(filename, oss.str());
        }

        std::map<std::string, std::map<std::string, uint32_t>, std::less<>> shaderVertexLayouts;

        for (const auto& contentAsset : mDatabase.mContentInfo) {
            const auto& contentData = mResources.mContents.at(contentAsset.mMetaID);
            updateResource(contentAsset.mName, contentData);

            auto addShader = [this, &shaderVertexLayouts](const MetaID& mesh, const MetaID& material) {
                const auto& materialAsset = at(mDatabase.mMaterialInfo, material);
                const auto& shaderName = materialAsset.mShader;

                if (mesh.is_nil()) {
                    shaderVertexLayouts[shaderName].try_emplace("", mResources.mSettings.mVertexLayoutIndex.at(""));
                } else {
                    const auto& meshData = mResources.mMeshes.at(mesh);

                    auto vertexLayoutID = meshData.mLayoutID;
                    std::string layoutName(sv(meshData.mLayoutName));
                    Expects(!layoutName.empty());
                    Expects(at(mResources.mSettings.mVertexLayoutIndex, sv(layoutName)) == vertexLayoutID);

                    if (layoutName.empty()) {
                        throw std::runtime_error("build shader failed, vertex layout not found");
                    }
                    shaderVertexLayouts[shaderName].try_emplace(layoutName, vertexLayoutID);
                }
            };

            // update shader binding
            for (const auto& dc : contentData.mDrawCalls) {
                addShader(dc.mMesh, dc.mMaterial);
            }
            for (const auto& object : contentData.mFlattenedObjects) {
                for (const auto& renderer : object.mMeshRenderers) {
                    for (const auto& materialID : renderer.mMaterialIDs) {
                        addShader(renderer.mMeshID, materialID);
                    }
                }
            }
        }

        for (const auto& shaderAsset : mDatabase.mShaderInfo) {
            auto shaderIter = mResources.mShaders.find(shaderAsset.mMetaID);
            if (shaderIter == mResources.mShaders.end()) {
                continue;
            }
            auto& shaderData = mResources.mShaders.at(shaderAsset.mMetaID);
            auto iter = shaderVertexLayouts.find(sv(shaderData.mName));
            if (iter != shaderVertexLayouts.end()) {
                auto& layouts = iter->second;
                visitShaderSubpassData(shaderData, [&](ShaderSubpassData& pass) {
                    pass.mVertexLayouts.clear();
                    for (const auto& layout : layouts) {
                        pass.mVertexLayouts.emplace_back(layout.second);
                    }
                });
            }

            updateResource(shaderAsset.mName, shaderData);
        }
                
        for (const auto& materialAsset : mDatabase.mMaterialInfo) {
            MaterialData materialData(std::pmr::get_default_resource());
            materialData.mShader = materialAsset.mShader;
            materialData.mTextures.reserve(materialAsset.mTextures.size());
            for (const auto& texID : materialAsset.mTextures) {
                auto iter = attributes.mIndex.find(texID.first);
                if (iter != attributes.mIndex.end()) {
                    const auto& id = iter->second;
                    materialData.mTextures.emplace(id, texID.second);
                }
            }
            updateResource(materialAsset.mName, materialData);
        }
        TextureImportSettings settings;
        std::for_each(std::execution::par_unseq,
            mDatabase.mTextureInfo.begin(),
            mDatabase.mTextureInfo.end(),
            [this, &settings](const TextureInfo& textureAsset){
                TextureData textureData(std::pmr::get_default_resource());

                std::filesystem::path name(textureAsset.mName);
                if (boost::algorithm::iequals(name.extension().string(), ".png")) {
                    std::ifstream ifs(mFolder / textureAsset.mName, std::ios::binary);
                    ifs.exceptions(std::istream::failbit);
                    loadPNG(ifs, std::pmr::get_default_resource(), settings, textureData);
                } else if (boost::algorithm::iequals(name.extension().string(), ".tga")) {
                    std::ifstream ifs(mFolder / textureAsset.mName, std::ios::binary);
                    ifs.exceptions(std::istream::failbit);
                    loadTGA(ifs, std::pmr::get_default_resource(), settings, textureData);
                }
                if (!textureData.mBuffer.empty()) {
                    std::ostringstream oss;
                    saveDDS(oss, textureData);
                    auto filename = mLibrary / name;
                    filename.replace_extension(".dds");
                    if (!exists(filename.parent_path())) {
                        create_directories(filename.parent_path());
                    }
                    updateBinary(filename, oss.str());
                }
            }
        );
    }

    void processAllAssets() {
        std::string_view extMeta(".meta");
        for (const auto& p0 : std::filesystem::recursive_directory_iterator(mFolder)) {
            auto p = std::filesystem::path(boost::algorithm::to_lower_copy(p0.path().string()));
            const auto& ext = p.extension().string();
            if (boost::algorithm::iequals(ext, extMeta)) {
                auto filepath = p;
                filepath.replace_extension("");
                if (!exists(filepath)) {
                    continue;
                }
                auto name = getAssetNameFromFullPath(filepath, mFolder);
                processAsset(name, filepath.extension().string());
            }
        }
    }

    void processAsset(std::string_view assetPath, std::string_view ext) {
        Expects(std::this_thread::get_id() == mThreadID);
        std::string_view extMeta(".meta");
        std::string_view extFbx(".fbx");
        std::string_view extJPG(".jpg");
        std::string_view extPNG(".png");
        std::string_view extTGA(".tga");
        std::string_view extEXR(".exr");

        if (boost::algorithm::iequals(ext, extFbx)) {
            auto [metaID, succeeded] = try_readAssetMetaID(assetPath);
            Expects(succeeded);
            AssetFbxImporter importer{};
            auto filename = (mFolder / assetPath).string();
            auto pScene = importer.read(filename);
            AssetFbxScene fbx(std::move(pScene), metaID, mFolder, filename);
            fbx.createMaterials([&](std::string_view materialName, const Map<std::string, std::string>& textures) {
                auto res = try_createAsset(materialName, "material", mDatabase.mMaterialInfo);
                if (res.second) {
                    std::ostringstream oss;
                    oss << "create material: " << materialName << ", textures: ";
                    for (const auto& tex : textures) {
                        oss << tex.second << " ";
                    }
                    S_INFO << oss.str();

                    auto metaID = res.first->mMetaID;
                    auto name = res.first->mName;
                    auto res2 = mDatabase.mMaterialInfo.modify(res.first, [&](MaterialInfo& asset) {
                        bool normalMap = false;
                        bool alphaTest = false;
                        asset.mTextures.clear();
                        for (const auto& [attr, texturePath] : textures) {
                            const auto& texMetaID = getAssetMetaID(texturePath, mDatabase.mTextureInfo);
                            asset.mTextures.emplace(attr, texMetaID);
                            if (boost::algorithm::contains(texturePath, "normal")) {
                                normalMap = true;
                            }
                            if (boost::algorithm::contains(texturePath, "albedo") ||
                                boost::algorithm::contains(texturePath, "diffuse") ||
                                boost::algorithm::contains(texturePath, "basecolor"))
                            {
                                if (std::filesystem::path(texturePath).extension() == ".png") {
                                    std::ifstream ifs(mFolder / texturePath, std::ios::binary);
                                    Expects(ifs);
                                    if (isAlphaTestPNG(ifs)) {
                                        alphaTest = true;
                                    }
                                }
                            }
                        }
                        asset.mShader = "Star/Diffuse";
                        if (normalMap) {
                            asset.mShader += " NormalMap";
                        }
                        if (alphaTest) {
                            asset.mShader += " AlphaTest";
                        }

                        S_INFO << "Shader: " << asset.mShader;
                    });
                    Ensures(res2);
                    Ensures(res.first->mMetaID == metaID);
                    Ensures(res.first->mName == name);
                    updateAsset(materialName, "material", *res.first);
                }
            });
        } else if (boost::algorithm::iequals(ext, extPNG)
            || boost::algorithm::iequals(ext, extTGA)
            || boost::algorithm::iequals(ext, extJPG))
        {
        }
    }

    void registerProducers() {
        Expects(std::this_thread::get_id() == mThreadID);
        registerProducer(Core::Mesh);
        registerProducer(Core::Texture);
        registerProducer(Core::Shader);
        registerProducer(Core::Material);
        registerProducer(Core::Content);
        registerProducer(Core::RenderGraph);
    }

    template<class Info, class Resources>
    auto load(const MetaID& metaID, const Info& info, Resources& resources) {
        Expects(std::this_thread::get_id() == mThreadID);
        auto iter = resources.find(metaID);
        if (iter != resources.end()) {
            return &iter->second;
        }
        Expects(iter == resources.end());
        auto iterInfo = info.find(metaID);
        Expects(iterInfo != info.end());
        auto filePath = mLibrary / iterInfo->mName;
        std::ifstream ifs(filePath, std::ios::binary);
        PmrBinaryInArchive ia(ifs, mResources.get_allocator().resource());
        auto res = resources.try_emplace(metaID);
        Ensures(res.second);
        iter = res.first;
        ia >> iter->second;
        return &iter->second;
    }

    bool load(const Core::Resource& resource, bool async) override {
        if (mTaskCount >= mMaxTaskCount)
            return false;

        const auto& metaID = getMetaID(resource);
        const auto& tag = getTag(resource);

        ++mTaskCount;
        ++mResourceCount;

        visit(overload(
            [&](Core::Mesh_) {
                Expects(!async);
                auto ptr = load(metaID, mDatabase.mMeshInfo, mResources.mMeshes);
                deliver(resource, ptr, async);
            },
            [&](Core::Texture_) {
                const auto& info = mDatabase.mTextureInfo;
                auto& resources = mResources.mTextures;

                Expects(std::this_thread::get_id() == mThreadID);
                auto iter = resources.find(metaID);

                Expects(iter == resources.end());
                auto iterInfo = info.find(metaID);
                Expects(iterInfo != info.end());
                auto filePath = mLibrary / iterInfo->mName;
                filePath.replace_extension(".dds");
                std::ifstream ifs(filePath, std::ios::binary);
                auto res = resources.try_emplace(metaID);
                Ensures(res.second);
                iter = res.first;
                bool bSrgb = true;
                if (boost::algorithm::contains(iterInfo->mName, "normal")) {
                    bSrgb = false;
                }
                loadDDS(ifs, std::pmr::get_default_resource(), iter->second, bSrgb);
                auto ptr = &iter->second;
                deliver(resource, ptr, async);
                S_WARNING << filePath << " loaded";
            },
            [&](Core::Shader_) {
                Expects(!async);
                auto ptr = load(metaID, mDatabase.mShaderInfo, mResources.mShaders);
                deliver(resource, ptr, async);
            },
            [&](Core::Material_) {
                Expects(!async);
                auto ptr = load(metaID, mDatabase.mMaterialInfo, mResources.mMaterials);
                deliver(resource, ptr, async);
            },
            [&](Core::Content_) {
                Expects(!async);
                auto ptr = load(metaID, mDatabase.mContentInfo, mResources.mContents);
                deliver(resource, ptr, async);
            },
            [&](Core::RenderGraph_) {
                Expects(!async);
                auto ptr = load(metaID, mDatabase.mRenderGraphInfo, mResources.mRenderGraphs);
                deliver(resource, ptr, async);
            }
        ), tag);
        return true;
    }

    void created(const Core::Resource& resource) override {
        Expects(std::this_thread::get_id() == mThreadID);
        --mTaskCount;
    }

    void destroy(const Core::Resource& resource) noexcept override {
        Expects(std::this_thread::get_id() == mThreadID);
        --mResourceCount;
        // lazy deletion
        // TODO: add destroy
    }

    bool try_createMaterial(std::string_view assetPath, std::string_view shaderName) {
        auto res = try_createAsset(assetPath, "material", mDatabase.mMaterialInfo);
        if (res.second) {
            auto res2 = mDatabase.mMaterialInfo.modify(res.first, [&](MaterialInfo& asset) {
                asset.mShader = shaderName;
            });
            Ensures(res2);
            res2 = updateAsset(assetPath, "material", *res.first);
            Ensures(res2);
        } else {
            if (res.first->mShader != shaderName) {
                throw std::invalid_argument("create material failed, shader inconsistent: " + str(shaderName));
            }
        }
        return res.second;
    }

    std::pair<std::pair<const MetaID, Graphics::Render::ContentData>&, bool>
        try_createContent(std::string_view assetPath)
    {
        auto res = try_createAsset(assetPath, "content", mDatabase.mContentInfo);
        auto res2 = mResources.mContents.try_emplace(res.first->mMetaID);
        if (res.second) {
            Ensures(res2.second);
        }
        return { *res2.first, res2.second };
    }

    FlattenedObjects& contentInstantiateFlattenedObjects(std::string_view contentPath, std::string_view fbxPath) {
        auto& content = getResource(contentPath, mDatabase.mContentInfo, mResources.mContents);
        MetaID fbxID{};
        {
            auto iter = mDatabase.mFbxInfo.get<Index::Name>().find(sv(getAssetName(fbxPath)));
            Expects(iter != mDatabase.mFbxInfo.get<Index::Name>().end());
            fbxID = iter->mMetaID;
        }
        Ensures(!fbxID.is_nil());
        auto iter = mFlattenedFbx.find(fbxID);
        if (iter == mFlattenedFbx.end()) {
            AssetFbxImporter importer{};
            auto filePath = (mFolder / fbxPath).string();
            auto pScene = importer.read(filePath);
            AssetFbxScene fbx(std::move(pScene), fbxID, mFolder, filePath);
            auto res = mFlattenedFbx.try_emplace(fbxID);
            Ensures(res.second);
            iter = res.first;
            fbx.readFlattenedNodes(mDatabase.mMeshInfo, iter->second);
        }
        content.mIDs.emplace_back(ContentID{ { ObjectBatch }, gsl::narrow<uint16_t>(content.mFlattenedObjects.size()) });
        auto& objects = content.mFlattenedObjects.emplace_back();
        objects = iter->second;
        return objects;
    }

    void contentAddFullscreenTriangle(std::string_view contentPath, std::string_view materialPath) {
        auto& content = getResource(contentPath, mDatabase.mContentInfo, mResources.mContents);
        MetaID materialID{};
        {
            auto iter = mDatabase.mMaterialInfo.get<Index::Name>().find(sv(getAssetName(materialPath)));
            Expects(iter != mDatabase.mMaterialInfo.get<Index::Name>().end());
            materialID = iter->mMetaID;
        }
        Ensures(!materialID.is_nil());
        
        content.mIDs.emplace_back(ContentID{ { DrawCall }, gsl::narrow<uint16_t>(content.mDrawCalls.size()) });
        auto& dc = content.mDrawCalls.emplace_back();
        dc.mType = FullScreenTriangle;
        dc.mMesh = {};
        dc.mMaterial = materialID;
        dc.mInstanceSize = 0;
        dc.mInstanceCount = 1;
    }

    void clearContent(std::string_view contentPath) {
        clearResource(contentPath, mDatabase.mContentInfo, mResources.mContents);
    }

    void saveContent(std::string_view assetPath) const {
        auto iter = mDatabase.mContentInfo.get<Index::Name>().find(sv(getAssetName(assetPath)));
        Expects(iter != mDatabase.mContentInfo.get<Index::Name>().end());
        const auto& content = mResources.mContents.at(iter->mMetaID);
        
        updateAsset(assetPath, "content", *iter, content);
    }

    bool try_createRenderGraph(std::string_view assetPath, std::string_view name, uint32_t width, uint32_t height) {
        auto res = try_createAsset(assetPath, "render", mDatabase.mRenderGraphInfo);
        if (res.second) {
            auto res2 = mDatabase.mRenderGraphInfo.modify(res.first, [&](RenderGraphInfo& asset) {
                asset.mRenderGraphName = name;
                asset.mWidth = width;
                asset.mHeight = height;
            });
            Ensures(res2);
            res2 = updateAsset(assetPath, "render", *res.first);
            Ensures(res2);
        }
        return res.second;
    }

    void editRenderGraph(std::string_view assetPath0, std::string_view shaderFolder) {
        auto assetPath = getAssetName(assetPath0);
        auto res1 = mRenderGraphs.try_emplace(assetPath, RenderGraphFactory{ mShaderModules, shaderFolder });
        Ensures(res1.second);

        clearResource(assetPath, mDatabase.mRenderGraphInfo, mResources.mRenderGraphs);
        {
            auto& asset = getAsset2(assetPath, mDatabase.mRenderGraphInfo);
            auto& rg = getResource(assetPath, mDatabase.mRenderGraphInfo, mResources.mRenderGraphs);
            rg.mRenderGraph.mName = asset.mRenderGraphName;
            rg.mRenderGraph.mWidth = asset.mWidth;
            rg.mRenderGraph.mHeight = asset.mHeight;
        }
    }

    std::pair<Graphics::Render::RenderSolutionFactory&, bool> try_createRenderSolution(
        std::string_view renderGraph, std::string_view solution
    ) {
        auto& rg = at(mRenderGraphs, getAssetName(renderGraph));
        auto res = rg.mSolutionFactories.try_emplace(str(solution), str(solution));
        return { res.first->second, res.second };
    }

    ShaderDatabase& setupRenderGraph(std::string_view renderGraph) {
        auto name = getAssetName(renderGraph);
        auto& rg = at(mRenderGraphs, name);
        rg.buildShaderGroupFromSolutions();
        return rg.mShaderDatabase;
    }

    void addContent(std::string_view contentPath, std::string_view renderGraphPath,
        std::string_view solutionName, std::string_view pipelineName, std::string_view passName
    ) {
        const auto& contentID = getAssetMetaID(contentPath, mDatabase.mContentInfo);
        auto& renderGraph = getResource(renderGraphPath, mDatabase.mRenderGraphInfo, mResources.mRenderGraphs).mRenderGraph;
        auto& solution = renderGraph.mSolutions.at(at(renderGraph.mSolutionIndex, solutionName));
        auto& pipeline = solution.mPipelines.at(at(solution.mPipelineIndex, pipelineName));
        const auto& passDesc = at(pipeline.mSubpassIndex, passName);
        auto& pass = pipeline.mPasses.at(passDesc.mPassID);
        auto& queue = pass.mGraphicsSubpasses.at(passDesc.mSubpassID).mOrderedRenderQueue.emplace_back();
        queue.mContents.emplace_back(contentID);
    }

    void saveRenderGraph(std::string_view renderGraph) {
        auto& rg = at(mRenderGraphs, getAssetName(renderGraph));
        rg.bindShadersToShaderGroups();
        rg.buildRootSignatureAndDescriptors();
        rg.completeFactories();

        // init render graph data
        auto& renderGraphData = getResource(renderGraph, mDatabase.mRenderGraphInfo, mResources.mRenderGraphs).mRenderGraph;
        rg.buildRenderGraphData(renderGraphData);
    }

    std::thread::id mThreadID = {};

    std::filesystem::path mFolder;
    std::filesystem::path mLibrary;

    std::unordered_set<MetaID> mUnique;
    AssetDatabase mDatabase;
    Resources mResources;

    std::pmr::unordered_map<MetaID, FlattenedObjects> mFlattenedFbx;
    Shader::ShaderModules mShaderModules;
    Map<std::string, RenderGraphFactory> mRenderGraphs;

    int32_t mMaxTaskCount = 4;
    int32_t mTaskCount = 0;
    int64_t mResourceCount = 0;
};

AssetFactory::AssetFactory(std::string_view assetPath, std::string_view libPath, const allocator_type& alloc)
    : mImpl(pmr_make_unique<Impl>(alloc.resource(), assetPath, libPath))
{
}

AssetFactory::allocator_type AssetFactory::get_allocator() const noexcept {
    return allocator_type(mImpl.get_deleter().resource());
}

AssetFactory::~AssetFactory() = default;

void AssetFactory::scan() {
    mImpl->scan();
}

void AssetFactory::cleanup() const {
    mImpl->cleanup();
}

void AssetFactory::processAssets() {
    mImpl->processAssets();
}

void AssetFactory::registerProducers() {
    mImpl->registerProducers();
}

Shader::ShaderModules& AssetFactory::getShaderModules() {
    return mImpl->mShaderModules;
}

const Shader::ShaderModules& AssetFactory::getShaderModules() const {
    return mImpl->mShaderModules;
}

bool AssetFactory::try_createRenderGraph(std::string_view assetPath, std::string_view name, uint32_t width, uint32_t height) {
    return mImpl->try_createRenderGraph(assetPath, name, width, height);
}

void AssetFactory::editRenderGraph(std::string_view assetPath, std::string_view shaderFolder) {
    mImpl->editRenderGraph(assetPath, shaderFolder);
}

std::pair<Graphics::Render::RenderSolutionFactory&, bool> AssetFactory::try_createRenderSolution(
    std::string_view renderGraph, std::string_view solution
) {
    return mImpl->try_createRenderSolution(renderGraph, solution);
}

ShaderDatabase& AssetFactory::setupRenderGraph(std::string_view assetPath) {
    return mImpl->setupRenderGraph(assetPath);
}

void AssetFactory::addContent(std::string_view contentPath, std::string_view renderGraphPath,
    std::string_view solution, std::string_view pipeline, std::string_view pass
) {
    mImpl->addContent(contentPath, renderGraphPath, solution, pipeline, pass);
}

void AssetFactory::saveRenderGraph(std::string_view renderGraph) {
    mImpl->saveRenderGraph(renderGraph);
}

void AssetFactory::build() const {
    mImpl->build();
}

bool AssetFactory::try_createMaterial(std::string_view material, std::string_view shaderName) {
    return mImpl->try_createMaterial(material, shaderName);
}

std::pair<std::pair<const MetaID, Graphics::Render::ContentData>&, bool> AssetFactory::try_createContent(std::string_view assetPath) {
    return mImpl->try_createContent(assetPath);
}

void AssetFactory::clearContent(std::string_view content) {
    mImpl->clearContent(content);
}

void AssetFactory::saveContent(std::string_view content) {
    mImpl->saveContent(content);
}

FlattenedObjects& AssetFactory::contentInstantiateFlattenedObjects(std::string_view content, std::string_view fbx) {
    return mImpl->contentInstantiateFlattenedObjects(content, fbx);
}

void AssetFactory::contentAddFullscreenTriangle(std::string_view content, std::string_view material) {
    return mImpl->contentAddFullscreenTriangle(content, material);
}

}

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

#pragma once
#include <Star/SFileUtils.h>

namespace Star::Asset {

inline std::string getAssetNameFromFullPath(const std::filesystem::path& filename,
    const std::filesystem::path& folder
) {
    return boost::algorithm::to_lower_copy(relative(filename, folder).generic_u8string());
}

inline void getAssetNameFromFullPath(const std::filesystem::path& filename,
    const std::filesystem::path& folder, std::pmr::string& name
) {
    name = relative(filename, folder).generic_string<char>(name.get_allocator());
    boost::algorithm::to_lower(name);
}

inline std::string getAssetName(const std::filesystem::path& assetPath) {
    return boost::algorithm::to_lower_copy(assetPath.generic_u8string());
}

inline std::string getAssetName(std::string_view assetPath) {
    return boost::algorithm::to_lower_copy(std::filesystem::path(assetPath).generic_u8string());
}

inline void getAssetName(std::string_view assetPath, std::pmr::string& name) {
    name = boost::algorithm::to_lower_copy(std::filesystem::path(assetPath).generic_u8string());
}

inline bool isAsset(std::string_view ext) {
    constexpr std::string_view extensions[] = {
        ".fbx",
        ".jpg",
        ".png",
        ".tga",
        ".exr",
        ".shader",
        ".material",
        ".render",
        ".content",
    };

    for (const auto& type : extensions) {
        if (boost::algorithm::iequals(ext, type))
            return true;
    }

    return false;
}

inline bool isAsset(const std::filesystem::path& ext) {
    constexpr std::wstring_view extensions[] = {
        L".fbx",
        L".jpg",
        L".png",
        L".tga",
        L".exr",
        L".shader",
        L".material",
        L".render",
        L".content",
    };

    for (const auto& type : extensions) {
        if (boost::algorithm::iequals(ext.native(), type))
            return true;
    }

    return false;
}

inline bool isAsset(const std::string& ext) {
    return isAsset(std::string_view(ext));
}

inline bool isImage(std::string_view ext) {
    constexpr std::string_view extensions[] = {
        ".jpg",
        ".png",
        ".tga",
        ".exr",
    };

    for (const auto& type : extensions) {
        if (boost::algorithm::iequals(ext, type))
            return true;
    }

    return false;
}

inline bool isImage(const std::filesystem::path& ext) {
    constexpr std::wstring_view extensions[] = {
        L".jpg",
        L".png",
        L".tga",
        L".exr",
    };

    for (const auto& type : extensions) {
        if (boost::algorithm::iequals(ext.native(), type))
            return true;
    }

    return false;
}

inline bool isImage(const std::string& ext) {
    return isImage(std::string_view(ext));
}

inline bool isMeta(std::string_view ext) {
    if (boost::algorithm::iequals(ext, ".meta"))
        return true;
    return false;
}

inline bool isMeta(const std::filesystem::path& ext) {
    if (boost::algorithm::iequals(ext.native(), L".meta"))
        return true;
    return false;
}

inline std::string getRelativeFilename(std::string_view fbxName, const char* relativePath) {
    return boost::algorithm::to_lower_copy(
        relative(std::filesystem::path(fbxName).parent_path() /
            std::filesystem::u8path(relativePath)).generic_u8string());
}

inline std::string getRelativeFilename(const std::filesystem::path& fbxName, const char* relativePath) {
    return boost::algorithm::to_lower_copy(
        relative(fbxName.parent_path() /
            std::filesystem::u8path(relativePath)).generic_u8string());
}

std::pair<MetaID, bool> try_readMetaIDFile(const std::filesystem::path& filename);
void writeMetaIDFile(const std::filesystem::path& filename, const MetaID& metaID);

}

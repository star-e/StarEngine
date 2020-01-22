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

#include "SAssetFbxImporter.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(mManager->GetIOSettings()))
#endif

using namespace boost;

namespace Star::Asset {

AssetFbxImporter::AssetFbxImporter()
    : mManager(FbxManager::Create())
{
    if (mManager) {
        FbxIOSettings* ios = FbxIOSettings::Create(mManager.get(), IOSROOT);
        mManager->SetIOSettings(ios);
    }
}

FbxPtr<fbxsdk::FbxScene> AssetFbxImporter::read(std::string_view filename) {
    std::string u8path(filename);
    int ec = 0;
    auto pManager = mManager.get();

    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor, lSDKMinor, lSDKRevision;
    //int lFileFormat = -1;
    int i, lAnimStackCount;
    bool lStatus;

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    std::unique_ptr<fbxsdk::FbxImporter, AssetFbxDeleter> lImporter(
        fbxsdk::FbxImporter::Create(pManager, ""));

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(u8path.c_str(), -1, pManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if (!lImportStatus) {      
        ec = lImporter->GetStatus().GetCode();
        FbxString error = lImporter->GetStatus().GetErrorString();
        S_ERROR << "call to fbxsdk::FbxImporter::Initialize() failed.";
        S_ERROR << "error returned: " << error.Buffer();

        if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion) {
            S_ERROR << str(format("FBX file format version for this FBX SDK is %d.%d.%d")
                % lSDKMajor % lSDKMinor % lSDKRevision);
            S_ERROR << str(format("FBX file format version for file '%s' is %d.%d.%d")
                % u8path % lFileMajor % lFileMinor % lFileRevision);
        }
        throw std::invalid_argument("call to fbxsdk::FbxImporter::Initialize() failed.");
    }

    S_INFO << str(format("FBX file format version for this FBX SDK is %d.%d.%d")
        % lSDKMajor % lSDKMinor % lSDKRevision);

    if(lImporter->IsFBX()) {
        S_INFO << str(format("FBX file format version for file '%s' is %d.%d.%d")
            % u8path % lFileMajor % lFileMinor % lFileRevision);

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

        S_INFO << "Animation Stack Information";

        lAnimStackCount = lImporter->GetAnimStackCount();

        S_INFO << str(format("    Number of Animation Stacks: %d") % lAnimStackCount);

        S_INFO << str(format("    Current Animation Stack: \"%s\"") %
            lImporter->GetActiveAnimStackName().Buffer());

        for (i = 0; i < lAnimStackCount; i++) {
            FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

            S_INFO << str(format("    Animation Stack %d") % i);
            S_INFO << str(format("         Name: \"%s\"") % lTakeInfo->mName.Buffer());
            S_INFO << str(format("         Description: \"%s\"") %
                lTakeInfo->mDescription.Buffer());

            // Change the value of the import name if the animation stack should be imported 
            // under a different name.
            S_INFO << str(format("         Import Name: \"%s\"") %
                lTakeInfo->mImportName.Buffer());

            // Set the value of the import state to false if the animation stack should be not
            // be imported. 
            S_INFO << str(format("         Import State: %s") %
                (lTakeInfo->mSelect ? "true" : "false"));
        }

        // Set the import states. By default, the import states are always set to 
        // true. The code below shows how to change these states.
        IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
        IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
        IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
        IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
        IOS_REF.SetBoolProp(IMP_FBX_GOBO, false);
        IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, false);
        IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    }

    // Import the scene.
    FbxPtr<fbxsdk::FbxScene> pScene(FbxScene::Create(mManager.get(), u8path.c_str()));
    lStatus = lImporter->Import(pScene.get());

    //fbxsdk::FbxAxisSystem sceneAxisSystem = pScene->GetGlobalSettings().GetAxisSystem();
    //if (sceneAxisSystem != fbxsdk::FbxAxisSystem::DirectX) {
    //    fbxsdk::FbxAxisSystem::DirectX.ConvertScene(pScene.get());
    //}

    //if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError) {
    //    ec = lImporter->GetStatus().GetCode();
    //    S_ERROR << "failed to read fbx. file has password.";
    //    return ec;
    //}

    return pScene;
}

}

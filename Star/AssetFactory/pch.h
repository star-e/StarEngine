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

#include <Star/PrecompiledHeaders/SCore.h>
#include <Star/PrecompiledHeaders/SCoreRuntime.h>

#include <filesystem>
#include <fstream>
#include <boost/uuid/uuid_io.hpp>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/format.hpp>

#include <boost/serialization/array_wrapper.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/xml_oarchive.hpp>

// fbx
#include <fbxsdk.h>

#include <Star/SFileUtils.h>
#include <Star/Log/SLog.h>
#include <Star/Serialization/SOptional.h>
#include <Star/Serialization/SPmrVector.h>
#include <Star/Serialization/SPmrString.h>
#include <Star/Serialization/SVariant.h>
#include <Star/Serialization/SMath.h>
#include <Star/Serialization/SFlatMap.h>
#include <Star/Serialization/SPmrBinaryInArchive.h>
#include <Star/Serialization/SPmrTextInArchive.h>
#include <Star/Serialization/SPmrXmlInArchive.h>
#include <StarCompiler/RenderGraph/SRenderGraphContainer.h>
#include <Star/AssetFactory/SAssetContainer.h>

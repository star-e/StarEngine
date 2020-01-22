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

// temporary
#include <fstream>

// boost
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/uuid/uuid_io.hpp>

// msvc
#include <D3Dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")
#include <DXGI1_4.h>
#include <d3d12.h>
#include <d3d12sdklayers.h>
#include <3rdparty/d3dx12.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")

// Star
#include <Star/SWinRT.h>
#include <Star/SLocale.h>
#include <Star/SWinThread.h>

#include <Star/Graphics/SRenderFormatDXGI.h>
#include <Star/Serialization/SRuntime.h>
#include <Star/Serialization/SPmrBinaryInArchive.h>
#include <Star/DX12Engine/SDX12Render.h>
#include <Star/DX12Engine/SDX12Helpers.h>
#include <Star/DX12Engine/SDX12DescriptorArray.h>

#include <Star/Graphics/SRenderResource.h>
#include <Star/Core/SFetch.h>
#include <Star/DX12Engine/SDX12InternalFwd.h>

#include <Star/DX12Engine/SDX12Fwd.h>
#include <Star/DX12Engine/SDX12Pointer.h>
#include <Star/DX12Engine/SDX12Types.h>

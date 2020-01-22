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

#include <windows.h>
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
//#include <winrt/Windows.System.h>
//#include <winrt/Windows.UI.Xaml.h>
//#include <winrt/Windows.UI.Xaml.Controls.h>
//#include <winrt/Windows.UI.Xaml.Hosting.h>
//#include <winrt/Windows.UI.Xaml.Media.h>
//#include <Windows.UI.Xaml.Hosting.DesktopWindowXamlSource.h>

#include <Star/PrecompiledHeaders/SCore.h>
#include <Star/PrecompiledHeaders/SCoreRuntime.h>

#include <rxcpp/rx.hpp>

#include <Star/SCoreDump.h>
#include <Star/SWinRT.h>
#include <Star/SWinThread.h>

#include <Star/SLocale.h>
#include <Star/Log/SLog.h>
#include <Star/Log/SLogUtils.h>
#include <Star/SDate.h>
#include <Star/SLocaleUtils.h>

#include <Star/SRxCpp.h>
#include <Star/SScopeExit.h>

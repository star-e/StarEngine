// Copyright (C) 2019 star.engine at outlook dot com
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

#ifdef _MSC_VER
#   ifdef STAR_CORE_STATIC
#       define STAR_CORE_API
#       define STAR_CORE_TEMPLATE
#   else
#       ifdef STAR_CORE_EXPORTS
#           ifdef STAR_CORE_DEF
#               define STAR_CORE_API
#               define STAR_CORE_TEMPLATE
#           else
#               define STAR_CORE_API __declspec(dllexport)
#               define STAR_CORE_TEMPLATE
#           endif
#       else
#           ifdef _LIB
#               define STAR_CORE_API
#               define STAR_CORE_TEMPLATE
#           else
#               define STAR_CORE_API __declspec(dllimport)
#               define STAR_CORE_TEMPLATE extern
#           endif
#       endif
#   endif
#else
#   define STAR_CORE_API   
#   define STAR_CORE_TEMPLATE
#endif

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

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef NOMINMAX
#endif

//------------------------------------------------------------
// C
//------------------------------------------------------------
#include <cstdint>
#include <cstddef>
#define _USE_MATH_DEFINES
#include <cmath>

//------------------------------------------------------------
// C++
//------------------------------------------------------------
#include <type_traits>
#include <array>
#include <tuple>
#include <optional>
#include <variant>

#include <memory>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <functional>
#include <algorithm>

#include <complex>

//------------------------------------------------------------
// boost
//------------------------------------------------------------
// preprocessor
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

// memory
#include <boost/align.hpp>

// iterator
#include <boost/iterator/iterator_facade.hpp>

// container
#include <boost/container/flat_map.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/global_fun.hpp>

// uuid
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_hash.hpp>

// rational
#include <boost/rational.hpp>

//------------------------------------------------------------
// gsl
//------------------------------------------------------------
#include <gsl/pointers>
#include <gsl/gsl_util>
#include <gsl/span>
#include <gsl/gsl_assert>

//------------------------------------------------------------
// Eigen
//------------------------------------------------------------
#include <Eigen/Dense>

//------------------------------------------------------------
// Star
//------------------------------------------------------------
// Debug
#include <Star/SStaticSize.h>

#ifdef _DEBUG
#ifndef STAR_DEV
#define STAR_DEV
#endif
#endif

// Release
#include <Star/SEnum.h>
#include <Star/SAliasCast.h>
#include <Star/SOverload.h>
#include <Star/SMetaID.h>
#include <Star/SString.h>
#include <Star/SSet.h>
#include <Star/SVariant.h>
#include <Star/SAlignedBuffer.h>
#include <Star/SMap.h>
#include <Star/SFlatMap.h>
#include <Star/SMultiIndex.h>
#include <Star/SMultiIndexUtils.h>
#include <Star/SUUID.h>
#include <Star/SMathFwd.h>

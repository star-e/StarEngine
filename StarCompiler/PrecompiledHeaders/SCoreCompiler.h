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
//------------------------------------------------------------
// C
//------------------------------------------------------------
#include <cctype>

//------------------------------------------------------------
// C++
//------------------------------------------------------------
#include <locale>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>

//------------------------------------------------------------
// boost
//------------------------------------------------------------
// string
#include <boost/algorithm/string.hpp>

// container
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/stable_vector.hpp>

// graph
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_graph.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/topological_sort.hpp>

// uuid
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>

// serialization
#include <boost/serialization/array_wrapper.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/string.hpp>

// archive
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

//------------------------------------------------------------
// Star
//------------------------------------------------------------
#include <Star/SFileUtils.h>
#include <Star/SFlatMap.h>
#include <Star/SGraph.h>
#include <Star/Core/SMetaID.h>
#include <StarCompiler/SFormat.h>
#include <StarCompiler/SMultiIndex.h>
#include <StarCompiler/SGetVariantName.h>
#include <StarCompiler/STextUtils.h>
#include <StarCompiler/SIndent.h>
#include <StarCompiler/SConsoleColor.h>

using namespace std::literals::string_literals;

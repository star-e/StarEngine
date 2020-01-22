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

//------------------------------------------------------------
// C++
//------------------------------------------------------------
#include <memory_resource>
#include <execution>
#include <atomic>
#include <chrono>

//------------------------------------------------------------
// boost
//------------------------------------------------------------
// container
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/circular_buffer.hpp>

// graph
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_graph.hpp>

// uuid
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>

// lockfree
#include <boost/lockfree/queue.hpp>

// state machine
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/back/state_machine.hpp>

// geometry
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

// serialization
#include <boost/serialization/array_wrapper.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/map.hpp>

// archive
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// asio
#include <boost/asio.hpp>

//------------------------------------------------------------
// Star
//------------------------------------------------------------
#include <Star/SBitwise.h>
#include <Star/SMemory.h>
#include <Star/SSmallVector.h>
#include <Star/SAtomic.h>
#include <Star/SHash.h>
#include <Star/SGeometry.h>
#include <Star/SSerializationUtils.h>
#include <Star/Core/SMetaID.h>
#include <Star/Graphics/SRenderFormat.h>
#include <Star/Graphics/SRenderTypes.h>

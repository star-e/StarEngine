// Copyright (C) 2019 star.engine@outlook.com
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

namespace Star {

template<class T>
using UnorderedUUIDMap = std::unordered_map<boost::uuids::uuid, T>;

template<class T>
using PmrUnorderedUUIDMap = std::unordered_map<boost::uuids::uuid, T,
    std::hash<boost::uuids::uuid>, std::equal_to<boost::uuids::uuid>,
    std::pmr::polymorphic_allocator<std::pair<const boost::uuids::uuid, T>>
>;

}

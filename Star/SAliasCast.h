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

namespace Star {

template<typename _TargetPtrType, typename _ArgType>
inline _TargetPtrType alias_cast(_ArgType* const ptr) {
    // check argument alignment at runtime in debug builds
    Expects(uintptr_t(ptr) % alignof(_ArgType) == 0);

    using target_type = typename std::remove_pointer<_TargetPtrType>::type;
    static_assert(std::is_pointer<_TargetPtrType>::value && std::is_pod<target_type>::value, "Target type must be a pointer to POD");
    static_assert(std::is_pod<_ArgType>::value, "Argument must point to POD");
    static_assert(std::is_const<_ArgType>::value ? std::is_const<target_type>::value : true, "const argument must be cast to const target type");
    static_assert(alignof(_ArgType) % alignof(target_type) == 0, "Target alignment must be <= source alignment");
    static_assert(sizeof(_ArgType) >= sizeof(target_type), "Target size must be <= source size");

    //reinterpret cast doesn't remove a const qualifier either
    return reinterpret_cast<_TargetPtrType>(ptr);
}

}

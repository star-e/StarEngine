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
#include <Star/SMultiIndex.h>

namespace Star {

namespace Index {
struct Shader {};
}

namespace Asset {
struct ShaderBinding;
}

template<class T>
using MetaIDNameShaderIndex = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<Index::MetaID>,
            boost::multi_index::member<T, MetaID, &T::mMetaID>
        >,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Shader>,
            boost::multi_index::member<T, std::string, &T::mShaderName>,
            std::less<>
        >
    >
>;

}

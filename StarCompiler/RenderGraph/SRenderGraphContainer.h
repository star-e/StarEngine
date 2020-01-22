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
#include <StarCompiler/Graphics/SRenderFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

struct RenderValue;
std::pair<std::string, ResourceDataView> get_key(const RenderValue& v) noexcept;

template<class T>
using ResourceDataViewMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::global_fun<const T&, std::pair<std::string, ResourceDataView>, get_key>
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >
>;

}

}

}

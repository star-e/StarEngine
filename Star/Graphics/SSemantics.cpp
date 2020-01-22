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

#include "SSemantics.h"
#include <boost/preprocessor/stringize.hpp>

namespace Star {

namespace Graphics {

const char* getSemanticName(VertexSemanticEnum e) {
#define RETURN_NAME(NAME) \
case NAME:\
    return BOOST_PP_STRINGIZE(NAME)

    switch(e) {
        RETURN_NAME(POSITION);
        RETURN_NAME(COLOR);
        RETURN_NAME(TANGENT);
        RETURN_NAME(BINORMAL);
        RETURN_NAME(NORMAL);
        RETURN_NAME(TEXCOORD);
        RETURN_NAME(BLENDINDICES);
        RETURN_NAME(BLENDWEIGHT);
    }

    return "";
}

}

}

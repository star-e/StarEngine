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
#include <string>

namespace Star {

inline std::string camelToUnderscore(const std::string& str) {
    std::string out;
    out.reserve(str.size() + str.size() / 2);
    bool prevUpper = false;
    bool prevSpecial = false;
    for (int i = 0; i != str.size(); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z' ||
            str[i] >= 'A' && str[i] <= 'Z')
        {
            if (isupper(str[i])) {
                if (prevUpper == false) {
                    prevUpper = true;
                    if (i != 0 && prevSpecial == false) {
                        out.push_back('_');
                    }
                }
                out.push_back(tolower(str[i]));
            } else {
                prevUpper = false;
                out.push_back(str[i]);
            }
            prevSpecial = false;
        } else {
            prevUpper = false;
            if (str[i] == '_') {
                out.push_back('-');
            } else {
                out.push_back(tolower(str[i]));
            }
            prevSpecial = true;
        }
    }
    return out;
}

inline std::string macroToCamel(const std::string& str, bool keepUnderScore = false) {
    std::string out;
    out.reserve(str.size());
    bool prevUnderscore = true;
    for (int i = 0; i != str.size(); ++i) {
        if (prevUnderscore) {
            if (str[i] != '_') {
                out.push_back(str[i]);
                prevUnderscore = false;
            } else {
                if (keepUnderScore)
                    out.push_back(str[i]);
                prevUnderscore = true;
            }
        } else {
            if (str[i] != '_') {
                out.push_back(tolower(str[i]));
                prevUnderscore = false;
            } else {
                if (keepUnderScore)
                    out.push_back(str[i]);
                prevUnderscore = true;
            }
        }
    }
    return out;
}

}

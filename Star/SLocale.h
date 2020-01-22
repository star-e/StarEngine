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
#include <codecvt>

namespace Star {

inline std::wstring fromUTF8(const std::string& str) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
}

inline std::wstring fromUTF8(const std::string_view& str) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(
        str.data(), str.data() + str.size());
}

inline std::wstring fromUTF8(const char* str) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
}

inline std::string toUTF8(const std::wstring& str) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
}

inline std::string toUTF8(const std::wstring_view& str) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(
        str.data(), str.data() + str.size());
}

inline std::string toUTF8(const wchar_t* str) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
}

}

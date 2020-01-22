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
#include <string>

namespace Star {

class Indent {
public:
    Indent(std::string& indent) : mIndent(&indent) {
        mIndent->append("    ");
    }
    ~Indent() {
        reset();
    }
    Indent(Indent&& rhs) noexcept
        : mIndent(rhs.mIndent) {
        rhs.mIndent = nullptr;
    }
    Indent& operator=(Indent&& rhs) noexcept {
        mIndent = rhs.mIndent;
        rhs.mIndent = nullptr;
    }
    void reset() {
        if (mIndent) {
            mIndent->erase(mIndent->size() - 4);
            mIndent = nullptr;
        }
    }
    std::string* mIndent = nullptr;
};

inline Indent indent(std::string& str) {
    return Indent(str);
}

inline void copyString(std::ostream& os, const std::string& space, const std::string& str) {
    std::istringstream iss(str);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty())
            os << '\n';
        else if (line[0] == '#') {
            os << line << '\n';
        } else {
            os << space << line << '\n';
        }
    }
}

inline void copyString(std::ostream& os, const std::string& space, const std::pmr::string& str) {
    std::basic_istringstream<char, std::char_traits<char>,
        std::pmr::polymorphic_allocator<char>> iss(str);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty())
            os << '\n';
        else if (line[0] == '#') {
            os << line << '\n';
        } else {
            os << space << line << '\n';
        }
    }
}

inline void try_copyString(std::ostream& os, const std::string& space, const std::string& str) {
    if (str.empty())
        return;
    copyString(os, space, str);
}

inline void copyString(std::ostream& os, const std::string& str) {
    std::istringstream iss(str);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty())
            os << '\n';
        else if (line[0] == '#') {
            os << line << '\n';
        } else {
            os << line << '\n';
        }
    }
}

inline void copyString(std::ostream& os, const std::pmr::string& str) {
    std::basic_istringstream<char, std::char_traits<char>,
        std::pmr::polymorphic_allocator<char>> iss(str);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty())
            os << '\n';
        else if (line[0] == '#') {
            os << line << '\n';
        } else {
            os << line << '\n';
        }
    }
}

inline void try_copyString(std::ostream& os, const std::string& str, bool addNewLine = true) {
    if (str.empty())
        return;
    if (addNewLine)
        os << "\n";
    copyString(os, str);
}

}

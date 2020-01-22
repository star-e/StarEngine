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
#include <filesystem>
#include <sstream>
#include <memory>
#include <string>

namespace Star {

inline size_t getFileSize(std::ifstream& ifs) {
    auto pos = ifs.tellg();
    ifs.seekg(0, ifs.end);
    auto sz = ifs.tellg();
    ifs.seekg(pos, ifs.beg);
    return sz;
}

// http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
// Jerry Coffin
inline std::string readFile(const std::filesystem::path& file) {
    std::ifstream ifs(file);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

inline void readFileBuffer(std::string_view file, std::pmr::string& buffer) {
    std::ifstream ifs(file, std::ios::binary);
    ifs.exceptions(std::ifstream::failbit);

    auto sz = getFileSize(ifs);
    buffer.resize(sz);
    ifs.read(buffer.data(), sz);
}

inline void readFileBuffer(std::wstring_view file, std::pmr::string& buffer) {
    std::ifstream ifs(file, std::ios::binary);
    ifs.exceptions(std::ifstream::failbit);

    auto sz = getFileSize(ifs);
    buffer.resize(sz);
    ifs.read(buffer.data(), sz);    
}

inline bool updateFile(const std::filesystem::path& file, std::string_view content) {
    std::string orig = readFile(file);
    if (orig != content) {
        std::ofstream ofs(file);
        ofs.exceptions(std::ostream::failbit);
        ofs << content;
        return true;
    }
    return false;
}

inline bool copyFile(const std::filesystem::path& src, const std::filesystem::path& dst) {
    auto content = readFile(src);
    if (content.empty())
        return false;

    const auto& folder = dst.parent_path();
    if (!exists(folder)) {
        create_directories(folder);
    }
    return updateFile(dst, content);
}

inline std::string readBinary(std::string_view file) {
    std::ifstream ifs(file, std::ios::binary);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

inline void readBinary(std::string_view file, std::pmr::string& buffer) {
    std::ifstream ifs(file, std::ios::binary);
    auto sz = getFileSize(ifs);
    buffer.resize(sz);
    ifs.read(buffer.data(), sz);
}

inline bool updateBinary(std::string_view file, std::string_view content) {
    std::string orig = readBinary(file);
    if (orig != content) {
        std::ofstream ofs(file, std::ios::binary);
        ofs.exceptions(std::ostream::failbit);
        ofs.write(content.data(), content.size());
        return true;
    }
    return false;
}

inline std::string readBinary(const std::filesystem::path& file) {
    std::ifstream ifs(file, std::ios::binary);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

inline void readBinary(const std::filesystem::path& file, std::pmr::string& buffer) {
    std::ifstream ifs(file, std::ios::binary);
    auto sz = getFileSize(ifs);
    buffer.resize(sz);
    ifs.read(buffer.data(), sz);
}

inline bool updateBinary(const std::filesystem::path& file, std::string_view content) {
    std::string orig = readBinary(file);
    if (orig != content) {
        std::ofstream ofs(file, std::ios::binary);
        ofs.exceptions(std::ostream::failbit);
        ofs.write(content.data(), content.size());
        return true;
    }
    return false;
}

}

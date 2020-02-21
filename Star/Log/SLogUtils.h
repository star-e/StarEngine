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
#include <map>
#include <filesystem>

namespace Star {

inline void updateLogFolder(std::string_view foldername, int numMax = 10) {
    using namespace std::filesystem;

    if (!exists(std::filesystem::path(foldername))) {
        create_directories(foldername);
    }

    std::map<file_time_type, path> files;
    
    int count = 0;
    for (auto iter = directory_iterator(foldername); iter != directory_iterator(); ++iter) {
        if (iter->is_regular_file()) {
            files.emplace(std::pair{ iter->last_write_time(), iter->path() });
        }
        
        ++count;
    }

    auto sz = files.size();
    while (!files.empty() && sz) {
        if (sz < numMax)
            break;
        remove(files.begin()->second);
        --sz;
    }
}

}

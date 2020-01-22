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

#include "SAssetUtils.h"

namespace Star::Asset {

namespace {

void readMeta(std::istream& is, MetaID& id) {
    std::string line;
    std::string line2;
    line.reserve(256);
    line2.reserve(256);
    while (std::getline(is, line)) {
        line2 = line;
        auto range = boost::algorithm::find_first(line2, "guid: ");
        if (range.end() == line2.end())
            continue;
        line.clear();
        line.append(&*range.end(), 8);
        line.append("-");
        line.append(&*range.end() + 8, 4);
        line.append("-");
        line.append(&*range.end() + 12, 4);
        line.append("-");
        line.append(&*range.end() + 16, 4);
        line.append("-");
        line.append(&*range.end() + 20, 12);
        std::istringstream iss(line);
        iss.exceptions(std::istream::failbit);
        iss >> id;
        Ensures(!id.is_nil());
        return;
    }
    throw std::invalid_argument("metaID not found in meta file");
}

void writeMeta(std::ostream& os, const MetaID& metaID) {
    Expects(os);
    Expects(!metaID.is_nil());
    os << "guid: ";
    std::ostringstream oss;
    oss << metaID;
    os << boost::algorithm::replace_all_copy(oss.str(), "-", "");
    os << std::endl;
}

}

std::pair<MetaID, bool> try_readMetaIDFile(const std::filesystem::path& filename) {
    MetaID id{};
    Expects(id.is_nil());

    std::ifstream ifs(filename);
    if (ifs) {
        ifs.exceptions(std::istream::failbit);
        readMeta(ifs, id);
        Ensures(!id.is_nil());
        return std::pair{ id, true };
    }
    Ensures(id.is_nil());
    return std::pair{ id, false };
}

void writeMetaIDFile(const std::filesystem::path& filename, const MetaID& metaID) {
    Expects(!exists(filename));
    std::ofstream ofs(filename);
    ofs.exceptions(std::ostream::failbit);
    writeMeta(ofs, metaID);
}

}

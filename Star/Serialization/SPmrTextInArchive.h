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
#include <boost/archive/text_iarchive.hpp>
#include <memory_resource>

namespace Star {

class PmrTextInArchive : public boost::archive::text_iarchive_impl<PmrTextInArchive> {
public:
    PmrTextInArchive(std::istream& is, std::pmr::memory_resource* mr, unsigned int flags = 0)
        : boost::archive::text_iarchive_impl<PmrTextInArchive>(is, flags)
        , mMemoryResource(mr)
    {}

    std::pmr::memory_resource* resource() const noexcept {
        return mMemoryResource;
    }
private:
    std::pmr::memory_resource* mMemoryResource = nullptr;
};

}

BOOST_SERIALIZATION_REGISTER_ARCHIVE(Star::PmrTextInArchive)

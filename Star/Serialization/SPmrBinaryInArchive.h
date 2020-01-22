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
#include <boost/archive/binary_iarchive.hpp>
#include <memory_resource>

namespace Star {

class PmrBinaryInArchive : public boost::archive::binary_iarchive_impl<
    PmrBinaryInArchive, std::istream::char_type, std::istream::traits_type
> {
public:
    PmrBinaryInArchive(std::istream& is, std::pmr::memory_resource* mr, unsigned int flags = 0)
        : boost::archive::binary_iarchive_impl<PmrBinaryInArchive, std::istream::char_type, std::istream::traits_type>(is, flags)
        , mMemoryResource(mr)
    {}

    PmrBinaryInArchive(std::streambuf& bsb, std::pmr::memory_resource* mr, unsigned int flags = 0)
        : boost::archive::binary_iarchive_impl<PmrBinaryInArchive, std::istream::char_type, std::istream::traits_type>(bsb, flags)
        , mMemoryResource(mr)
    {}

    std::pmr::memory_resource* resource() const noexcept {
        return mMemoryResource;
    }

private:
    std::pmr::memory_resource* mMemoryResource = nullptr;
};

}

BOOST_SERIALIZATION_REGISTER_ARCHIVE(Star::PmrBinaryInArchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Star::PmrBinaryInArchive)

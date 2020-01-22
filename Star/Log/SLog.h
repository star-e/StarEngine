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
#include <Star/Log/SConfig.h>
#include <boost/log/trivial.hpp>

namespace Star {
    
void STAR_LOG_API initLogging(
    boost::log::trivial::severity_level level = boost::log::trivial::info, 
    const char* filename  ="");

void STAR_LOG_API exitLogging();

}

//#ifndef _DEBUG

#define S_TRACE BOOST_LOG_TRIVIAL(trace)
#define S_DEBUG BOOST_LOG_TRIVIAL(debug)
#define S_INFO BOOST_LOG_TRIVIAL(info)
#define S_WARNING BOOST_LOG_TRIVIAL(warning)
#define S_ERROR BOOST_LOG_TRIVIAL(error)
#define S_FATAL BOOST_LOG_TRIVIAL(fatal)

//#else
//
//namespace Star {
//struct LogVoid {
//    template<class T>
//    const LogVoid& operator<<(T&& expr) const {
//        return *this;
//    }
//    const LogVoid& operator<<(std::ostream& (*pf)(std::ostream&)) const {
//        return *this; 
//    }
//};
//}
//
//#define S_TRACE      std::cout << std::endl
//#define S_DEBUG      std::cout << std::endl
//#define S_INFO       std::cout << std::endl
//#define S_WARNING    std::cout << std::endl
//#define S_ERROR      std::cout << std::endl
//#define S_FATAL      std::cout << std::endl

//#endif

#define S_ASIO_ERROR(INFO, EC) \
    S_WARNING << INFO << EC.category().name() << ':' << EC.value() \
        << ", " << EC.message();

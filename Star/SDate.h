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

// Copyright (C) 2015-2018 Zhou Zhenglong <zlzhou.sh@outlook.com>
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <ctime>
#include <string>
#include <boost/format.hpp>

namespace Star {
    
inline std::string getDateTimeAscStr() {
    std::string str;
#ifdef _MSC_VER
    __time64_t long_time;
    _time64(&long_time);

    tm newtime;

    if (_localtime64_s(&newtime, &long_time)) {
        return str;
    }

    str.resize(26);
    if (asctime_s(&str[0], 26, &newtime)) {
        str.clear();
    }
    auto pos = str.find('\n');
    str.resize(pos);
#else
    time_t long_time;
    time(&long_time);

    tm newtime;

    newtime = *localtime(&long_time);
    str = asctime(&newtime);
#endif
    return str;
}

inline std::string getDateTimeStr() {
    std::string str;
#ifdef _MSC_VER
    __time64_t long_time;
    _time64(&long_time);

    tm newtime;

    if (_localtime64_s(&newtime, &long_time)) {
        return str;
    }

    str.reserve(18);

    str = boost::str(boost::format("%02d%02d_%02d%02d%02d")
        //% (newtime.tm_year + 1900)
        % (newtime.tm_mon + 1)
        % (newtime.tm_mday)
        % (newtime.tm_hour)
        % (newtime.tm_min)
        % (newtime.tm_sec));
#else
    time_t long_time;
    time(&long_time);
    tm newtime;

    newtime = *localtime(&long_time);

    //if (localtime(&long_time, &newtime)) {
    //    return str;
    //}

    str.reserve(18);

    str = boost::str(boost::format("%02d%02d_%02d%02d%02d")
        //% (newtime.tm_year + 1900)
        % (newtime.tm_mon + 1)
        % (newtime.tm_mday)
        % (newtime.tm_hour)
        % (newtime.tm_min)
        % (newtime.tm_sec));
#endif
    return str;
}

}
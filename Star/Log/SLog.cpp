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

#include "SLog.h"
#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>

#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/debug_output_backend.hpp>

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace Star {

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

//enum Color { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };
//
//struct colorSet {
//    HANDLE hCon;
//    Color col;
//
//    colorSet(HANDLE h, Color c) : hCon(h)
//        , col(c) {
//
//    }
//};
//
//std::basic_ostream< char > &operator << (std::basic_ostream< char > &s, const colorSet &cs) {
//    SetConsoleTextAttribute(cs.hCon, cs.col);
//    return s;
//}
//
//void my_formatter(logging::record_view const& rec, logging::formatting_ostream& strm) {
//    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//    // Finally, put the record message to the stream
//    boost::locale::generator gen;
//    std::locale::global(gen(""));
//
//    boost::locale::date_time now;
//    std::cout.imbue(std::locale());
//
//    std::cout << colorSet(h, BLUE) << boost::locale::as::ftime("%H:%M:%S") << "[" << now << "] ";
//    std::cout << colorSet(h, RED) << rec[expr::smessage] << colorSet(h, GRAY);
//}

void initLogging(boost::log::trivial::severity_level level, const char* filename) {

    boost::log::aux::add_console_log(std::clog, 
        keywords::format =
        (
            expr::stream
                << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S")
                << "] <" << logging::trivial::severity << "> " << expr::smessage
        )
    );

    if (filename && filename != std::string("")) {
        logging::add_file_log(filename, 
            keywords::format =
            (
                expr::stream
                << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S")
                << "] <" << logging::trivial::severity << "> " << expr::smessage
            )
        );
    }

    boost::log::add_common_attributes();

    typedef logging::sinks::synchronous_sink< logging::sinks::debug_output_backend > sink_t;
    boost::shared_ptr< sink_t > sink(new sink_t());
    sink->set_filter(expr::is_debugger_present());
    sink->set_formatter(expr::stream << expr::smessage << "\r\n");

    auto core = logging::core::get();
    core->add_sink(sink);

    core->set_filter(
        logging::trivial::severity >= level
    );
}

void exitLogging() {
    logging::core::get()->remove_all_sinks();
}

}
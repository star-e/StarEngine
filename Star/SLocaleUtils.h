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
#include <clocale>
#include <string>
#include <locale>

namespace Star {

inline constexpr bool checkUnicode() {
#pragma warning(push)
#pragma warning(disable: 4305)
#pragma warning(disable: 4309)
    const char ch = '屰';
#pragma warning(pop)
    //const char u8ch = '屰';
    const wchar_t wch = L'屰';
    static_assert(ch == gsl::narrow_cast<char>(0xB0));
    static_assert(wch == 0x5C70);

    constexpr char b_arr[] = "屰";
    constexpr char u8b_arr[] = u8"屰";
    constexpr wchar_t wbuffer_arr[] = L"屰";

    constexpr std::string_view b(b_arr);
    constexpr std::string_view u8b(u8b_arr);
    constexpr std::wstring_view wbuffer(wbuffer_arr);

    constexpr char b_gt_arr[] = { gsl::narrow_cast<char>(0xE5), gsl::narrow_cast<char>(0xB1), gsl::narrow_cast<char>(0xB0) };
    constexpr char u8b_gt_arr[] = { gsl::narrow_cast<char>(0xE5), gsl::narrow_cast<char>(0xB1), gsl::narrow_cast<char>(0xB0) };
    constexpr wchar_t wbuffer_gt_arr[] = { 0x5C70 };

    constexpr std::string_view b_gt(b_gt_arr, std::size(b_gt_arr));
    constexpr std::string_view u8b_gt(u8b_gt_arr, std::size(u8b_gt_arr));
    constexpr std::wstring_view wbuffer_gt(wbuffer_gt_arr, std::size(wbuffer_gt_arr));

    static_assert(ch == gsl::narrow_cast<char>(0xB0));
    static_assert(wch == 0x5C70);
    Expects(b == b_gt);
    Expects(u8b == u8b_gt);
    Expects(wbuffer == wbuffer_gt);

    bool res = true;
#pragma warning(push)
#pragma warning(disable: 4127)
    if (ch != gsl::narrow_cast<char>(0xB0))
        res = false;

    if (wch != 0x5C70)
        res = false;

    if (b != b_gt)
        res = false;

    if (u8b != u8b_gt)
        res = false;

    if (wbuffer != wbuffer_gt)
        res = false;
#pragma warning(pop)

    return res;
}

inline void initLocale(const char* loc, bool verbose = true) {
    std::string cLocale = std::setlocale(LC_ALL, nullptr); // get default c locale, should be "C"
    
    if(cLocale != "C") {
        throw std::runtime_error("Error! startup locale already set!");
    }

    { // check current locale
        if (verbose) {
            S_INFO << "startup c++ locale: " << std::locale().name();
            S_INFO << "startup c locale: " << std::setlocale(LC_ALL, nullptr);
        }


        // get current system locale by setlocale to "" 
        std::string nativeLocale = std::setlocale(LC_ALL, "");
        if (verbose) {
            S_INFO << "native locale: " << nativeLocale;
        }
        // set back c locale
        std::string cLocale2 = std::setlocale(LC_ALL, cLocale.c_str());
        Expects(cLocale == cLocale2);
    }

    if (verbose) {
        S_INFO << "set c++/c locale to " << loc;
    }
    std::locale globalLocale(std::setlocale(LC_ALL, loc));
    std::locale::global(globalLocale);

    if (verbose) {
        S_INFO << "current c++ locale: " << std::locale().name();
        S_INFO << "current c locale: " << std::setlocale(LC_ALL, nullptr);

        S_INFO << "中文测试";
        S_INFO << u8"utf-8 中文测试";
        S_INFO << toUTF8(L"wchar_t 中文");
        S_INFO << toUTF8(L"wchar_t Français");
        S_INFO << toUTF8(L"wchar_t 한국어");
        S_INFO << toUTF8(L"wchar_t にほんご");
        S_INFO << toUTF8(L"wchar_t Deutsches Wörterbuch");
    }
    wchar_t locale_str[100];
    std::time_t t = std::time(nullptr);
    struct tm timeinfo;
    localtime_s(&timeinfo, &t);
    std::wcsftime(locale_str, 100, L"%A %c", &timeinfo);
    if (verbose) {
        S_INFO << "Date Locale Test: " << toUTF8(locale_str);
    }
}

}

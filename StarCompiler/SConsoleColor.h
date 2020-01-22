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

namespace Star {

namespace Console {

static const int Red = 12;
static const int White = 15;
static const int Green = 10;
static const int Grey = 8;
static const int LightGrey = 7;
static const int Yellow = 14;
static const int Magenta = 13;
static const int Cyan = 11;
static const int DarkGreen = 2;
static const int DarkMagenta = 5;
static const int Blue = 9;
static const int DarkCyan = 3;
static const int DarkYellow = 6;

}

class SetConsoleColor {
public:
    SetConsoleColor(int color)
        : mConsole(GetStdHandle(STD_OUTPUT_HANDLE))
    {
        SetConsoleTextAttribute(mConsole, color);
    }
    SetConsoleColor(const SetConsoleColor&) = delete;
    SetConsoleColor& operator=(const SetConsoleColor&) = delete;
    ~SetConsoleColor() {
        SetConsoleTextAttribute(mConsole, Console::LightGrey);
    }

    HANDLE mConsole;
    int mPrevColor = -1;
};

#define CONSOLE_COLOR(COLOR) \
    SetConsoleColor console(Console::COLOR)

#define CONSOLE_WARNING() {\
    CONSOLE_COLOR(Yellow);\
    std::cout << "[warning]";\
}

}

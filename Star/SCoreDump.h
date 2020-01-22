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
#include <dbghelp.h>
#include <strsafe.h>

namespace Star {

inline int GenerateDump(EXCEPTION_POINTERS* pExceptionPointers) {
    BOOL bMiniDumpSuccessful;
    wchar_t szPath[MAX_PATH];
    wchar_t szFileName[MAX_PATH];
    //const wchar_t* szAppName = L"AppName";
    //const wchar_t* szVersion = L"v1.0";
    //DWORD dwBufferSize = MAX_PATH;
    //std::ignore = dwBufferSize;
    HANDLE hDumpFile;
    SYSTEMTIME stLocalTime;
    MINIDUMP_EXCEPTION_INFORMATION ExpParam;

    GetLocalTime(&stLocalTime);

    StringCchPrintf(szPath, MAX_PATH, L"%s", L"dump");
    CreateDirectory(szPath, NULL);

    StringCchPrintf(szFileName, MAX_PATH, L"%s\\%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
        L"dump", /*szAppName, szVersion,*/
        stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
        stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,
        GetCurrentProcessId(), GetCurrentThreadId());
    hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

    ExpParam.ThreadId = GetCurrentThreadId();
    ExpParam.ExceptionPointers = pExceptionPointers;
    ExpParam.ClientPointers = TRUE;

    bMiniDumpSuccessful = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
        hDumpFile, MiniDumpWithDataSegs, &ExpParam, NULL, NULL);

    return EXCEPTION_EXECUTE_HANDLER;
}

}

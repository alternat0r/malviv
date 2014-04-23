
#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <string.h>
#include <stdio.h>
#include <exception>

using namespace std;

void TerminateProcessName(const char *FileName)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp((const char*)pEntry.szExeFile, FileName) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

int rm_file(const char *FileName)
{
	try
	{
		if ( remove(FileName) != 0 )
		{
#ifdef DEBUG
	OutputDebugString(L"rm_file(): Unable to delete the file.");
#endif
		} else 
		{
#ifdef DEBUG
	OutputDebugString(L"rm_file(): Deleted done.");
#endif
		}
	}
	catch (int x)
	{
#ifdef DEBUG
		char *err;
		sprintf_s(err, "rm_file(): Something wrong with rm_file(); %s", x);
	OutputDebugString(err);
#endif
		return x;
	}
	return 0;
}


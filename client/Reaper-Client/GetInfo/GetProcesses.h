#pragma once
#include <Windows.h>

TCHAR* GetProcessName(DWORD processID);
void GetProcesses();
void CleanProcesses(TCHAR* processList[1024]);
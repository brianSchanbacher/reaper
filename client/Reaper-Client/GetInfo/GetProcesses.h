#pragma once
#include <Windows.h>

TCHAR* GetProcessName(DWORD processID);
char* GetProcesses(int *numProcesses);
void CleanProcesses(TCHAR* processList[1024]);
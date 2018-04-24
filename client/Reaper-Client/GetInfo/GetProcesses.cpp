#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <Psapi.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>

TCHAR* GetProcessName(DWORD processID) {
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.
	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// Release the handle to the process.
	CloseHandle(hProcess);

	return _tcsdup(szProcessName);
}

char* GetProcesses(int *numProcesses) {
	DWORD processes[1024], pBytesReturned;
	TCHAR* processName = (TCHAR*)malloc(1024 * sizeof(TCHAR));
	char* cpProcessNames = (char*)malloc(4080 * sizeof(char));

	BOOL success = EnumProcesses(
		processes,
		sizeof(processes),
		&pBytesReturned
	);

	if (!success) return NULL;

	*numProcesses = pBytesReturned / sizeof(DWORD);
	int count = 0;
	for (DWORD i = 0; i < *numProcesses; i++) {
		if (processes[i] != 0) {
			processName = GetProcessName(processes[i]);
			DWORD strsize = wcslen(processName);
			wcstombs(cpProcessNames + count, processName, 4080 - count);
			count++;
		}
	}

	return cpProcessNames;
}

void CleanProcesses(TCHAR* processList[1024]) {
	for (int i = 0; i < 1024; i++) {
		free(processList[i]);
	}
}
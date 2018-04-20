#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <tchar.h>

#include "stdafx.h"


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

void GetProcesses() {
	DWORD processes[1024], pBytesReturned;
	TCHAR** processNames = (TCHAR**)malloc(1024 * sizeof(TCHAR));

	BOOL success = EnumProcesses(
		processes,
		sizeof(processes),
		&pBytesReturned
	);

	if (!success) return;

	DWORD numProcesses = pBytesReturned / sizeof(DWORD);

	for (int i = 0; i < numProcesses; i++) {
		if (processes[i] != 0) {
			processNames[i] = GetProcessName(processes[i]);
		}
	}
}

void CleanProcesses(TCHAR* processList[1024]) {
	for (int i = 0; i < 1024; i++) {
		free(processList[i]);
	}
}
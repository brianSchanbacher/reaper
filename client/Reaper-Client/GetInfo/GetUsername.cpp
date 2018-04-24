#include "stdafx.h"

#include <Windows.h>
#include <lmcons.h>
#include <malloc.h>

LPWSTR GetUser() {
	LPWSTR lpBuffer = (WCHAR*)malloc((UNLEN + 1) * sizeof(WCHAR));
	DWORD dwSize = UNLEN;

	BOOL success = GetUserName(
		lpBuffer,
		&dwSize
	);

	return success ? lpBuffer : NULL;
}
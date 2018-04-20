#include <Windows.h>
#include <lmcons.h>

LPWSTR GetUser() {
	LPWSTR lpBuffer = (WCHAR*)malloc((UNLEN + 1) * sizeof(WCHAR));
	LPDWORD lpnSize;

	BOOL success = GetUserName(
		lpBuffer,
		lpnSize
	);

	return success ? lpBuffer : NULL;
}
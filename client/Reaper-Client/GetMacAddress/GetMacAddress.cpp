#include "stdafx.h"
#include <Windows.h>
#include <WinSock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "GetMacAddress.h"

char* GetMACaddress(void)
{
	char* macAddress = (char*)malloc(18);

	IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);                  // [in] size of receive data buffer
	if (dwStatus != ERROR_SUCCESS)
	{
		return NULL;
	}

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to  current adapter info
	do
	{
		if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET) {
			snprintf(macAddress, 18,
				"%X:%X:%X:%X:%X:%X",
				*(pAdapterInfo->Address), *(pAdapterInfo->Address + 1), *(pAdapterInfo->Address + 2),
				*(pAdapterInfo->Address + 3), *(pAdapterInfo->Address + 4), *(pAdapterInfo->Address + 5));
			break;
		}
		pAdapterInfo = pAdapterInfo->Next;    // Progress through linked list
	} while (pAdapterInfo);                    // Terminate if last adapter

	return macAddress;
}
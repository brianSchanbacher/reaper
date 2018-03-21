#include "stdafx.h"

#include <Windows.h>
#include <stdio.h>

bool RedPillMethod() {
	/**
	The IDTR on VMs will be much higher than on a host machine.
	This function tests the IDTR against prepared values to see
	if it matches values common with virtualization
	*/
	unsigned char idtr[6];
	unsigned long idt = 0;
	unsigned long idt_base = 0;

	__asm sidt idtr

	idt = *((unsigned long *)&idtr[2]);
	idt_base = idt >> 24;

	if (idt_base > 0xd0 || idt_base == 0x5d) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

bool VMWareDetect() {
	/**
	VMWare hooks into CPU port 5658h
	Specific calls to this port will return data
	Call 0xA queries the version of VMWare when a proper magic number is set in EAX
	TODO Stop it from segfaulting
	*/
	unsigned long r_ebx = 0; // Stores the result from the port

							 // Opens a CPU port to query the VMWare utils
	__asm {
		MOV EAX, 564D5868h; VMXh
		MOV EBX, 0
		MOV ECX, 0Ah; Request VMWare version
		MOV EDX, 5658h; VX
		in EAX, DX; Lowercase cuz of macros
		MOV r_ebx, EBX; EBX should be VMXh
	}

	// 0x564D5868 -> "VMXh"
	if (r_ebx == 0x564D5868)
		return TRUE;

	//printf("[-] IN PORT: 0x%x\n", r_ebx);
	return FALSE;
}

bool inAVirtualMachine() {
	bool redPillMethod = RedPillMethod();
	bool VMWareMethod = VMWareDetect();

	// Return aggregate of detection methods
	return redPillMethod | VMWareMethod;
}
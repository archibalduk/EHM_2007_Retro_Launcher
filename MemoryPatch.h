#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <Tlhelp32.h>

class MemoryPatch
{
private:
	int offset;
	int value;
	unsigned char size;
	std::string description;

	static DWORD pidEHM;
	static HANDLE exeEHM;

	static DWORD getPIDForProcess(wchar_t*);

public:
	MemoryPatch(void) {}
	MemoryPatch(int, int, unsigned char, std::string);
	~MemoryPatch(void) {}

	bool apply();

	static bool loadEHM(int, _TCHAR*[]);	
};
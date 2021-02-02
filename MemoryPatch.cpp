#include "MemoryPatch.h"

DWORD MemoryPatch::pidEHM;
HANDLE MemoryPatch::exeEHM;

MemoryPatch::MemoryPatch(int _offset, int _value, unsigned char _size, std::string _description) :
	offset(_offset),
	value(_value),
	size(_size),
	description(_description)
{
}

// Apply the changes
bool MemoryPatch::apply()
{
	// Buffer for reading the memory
	int currentValue = 0;

	// Read the memory to find the value before patching
	ReadProcessMemory(exeEHM, (void *)offset, &currentValue, size, NULL);

	std::cout << description << " (" << offset << "): " << currentValue << " -> " << value << " ";

	// Write to the memory
	if(WriteProcessMemory(exeEHM, (void *)offset, &value, size, NULL)){
		std::cout << "SUCCESS" << std::endl;
		return true;
	}
	else {
		std::cout << "ERROR" << std::endl;
		return false;
	}
}

// Load EHM and get Process ID
bool MemoryPatch::loadEHM(int argc, _TCHAR *argv[])
{
	std::cout << "Loading EHM ";
	/*
	if(argc != 0) {
		std::cout << "(" << argc << " -small_screen -windowed)" << std::endl;
		ShellExecute(NULL, L"open", L"EHM2007.exe", L"-small_screen -windowed", NULL, SW_SHOW);
	}*/
	// If only one or no command line arguments are present
	//else {
		std::cout << "(no command line arguments)" << std::endl;
		ShellExecute(NULL, L"open", L"EHM2007.exe", NULL, NULL, SW_SHOW);
	//}
	
	std::cout << "Waiting 6 seconds for EHM to load..." << std::endl;
	Sleep(6000);	// Wait six seconds in order to allow EHM to load before getting the process ID and opening the process

	std::cout << "Getting process ID..." << std::endl;
	pidEHM = getPIDForProcess(L"ehm2007.exe");
	exeEHM = OpenProcess(PROCESS_ALL_ACCESS, false, pidEHM);

	if(exeEHM)
		return true;
	else
		return false;
}

// Get process ID for a running process
DWORD MemoryPatch::getPIDForProcess(wchar_t* process)
{
    BOOL working=0;
    PROCESSENTRY32 lppe={0};
    DWORD targetPid=0;
    HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS ,0);
    if (hSnapshot) 
	{
		lppe.dwSize=sizeof(lppe);
		working=Process32First(hSnapshot,&lppe);
		while (working)
		{
			if(wcscmp(lppe.szExeFile,process)==0)
			{
				targetPid=lppe.th32ProcessID;
				break;
			}
			working=Process32Next(hSnapshot,&lppe);
		}
	}
    CloseHandle( hSnapshot );
    return targetPid;
}
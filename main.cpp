#include "main.h"
#include <windows.h>
#include <stdlib.h>
#include <Psapi.h>

using namespace std;

#define PRINTF( f, ... ) { printf( "[+] " f "\n", __VA_ARGS__ ); }
#define PUTS( s ) { printf( "[+] %s \n", s ); }

#define NtCurrentProcess() ( (HANDLE)(LONG_PTR) -1 )

// can be __stdcall for some reason.
using ZwQueryVirtualMemory_t = NTSTATUS(__fastcall*) (HANDLE, PVOID, int, PVOID, SIZE_T, PSIZE_T);

int main()
{
	auto address = VirtualAlloc (nullptr, 0x1000,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	cout << "read the address --> 0x" << hex << address << endl;

	HMODULE ntdll = GetModuleHandle("ntdll.dll");

	auto ZwQueryVirtualMemory = (ZwQueryVirtualMemory_t)GetProcAddress(ntdll, "ZwQueryVirtualMemory");

	if (!ZwQueryVirtualMemory) {
		cout << "ZwQueryVirtualMemory pointer couldn't be retrieved" << endl;
	}

	while (true) {
		PSAPI_WORKING_SET_EX_INFORMATION info = { 0 };
		info.VirtualAddress = address;

		// 4 is the indicies indicates MemoryWorkingSetList
		auto status = ZwQueryVirtualMemory(NtCurrentProcess(), NULL, 4, &info, sizeof info, NULL);

		// if Valid is 1, it means memory read has been detected
		if (info.VirtualAttributes.Valid)
			cout << "the memory has been read." << endl;

		if(GetAsyncKeyState(VK_F1) & 1) {
		    break;
		}
		Sleep(300);
	}
	return 0;
}

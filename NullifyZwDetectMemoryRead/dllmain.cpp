#include "dllmain.h"
#include <iostream>
#include "MinHook.h"

#define DEBUG

#ifdef DEBUG
#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}
#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#else
#define LOGHEX(name, val)
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif

using namespace std;

void Detach()
{
    FREECONSOLE()
}

ZwQueryVirtualMemory_t oZwQueryVirtualMemory = NULL;

NTSTATUS DetourZwQueryVirtualMemory(HANDLE hProcess, PVOID address, int indices, PVOID buffer, SIZE_T bufferLength, PSIZE_T returnLength) {
    NTSTATUS status = oZwQueryVirtualMemory(hProcess, address, indices, buffer, bufferLength, returnLength);
    if (indices != 4) {
        return status;
    }
    reinterpret_cast<PSAPI_WORKING_SET_EX_INFORMATION*>(buffer)->VirtualAttributes.Valid = 0;
    return status;
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE();
	HMODULE ntdll = GetModuleHandle("ntdll.dll");
    ZwQueryVirtualMemory_t ZwQueryVirtualMemory = (ZwQueryVirtualMemory_t)GetProcAddress(ntdll, "ZwQueryVirtualMemory");

    if (MH_STATUS status = MH_Initialize(); status != MH_OK) {
        cout << "Error at MH_Initialize: " << status << endl;
        return 1;
    }
    // Note that u don't pass &ZwQueryVirtualMemory for pTarget.  ZwQueryVirtualMemory itself is already a pointer.
    if (MH_STATUS status = MH_CreateHook(ZwQueryVirtualMemory, &DetourZwQueryVirtualMemory, reinterpret_cast<LPVOID*>(&oZwQueryVirtualMemory)); status != MH_OK) {
        cout << "Error at MH_CreateHook: " << status << endl;
        return 1;
    }
    // same here
    if (MH_STATUS status = MH_EnableHook(ZwQueryVirtualMemory); status != MH_OK) {
        cout << "Error at MH_EnableHook: " << status << endl;
        return 1;
    }
    else {
        cout << "Hook has been placed." << endl;
    }

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) {
            if (MH_DisableHook(ZwQueryVirtualMemory) != MH_OK) {
                cout << "Error at MH_DisableHook" << endl;
            }
            break;
        }
        Sleep(10);
    }
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(nullptr, 0, fMain, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    } else if (dwReason == DLL_PROCESS_DETACH && !lpReserved) {
        Detach();
    }
    return TRUE;
}
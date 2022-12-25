#pragma once
#include <Windows.h>
#include <Psapi.h>

using ZwQueryVirtualMemory_t = NTSTATUS(__fastcall*) (HANDLE, PVOID, int, PVOID, SIZE_T, PSIZE_T);

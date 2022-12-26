# ZwDetectMemoryRead

This is based on this [gist](https://gist.github.com/dkrutsko/d6118638b0ef711b30bfcfe5b083d067). (@dkrutsko)

While this gist is approaching with [QueryWorkingSetEx](https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-queryworkingsetex), 
this piece of code is using [ZwQueryVirtualMemory](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-zwqueryvirtualmemory) which is even lower layer of original one.
The thing is, official document saids ZwQueryVirtualMemory only support MEMORY_BASIC_INFORMATION, but acrually supports PSAPI_WORKING_SET_EX_INFORMATION under the hood. Idk why maybe it's undocumented behavior?

COOL!

# NullifyZwDetectMemoryRead

an independent code of hooking ZwQueryVirtualMemory to ruin this method. it's a separate code that works individually.

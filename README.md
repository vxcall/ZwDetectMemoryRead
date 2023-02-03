# ZwDetectMemoryRead

This is based on this [gist](https://gist.github.com/dkrutsko/d6118638b0ef711b30bfcfe5b083d067) by [@dkrutsko](https://github.com/dkrutsko). Kudos to him.

While this gist is approaching with [QueryWorkingSetEx](https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-queryworkingsetex), 
this piece of code is using [ZwQueryVirtualMemory](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-zwqueryvirtualmemory) which is even lower layer of his.
What got my attention is, official document says ZwQueryVirtualMemory solely support MEMORY_BASIC_INFORMATION, but acrually supports PSAPI_WORKING_SET_EX_INFORMATION under the hood. Most likely is an undocumented behavior?

It must not be something new technique but cool anyways.

# NullifyZwDetectMemoryRead

an independent code of hooking ZwQueryVirtualMemory to ruin this method. it's a separate code that works individually.

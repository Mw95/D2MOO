// Storm.dll stub loaded by the original D2Lang.dll, exporting the functions it imports by ordinal (see Storm.def).
#include "FakeImpl.h"
extern "C" {
__declspec(dllexport) void* __stdcall sMemAlloc(int n, const char*, int, unsigned) { return fake_alloc(n); }
__declspec(dllexport) BOOL __stdcall sMemFree(void* p, const char*, int, unsigned) { fake_free(p); return TRUE; }
__declspec(dllexport) BOOL __stdcall sFileGetFileName(HANDLE, char* b, int n) { if (n) b[0] = 0; return TRUE; }
__declspec(dllexport) int __stdcall sUniConvertUTF8to16(wchar_t* o, int oc, const char* s, int sc, int* ol, int) { return fake_utf8to16(o, oc, s, sc, ol); }
}

// Fog.dll stub loaded by the original D2Lang.dll, exporting the functions it imports by ordinal (see Fog.def).
#include "FakeImpl.h"
extern "C" {
__declspec(dllexport) void __cdecl fDisplayAssert(const char* m, const char* f, int l) { fake_assert(m, f, l); }
__declspec(dllexport) void __cdecl fDisplayHalt(const char* m, const char* f, int l) { fake_assert(m, f, l); }
__declspec(dllexport) void __cdecl fDisplayError(int, const char* m, const char* f, int l) { fake_assert(m, f, l); }
__declspec(dllexport) void __cdecl fTrace(const char* fmt, ...) { va_list a; va_start(a, fmt); fake_vtrace(fmt, a); va_end(a); }
__declspec(dllexport) void* __fastcall fAlloc(int n, const char*, int, int) { return fake_alloc(n); }
__declspec(dllexport) void __fastcall fFree(void* p, const char*, int, int) { fake_free(p); }
__declspec(dllexport) BOOL __fastcall fFOpenFile(const char* p, void** h) { return fake_fopen(p, h); }
__declspec(dllexport) void __fastcall fFCloseFile(void* h) { fake_fclose(h); }
__declspec(dllexport) BOOL __fastcall fFReadFile(void* h, void* b, size_t n, int* r, unsigned, unsigned, unsigned) { return fake_fread(h, b, n, r); }
__declspec(dllexport) unsigned __fastcall fFGetFileSize(void* h, unsigned* hi) { return fake_fsize(h, hi); }
}

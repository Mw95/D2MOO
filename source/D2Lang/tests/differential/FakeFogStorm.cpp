// Definitions of the Fog/Storm functions used by D2MOO's D2Lang/D2Hell, when built statically into the harness.
#include "FakeImpl.h"
#include <Fog.h>
#include <Storm.h>
void __cdecl FOG_DisplayAssert(const char* m, const char* f, int l) { fake_assert(m, f, l); }
void __cdecl FOG_DisplayHalt(const char* m, const char* f, int l) { fake_assert(m, f, l); }
void __cdecl FOG_DisplayError(int, const char* m, const char* f, int l) { fake_assert(m, f, l); }
void __cdecl FOG_Trace(const char* fmt, ...) { va_list a; va_start(a, fmt); fake_vtrace(fmt, a); va_end(a); }
void* __fastcall FOG_Alloc(int n, const char*, int, int) { return fake_alloc(n); }
void __fastcall FOG_Free(void* p, const char*, int, int) { fake_free(p); }
BOOL __fastcall FOG_FOpenFile(const char* p, HSFILE* h) { return fake_fopen(p, (void**)h); }
void __fastcall FOG_FCloseFile(HSFILE h) { fake_fclose(h); }
BOOL __fastcall FOG_FReadFile(HSFILE h, void* b, size_t n, int* r, uint32_t, uint32_t, uint32_t) { return fake_fread(h, b, n, r); }
uint32_t __fastcall FOG_FGetFileSize(HSFILE h, uint32_t* hi) { return fake_fsize(h, (unsigned*)hi); }
size_t __fastcall FOG_FSetFilePointer(HSFILE h, int32_t d, int32_t* hi, uint32_t m) { return fake_fseek(h, d, (int*)hi, m); }
BOOL __stdcall SFileGetFileName(HANDLE, char* b, int n) { if (n) b[0] = 0; return TRUE; }
BOOL __stdcall SFileOpenArchive(char*, int, int, HSARCHIVE* p) { *p = nullptr; return FALSE; }
BOOL __stdcall SFileCloseArchive(HSARCHIVE) { return TRUE; }
int __stdcall SStrNCat(char* base, const char* app, int max) { strncat(base, app, max - strlen(base) - 1); return (int)strlen(base); }
int __stdcall SUniConvertUTF8to16(wchar_t* o, int oc, const char* s, int sc, int* ol, int) { return fake_utf8to16(o, oc, s, sc, ol); }
void* __stdcall SMemAlloc(int n, const char*, int, uint32_t) { return fake_alloc(n); }
BOOL __stdcall SMemFree(void* p, const char*, int, uint32_t) { fake_free(p); return TRUE; }

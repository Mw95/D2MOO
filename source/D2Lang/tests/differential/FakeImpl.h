// Minimal fake implementations of the Fog/Storm functions used by D2Lang (1.10f), shared by the stub DLLs (used by the
// original D2Lang.dll) and by the D2MOO build in the harness.
#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
static inline void* fake_alloc(int n) { return calloc(1, n ? n : 1); }
static inline void fake_free(void* p) { free(p); }
static inline void fake_assert(const char* m, const char* f, int l) { fprintf(stderr, "ASSERT: %s (%s:%d)\n", m, f, l); fflush(stderr); ExitProcess(3); }
static inline void fake_vtrace(const char* fmt, va_list a) { if (getenv("FAKE_TRACE")) { vfprintf(stderr, fmt, a); fputc('\n', stderr); } }
static inline BOOL fake_fopen(const char* path, void** h) { FILE* f = fopen(path, "rb"); *h = f; if (getenv("FAKE_TRACE")) fprintf(stderr, "open %s -> %p\n", path, (void*)f); return f != NULL; }
static inline void fake_fclose(void* h) { if (h) fclose((FILE*)h); }
static inline unsigned fake_fsize(void* h, unsigned* hi) { FILE* f = (FILE*)h; long c = ftell(f); fseek(f, 0, SEEK_END); long s = ftell(f); fseek(f, c, SEEK_SET); if (hi) *hi = 0; return (unsigned)s; }
static inline BOOL fake_fread(void* h, void* b, size_t n, int* r) { size_t x = fread(b, 1, n, (FILE*)h); if (r) *r = (int)x; return x == n; }
static inline unsigned fake_fseek(void* h, int d, int* hi, unsigned m) { fseek((FILE*)h, d, m); return (unsigned)ftell((FILE*)h); }
static inline int fake_utf8to16(wchar_t* out, int outCount, const char* src, int srcCount, int* outLen) {
    int n = MultiByteToWideChar(CP_UTF8, 0, src, srcCount, out, outCount);
    if (outLen) *outLen = n; return n > 0 ? 0 : 1;
}

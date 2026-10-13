#include <Fog.h>

// Functions that are empty in the release build, probably debug or profiling functions that were compiled out.
// Several ordinals are exported with the same function, see the .def file.

// 1.10f: 0x6FF51DE0 (#10082)
// Also used by #10048, #10049, #10053, #10054, #10146, #10194, #10195, #10196, #10197, #10220, #10221, #10225, #10232, #10240, #10241, #10242, #10243
// 1.10f: 0x6FF5DC60 (#10251) is an identical function
void __fastcall FOG_10082_Noop()
{
}

// 1.10f: 0x6FF51B10 (#10182)
// Also used by #10081
int __stdcall FOG_10182_Return(void*)
{
	// Note: original code does not set a return value
	return 0;
}

// 1.10f: 0x6FF57620 (#10183)
// Also used by #10228
int __stdcall FOG_10183_Return(void*, int)
{
	// Note: original code does not set a return value
	return 0;
}

// 1.10f: 0x6FF5C9D0 (#10098)
// Also used by #10148, #10192
int __cdecl FOG_ReturnZero()
{
	return 0;
}

// 1.10f: 0x6FF57410 (#10167)
// Also used by #10179, #10193
void __stdcall FOG_Noop_Stdcall3(int, int, int)
{
}

// 1.10f: 0x6FF5F0F0 (#10236)
void __stdcall FOG_Noop_Stdcall6(int, int, int, int, int, int)
{
}

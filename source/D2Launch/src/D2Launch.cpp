#include "D2Launch.h"

#include "MainMenus.h"


//D2Launch.0x6FA3CA90
HINSTANCE ghD2LaunchInstance;

//D2Launch.0x6FA3333C
D2LaunchInterfaceStrc gD2LaunchInterface =
{
	MENU_Run,
};


//D2Launch.0x6FA17740 (#1)
D2LaunchInterfaceStrc* __cdecl QueryInterface()
{
	return &gD2LaunchInterface;
}

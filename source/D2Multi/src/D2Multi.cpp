#include "D2Multi.h"

#include "ChatDlg.h"


D2MultiInterfaceStrc gD2MultiInterface_6F9BEA8C =
{
	CHATDLG_RunModule,
};

//D2Multi.0x6F9AF3B0 (#1)
D2MultiInterfaceStrc* __cdecl QueryInterface()
{
	return &gD2MultiInterface_6F9BEA8C;
}

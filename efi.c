#include"efi.h"

EFI_SYSTEM_TABLE *SysTbl;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;

void EfiInit(EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GUID GOP_GUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	SysTbl = SystemTable;
	SysTbl->ConOut->ClearScreen(SysTbl->ConOut);
	SysTbl->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	SysTbl->BootServices->LocateProtocol(&GOP_GUID, NULL, (void **)&GOP);
}

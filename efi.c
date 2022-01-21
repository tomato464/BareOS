#include"efi.h"

EFI_SYSTEM_TABLE *SysTbl;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
EFI_SIMPLE_POINTER_PROTOCOL *SPP;

void EfiInit(EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GUID GOP_GUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GUID SPP_GUID = EFI_SIMPLE_POINTER_PROTOCOL_GUID;

	SysTbl = SystemTable;
	SysTbl->ConOut->ClearScreen(SysTbl->ConOut);
	SysTbl->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	SysTbl->BootServices->LocateProtocol(&GOP_GUID, NULL, (void **)&GOP);
	SysTbl->BootServices->LocateProtocol(&SPP_GUID, NULL, (void **)&SPP);
}

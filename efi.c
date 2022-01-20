#include"efi.h"

EFI_SYSTEM_TABLE *SysTbl;

void EfiInit(EFI_SYSTEM_TABLE *SystemTable)
{
	SysTbl = SystemTable;
	SysTbl->ConOut->ClearScreen(SysTbl->ConOut);
	SysTbl->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
}

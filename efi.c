#include"efi.h"

EFI_SYSTEM_TABLE *SysTbl;

void EfiInit(EFI_SYSTEM_TABLE *SystemTable)
{
	SysTbl = SystemTable;
}

#ifndef _EFI_H_
#define _EFI_H_

#include"defines.h"
#include"efi.h"

extern EFI_SYSTEM_TABLE *SysTbl;

void EfiInit(EFI_SYSTEM_TABLE *SystemTable);

#endif

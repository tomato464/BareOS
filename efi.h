#ifndef _EFI_H_
#define _EFI_H_

#include"defines.h"
#include"efi.h"

extern EFI_SYSTEM_TABLE *SysTbl;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL	*GOP;

void EfiInit(EFI_SYSTEM_TABLE *SystemTable);

#endif

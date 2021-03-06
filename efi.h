#ifndef _EFI_H_
#define _EFI_H_

#include"defines.h"
#include"efi.h"

extern EFI_SYSTEM_TABLE *SysTbl;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL	*GOP;
extern EFI_SIMPLE_POINTER_PROTOCOL *SPP;
extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FSP;

void ClearScreen(void);
void EfiInit(EFI_SYSTEM_TABLE *SystemTable);

#endif

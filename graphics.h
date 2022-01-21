#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include"defines.h"
#include"efi.h"
#include"lib.h"

void Draw(UINT32 x, UINT32 y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *color);
void DrawRec(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2);

#endif

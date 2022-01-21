#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include"defines.h"
#include"efi.h"
#include"lib.h"

extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT white;
extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT brack;
extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT yellow;
typedef struct {
	UINT32 x, y;
	UINT32 w,h;
}RECT;


void DrawPixel(UINT32 x, UINT32 y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color);
void DrawRectAll(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2,\
					 EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color);
void DrawRect(RECT rec, EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color);
EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT GetPixel(UINT32 x, UINT32 y);
bool IsInRect(UINT32 x, UINT32 y, RECT rect);

#endif

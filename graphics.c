#include"graphics.h"

void draw(UINT32 x, UINT32 y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color)
{//if this is wrong, check GOP->Mode->Info->PixelFormat
	UINT32 hr = GOP->Mode->Info->HorizontalResolution;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *base = \
			(EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *)GOP->Mode->FrameBufferBase;

	EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *p;
	
	p = base + x + (hr * y);

	p->Blue 	=	color.Blue;
	p->Green	=	color.Green;
	p->Red		=	color.Red;
	p->Reserved =	color.Reserved;
}

void DrawRec(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2)
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color;
	color.Blue		= 0xff;
	color.Green	= 0xff;
	color.Red		= 0xff;
	color.Reserved	= 0xff;

	for(UINT32 i = y1; i < y2 ; i++){
		for(UINT32 j = x1; j < x2; j++){
			draw(j, i, color);
		}
	}
}

#include"graphics.h"

const EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT white = {0xff, 0xff, 0xff, 0xff};
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT brack = {0x0, 0x0, 0x0, 0x0};
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT yellow = {0x0, 0xff, 0xff, 0xff};
void DrawPixel(UINT32 x, UINT32 y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color)
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

void DrawRectAll(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2,\
			 EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color)
{
	for(UINT32 i = y1; i < y2 ; i++){
		for(UINT32 j = x1; j < x2; j++){
			DrawPixel(j, i, color);
		}
	}
}

void DrawRect(RECT rec, EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT color)
{
	UINT32 i;

	for(i = 0; i < rec.w; i++){
		DrawPixel(rec.x + i, rec.y, color);
	}

	for(i = 0; i < rec.h; i++){
		DrawPixel(rec.x, rec.y + i, color);
		DrawPixel(rec.x + rec.w, rec.y + i, color);
	}

	for(i = 0; i < rec.w; i++){
		DrawPixel(rec.x + i, rec.y + rec.h, color);
	}
}

EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT GetPixel(UINT32 x, UINT32 y)
{
	UINT32 hori = GOP->Mode->Info->HorizontalResolution;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *p;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *base;
	base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT *)GOP->Mode->FrameBufferBase;
	
	p = base + x + (hori * y); 

	return *p;
}

bool IsInRect(UINT32 x, UINT32 y, RECT rec)
{
	if((rec.x <= x && x <=rec.x + rec.w) && (rec.y <= y && y <= rec.y + rec.h)){
		return true;
	}
	return false;
}
void Blt(UINT8 buf[], UINT32 img_w, UINT32 img_h)
{//only from (0, 0)
	UINT32 ofs = 0;
	UINT8 *fb = (UINT8 *)GOP->Mode->FrameBufferBase;
	UINT32 hr = GOP->Mode->Info->HorizontalResolution;
	UINT32 ver = GOP->Mode->Info->VerticalResolution;
	for(UINT32 y = 0; y < ver; y++){
		if(y >= img_h){
			break;
		}
		for(UINT32 x = 0; x < hr; x++){
			if(x >= img_w){
				fb += (hr - img_w)*4;
				break;
			}
			for(int k = 0; k < 4; k++){
				*fb = buf[ofs];
				ofs++;
				fb++;
			}
		}
	}
}

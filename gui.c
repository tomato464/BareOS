#include"gui.h"
EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT cursol_tmp = {0, 0, 0, 0};

UINT32 old_x;
UINT32 old_y;

static void DrawCursol(UINT32 x, UINT32 y)
{
	DrawPixel(x, y, white);
}

static void SaveCursolArea(UINT32 x, UINT32 y)
{
	cursol_tmp = GetPixel(x, y);
	cursol_tmp.Reserved = 0xff;
}

static void LoadCursolArea(UINT32 x, UINT32 y)
{
	DrawPixel(x, y, cursol_tmp);
}

static void MoveCursol(UINT32 x, UINT32 y)
{
	if(cursol_tmp.Reserved){
		LoadCursolArea(old_x, old_y);
	}
	SaveCursolArea(x, y);
	DrawCursol(x, y);

	old_x = x;
	old_y = y;
}

void Gui(void)
{
	EFI_STATUS n;
	RECT win = {10, 10, 20, 20};
	UINTN waitidx;
	EFI_SIMPLE_POINTER_STATE s;
	SPP->Reset(SPP, false);
	bool IsHilight = false;

	int cursol_x = 100;
	int cursol_y = 100;

	SysTbl->ConOut->ClearScreen(SysTbl->ConOut);
	DrawRect(win, white);
	while(1){
		SysTbl->BootServices->WaitForEvent(1,
										&(SPP->WaitForInput), &(waitidx));

		n = SPP->GetState(SPP, &s);
		if(!n){
			cursol_x += (s.RelativeMomentX >> 12);
			if(cursol_x <= 0){
				cursol_x = 1;
			}
			if(cursol_x >= (int)GOP->Mode->Info->HorizontalResolution){
				cursol_x = GOP->Mode->Info->HorizontalResolution - 1;
			}
			cursol_y += (s.RelativeMomentY >> 12);
			if(cursol_y <= 0){
				cursol_y = 1;
			}
			if(cursol_y >= (int)GOP->Mode->Info->VerticalResolution){
				cursol_y = GOP->Mode->Info->VerticalResolution - 1;
			}

			MoveCursol(cursol_x, cursol_y);

			if(IsInRect(cursol_x, cursol_y, win)){
				if(!IsHilight){
					DrawRect(win, yellow);
					IsHilight = true;
				}
			}else{
				if(IsHilight){
					DrawRect(win, white);
					IsHilight = false;
				}
			}
		}
	}
}

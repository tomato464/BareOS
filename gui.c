#include"gui.h"
EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT cursol_tmp = {0, 0, 0, 0};

UINT32 old_x;
UINT32 old_y;

static void gui_cat(CHAR16 *file_name)
{
	ClearScreen();
	cat(file_name);

	while(1){
		if(getc() == SC_ESC){
			break;
		}
	}
}

static UINT32 gui_ls()
{	
	ClearScreen();
	UINT32 file_num = ls();
	UINT32 x = 0;
	UINT32 y = 0;
	UINT32 len;

	for(UINT32 idx = 0; idx < file_num; idx++){
		len = strlen(FileList[idx].Name);
		FileList[idx].rect.x = x;
		FileList[idx].rect.y = y;
		FileList[idx].rect.w = W_PER_CHAR * len;
		FileList[idx].rect.h = H_PER_CHAR;
		FileList[idx].IsHighlight = false;
		DrawRect(FileList[idx].rect, white);
		x = x + W_PER_CHAR * len;
	}
	return file_num;
}

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
	UINTN waitidx;
	EFI_SIMPLE_POINTER_STATE s;
	UINT32 file_num;


	SPP->Reset(SPP, false);

	int cursol_x = 100;
	int cursol_y = 100;

	file_num = gui_ls();
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
			for(UINT32 i = 0; i < file_num; i++){
				if(IsInRect(cursol_x, cursol_y, FileList[i].rect)){
					if(!FileList[i].IsHighlight){
						DrawRect(FileList[i].rect, yellow);
						FileList[i].IsHighlight = true;
					}
					if(s.LeftButton){
						gui_cat(FileList[i].Name);
						file_num = gui_ls();
					}
				}else{
					if(FileList[i].IsHighlight){
						DrawRect(FileList[i].rect, white);
						FileList[i].IsHighlight = false;
					}

				}
			}
		}
	}
}

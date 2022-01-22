#include"shell.h"
RECT rec = {100,100, 100, 200};

#define MAX_BUF_SIZE 256
#define MAX_IMAGE_BUF 2097107

UINT8 img[MAX_IMAGE_BUF];
void view(CHAR16 *file_name)
{

	EFI_STATUS stat;
	EFI_FILE_PROTOCOL *root;
	EFI_FILE_PROTOCOL *file;
	UINT32 hr = GOP->Mode->Info->HorizontalResolution;
	UINT32 ver = GOP->Mode->Info->VerticalResolution;

	UINTN buffer_size = MAX_IMAGE_BUF;

	ClearScreen();
	

	stat = OpenVolume(&root);
	Assert(stat, L"SFP->OpenVlume");
	stat = Open(root, &(file), file_name, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if(stat){
		puts(L"error at root->open\r\n");
		Close(root);
		return;
	}
	stat = Read(file, &buffer_size, (void*)img);
	Assert(stat, L"file->read");
	if(buffer_size){
		Blt(img, hr, ver);
		while(1){
			if(getc() == SC_ESC){
				break;
			}
		}
	}
	puts(L"\r\n");


	Close(file);
	Close(root);

}

void edit(CHAR16 *file_name)
{
	EFI_STATUS stat;
	EFI_FILE_PROTOCOL *root;
	EFI_FILE_PROTOCOL *file;

	CHAR16 buffer[MAX_FILE_BUF >> 1];
	UINTN buffer_size = MAX_FILE_BUF;

	ClearScreen();

	CHAR16 c;
	UINT32 i = 0;
	while(1){
		c = getc();

		if(c == SC_ESC){
			buffer[i] = L'\0';			
			break;
		}

		if(c == L'\r'){
			buffer[i++] = c;
			buffer[i++] = L'\n';
			puts(L"\r\n");
			continue;
		}
		putc(c);
		buffer[i++] = c;
	}
	stat = OpenVolume(&root);
	Assert(stat, L"SFP->OpenVlume");
	stat = Open(root, &(file), file_name, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
	if(stat){
		puts(L"error at root->open\r\n");
		Close(root);
		return;
	}

	stat = Write(file, &(buffer_size), (void *) buffer);
	Assert(stat, L"file->Write");
	
	stat = Flush(file);
	Assert(stat, L"file->flush");
	Close(file);
	Close(root);

}

void cat(CHAR16 *file_name)
{
	EFI_STATUS stat;
	EFI_FILE_PROTOCOL *root;
	EFI_FILE_PROTOCOL *file;

	CHAR16 buffer[MAX_FILE_BUF];
	UINTN buffer_size = MAX_FILE_BUF;

	stat = OpenVolume(&root);
	Assert(stat, L"SFP->OpenVlume");
	stat = Open(root, &(file), file_name, EFI_FILE_MODE_READ, 0);
	if(stat){
		puts(L"error at root->open\r\n");
		Close(root);
		return;
	}
	stat = Read(file, &buffer_size, (void*)buffer);
	Assert(stat, L"file->read");
	if(buffer_size){
		puts(buffer);
	}
	puts(L"\r\n");

	Close(file);
	Close(root);
	return;
}

UINT32 ls()
{
	EFI_STATUS status;
	EFI_FILE_PROTOCOL *fs;
	EFI_FILE_INFO *file_info;
	UINT32 idx = 0;
	UINTN buffer_size = MAX_FILE_BUF;
	UINT8  buf[MAX_FILE_BUF];

	status = OpenVolume(&fs);
	Assert(status, L"OpenVolume");

	while(1){
		buffer_size = MAX_FILE_BUF;//otherwist this overwrite by read, and this will be 0;
		status = Read(fs, &buffer_size, (void *)buf);
		Assert(status, L"File Read");
		if(!buffer_size){
			break;
		}
		file_info = (EFI_FILE_INFO *)buf;
		strncpy(FileList[idx].Name, file_info->FileName, MAX_FILE_NAME);
		FileList[idx].Name[MAX_FILE_NAME] = L'\0';
		puts(FileList[idx].Name);
		puts(L" ");
		idx++;
	}

	puts(L"\r\n");
	Close(fs);
	return idx;
}

void pstat()
{
	EFI_STATUS n;
	EFI_SIMPLE_POINTER_STATE state;
	UINTN	waitidx;
	SPP->Reset(SPP, false);
	int i = 0;
	puts(L"wating for mouse input.....\r\n");
	while(1){
		SysTbl->BootServices->WaitForEvent(1,
								&(SPP->WaitForInput), &waitidx);

		n = SPP->GetState(SPP, &state);
		if(!n){
			putxval(state.RelativeMomentX, 8);
			puts(L"  ");
			putxval(state.RelativeMomentY, 8);
			puts(L"  ");
			putxval(state.RelativeMomentZ, 8);
			puts(L"  ");
			putxval(state.LeftButton, 1);
			puts(L"  ");
			putxval(state.RightButton, 1);
			puts(L"  \r\n");
		}else{
			puts(L"failed\r\n");
		}
		i++;
		if(i == 100){
			return;
		}
	}
}

void shell()
{
	CHAR16 buf[MAX_BUF_SIZE];

	while(1){
		puts(L"KajiOS>");
		if(gets(buf, MAX_BUF_SIZE) <= 0){
			continue;
		}

		if(!strcmp(buf, L"hello")){
			puts(L"Hello! EFI\r\n");
		}else if(!strcmp(buf, L"white")){
			DrawRectAll(10, 10, 100, 100, white);
		}else if(!strcmp(buf, L"rec")){
			DrawRect(rec, white);
		}else if(!strcmp(buf, L"back")){
			DrawRect(rec, brack);
		}else if(!strcmp(buf, L"checkf")){
			putxval(GOP->Mode->Info->PixelFormat, 10);
			puts(L"\r\n");
		}else if(!strcmp(buf, L"pstat")){
			pstat();
		}else if(!strcmp(buf, L"ls")){
			ls();
		}else if(!strcmp(buf, L"gui")){
			Gui();
		}else if(!strcmp(buf, L"num")){
			putxval(0x123456, 8);
			puts(L"\r\n");
		}else if(!strcmp(buf, L"cat")){
			cat(L"abc");
		}else if(!strcmp(buf, L"edit")){
			edit(L"abc");
			puts(L"\r\n");
		}else if(!strcmp(buf, L"view")){
			view(L"img");
		}else if(!strcmp(buf, L"ver")){
			putxval(GOP->Mode->Info->VerticalResolution, 8);
			puts(L"\r\n");
		}else if(!strcmp(buf, L"hor")){
			putxval(GOP->Mode->Info->HorizontalResolution, 8);
			puts(L"\r\n");
		}else{
			puts(L"unrecognized command\r\n");
		}
	}
}

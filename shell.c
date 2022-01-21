#include"shell.h"

#define MAX_BUF_SIZE 256
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
		}else if(!strcmp(buf, L"rec")){
			DrawRec(10, 10, 100, 100);
		}else if(!strcmp(buf, L"checkf")){
			putxval(GOP->Mode->Info->PixelFormat, 10);
			puts(L"\r\n");
		}else{
			puts(L"unrecognized command\r\n");
		}
	}
}

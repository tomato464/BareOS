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
		}else{
			puts(L"unrecognized command\r\n");
		}
	}
}

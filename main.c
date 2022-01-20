#include"defines.h"
#include"efi.h"
#include"lib.h"

// for entry poin
// efi_status main( EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *system_table);
void EfiMain(EFI_HANDLE ImageHandle __attribute__ ((unused)), EFI_SYSTEM_TABLE *SystemTable)
{
	CHAR16 buf[256];
	EfiInit(SystemTable);

	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
	puts(L"Hello UEFI!\n");
	while (1){

		get(buf, 256);
/*
		SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn,&key);
		if(key.UnicodeChar != L'\r'){
			str[0] = key.UnicodeChar;
			str[1] = L'\0';
		}else{
			str[0] = L'\r';
			str[1] = L'\n';
			str[2] = L'\0';
		}*/
	}
}

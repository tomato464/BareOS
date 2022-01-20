#include"defines.h"
#include"efi.h"
#include"lib.h"
#include"shell.h"

// for entry poin
// efi_status main( EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *system_table);
void EfiMain(EFI_HANDLE ImageHandle __attribute__ ((unused)), EFI_SYSTEM_TABLE *SystemTable)
{
	EfiInit(SystemTable);
	puts(L"Hello UEFI!\r\n");

	shell();
}

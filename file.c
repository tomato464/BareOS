#include"file.h"

FILE FileList[MAX_FILE_LIST];

EFI_STATUS OpenVolume(EFI_FILE_PROTOCOL **Root)
{
	EFI_STATUS n;
	n = FSP->OpenVolume(FSP, Root);
	return n;
}



EFI_STATUS Read(EFI_FILE_PROTOCOL *this, UINTN *buffer_size, void *buffer)
{
	EFI_STATUS n;
	if(!this){
		puts(L"this is no exist\r\n");
		return 1;
	}
	n = this->Read(this, buffer_size, buffer);
	return n;
}

EFI_STATUS Open(EFI_FILE_PROTOCOL *this, EFI_FILE_PROTOCOL **new, CHAR16 *name, \
				UINT64 mode, UINT64 attribute)
{
	EFI_STATUS n;

	n = this->Open(this, new, name, mode, attribute);

	return n;
}

EFI_STATUS Close(EFI_FILE_PROTOCOL *this)
{
	EFI_STATUS n;
	if(!this){
		return 1;
	}
	n = this->Close(this);
	return n;
}

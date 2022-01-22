#ifndef _FILE_H_
#define _FILE_H_
#include"defines.h"
#include"lib.h"
#include"efi.h"
#include"graphics.h"

#define MAX_FILE_NAME 15
#define	MAX_FILE_BUF 1024
#define MAX_FILE_LIST 16
typedef struct{
	CHAR16 Name[MAX_FILE_NAME + 1];
	bool IsHighlight;
	RECT rect;
} FILE;

extern FILE FileList[MAX_FILE_LIST];

EFI_STATUS OpenVolume(EFI_FILE_PROTOCOL **Root);
EFI_STATUS Open(EFI_FILE_PROTOCOL *this, EFI_FILE_PROTOCOL **new, CHAR16 *name, \
				UINT64 mode, UINT64 attribute);
EFI_STATUS Read(EFI_FILE_PROTOCOL *this, UINTN *buffer_size, void *buffer);
EFI_STATUS Write(EFI_FILE_PROTOCOL *this, UINTN *size, void *buf);
EFI_STATUS Flush(EFI_FILE_PROTOCOL *this);
EFI_STATUS Close(EFI_FILE_PROTOCOL *this);

#endif

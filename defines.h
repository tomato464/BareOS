#ifndef _DEFINES_H_
#define _DEFINES_H_
typedef unsigned long long UINTN;
typedef UINTN EFI_STATUS;
typedef char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef void *  EFI_HANDLE;
typedef unsigned short CHAR16;

typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct{
	CHAR16	ScanCode;
	CHAR16	UnicodeChar;
}EFI_INPUT_KEY;

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL{
	EFI_STATUS	Reset;
	EFI_STATUS	(*OutPutString)(
			struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *this,
			 CHAR16 *string);
	EFI_STATUS func[4];
	EFI_STATUS (*ClearScreen)(
			struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *this);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL{
	EFI_STATUS	Reset;
	EFI_STATUS	(*ReadKeyStroke)(
				struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *this,
				EFI_INPUT_KEY *Key);
	EFI_STATUS	Wait;
}EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct EFI_SYSTEM_TABLE{
// declare just we want to use now(EFI_SIMPLE_TEXT_OUTPUT)
	EFI_TABLE_HEADER	Hdr;
	CHAR16	*FirmwareVender;
	UINT32	FirmwareRevision;
	EFI_HANDLE	ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
	EFI_HANDLE	ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
} EFI_SYSTEM_TABLE;

#endif

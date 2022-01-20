#ifndef _DEFINES_H_
#define _DEFINES_H_
#define NULL (void *) 0
#define bool int
#define true 1
#define false 0
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
typedef	void * EFI_EVENT;
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
	EFI_EVENT	WaitForKey;
}EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct {
	EFI_TABLE_HEADER		Hdr;
	// Tsk priority  2
	EFI_STATUS	_bufT[2];
	// Memory 5
	EFI_STATUS	_bufM[5];
	//Event
	EFI_STATUS	_bufE[2];

	EFI_STATUS	(*WaitForEvent)(	
					UINTN	NumberOfEvents,
					EFI_EVENT	*Event,
					UINTN	*Index);
	EFI_STATUS	_bufEE[3];

	//protocol handler
	EFI_STATUS	_bufP[4];
	void *		Reserved;
	EFI_STATUS	_bufPP[4];

	//Image Services
	EFI_STATUS	_bufI[5];

	//Miscellaneous Services
	EFI_STATUS	_bufMi[2];
	EFI_STATUS	(*SetWatchdogTimer)(
				UINT64 Timeout,
				UINT64 WatchdogCode,
				UINT64 DataSize,
				UINT16 *WatchdogData);
} EFI_BOOT_SERVICES;

typedef struct EFI_SYSTEM_TABLE{
// declare just we want to use now(EFI_SIMPLE_TEXT_OUTPUT)
	EFI_TABLE_HEADER				Hdr;
	CHAR16							*FirmwareVender;
	UINT32							FirmwareRevision;
	EFI_HANDLE						ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL 	*ConIn;
	EFI_HANDLE						ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	EFI_HANDLE						StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*StdErr;
	EFI_STATUS						*RuntimeServices;//not implement
	EFI_BOOT_SERVICES				*BootServices;
} EFI_SYSTEM_TABLE;

#endif

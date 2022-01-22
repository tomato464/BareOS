#ifndef _DEFINES_H_
#define _DEFINES_H_

//////////// data type
#define NULL (void *) 0
typedef unsigned char bool;
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

#define SC_OFS	0x1680
#define SC_ESC	(SC_OFS + 0x0017)

////EFI STATUS CODES
#define EFI_SUCCESS	0
#define EFI_LOAD_ERROR	2
#define EFI_UNSUPPORTED	3

////////////GUID
typedef struct{
	//128bit buffer
	UINT32	buf1;
	UINT16	buf2;
	UINT16	buf3;
	UINT8	buf4[8];
}EFI_GUID;

///Graphics output
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID	\
		{0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, \
			0xd0, 0x80, 0x51, 0x6a}}

//// Simple pointer protocol
#define EFI_SIMPLE_POINTER_PROTOCOL_GUID	\
		{0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, \
			0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID	\
		{0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, \
			0xc9, 0x69, 0x72, 0x3b}}

//////////file system
//file mode
#define EFI_FILE_MODE_READ		0x0000000000000001
#define EFI_FILE_MODE_WRITE		0x0000000000000002
#define EFI_FILE_MODE_CREATE	0x8000000000000000
//file attribute
#define EFI_FILE_READ_ONLY	0x0000000000000001
#define EFI_FILE_HIDDEN		0x0000000000000002
#define EFI_FILE_SYSTEM		0x0000000000000004
#define EFI_FILE_RESERVED	0x0000000000000008
#define EFI_FILE_DIRECTORY	0x0000000000000010
#define EFI_FILE_ARCHIVE	0x0000000000000020
#define EFI_FILE_VALID_ATTR	0x0000000000000037

typedef struct{
	UINT16 Year;
	UINT8	Month;
	UINT8	Day;
	UINT8	Hour;
	UINT8	Minute;
	UINT8	Second;
	UINT8	Pad1;
	UINT32	NanoSecond;
	INT16	TimeZone;
	UINT8	Daylight;
	UINT8	Pad2;
} EFI_TIME;

typedef struct {
	UINT64	Size;
	UINT64	FileSize;
	UINT64	PhisicalSize;
	EFI_TIME	CreateTime;
	EFI_TIME	LastAccessTime;
	EFI_TIME	ModificationTime;
	UINT64	Attribute;
	CHAR16	FileName[];
}EFI_FILE_INFO;

typedef struct EFI_FILE_PROTOCOL{
	UINT64		Revision;
	EFI_STATUS	(*Open)(
				struct EFI_FILE_PROTOCOL *this,
				struct EFI_FILE_PROTOCOL **NewHandle,
				CHAR16	*FileName,
				UINT64	OpenMode,
				UINT64	Attribute);
	EFI_STATUS	(*Close)(
				struct EFI_FILE_PROTOCOL *this);
	EFI_STATUS	_buf1;
	EFI_STATUS	(*Read)(
				struct EFI_FILE_PROTOCOL *this,
				UINTN	*BufferSize,
				void	*Buffer);
	EFI_STATUS	buf2[5];
}EFI_FILE_PROTOCOL;


typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL{
	UINT64			Revision;
	EFI_STATUS 		(*OpenVolume)(
					struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *this,
					EFI_FILE_PROTOCOL	**Root);
}EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;


/////pointer


typedef struct{
	UINT64	ResolutionX;
	UINT64	ResolutionY;
	UINT64	ResolutionZ;
	bool	LeftButton;
	bool	RightButton;
}EFI_SIMPLE_POINTER_MODE;

typedef struct{
	INT32	RelativeMomentX;
	INT32	RelativeMomentY;
	INT32	RelativeMomentZ;
	bool	LeftButton;
	bool	RightButton;
}EFI_SIMPLE_POINTER_STATE;

typedef struct EFI_SIMPLE_POINTER_PROTOCOL{
	EFI_STATUS	(*Reset)(
				struct EFI_SIMPLE_POINTER_PROTOCOL *this,
				bool ExtendedVerification);
	EFI_STATUS	(*GetState)(
				struct EFI_SIMPLE_POINTER_PROTOCOL *this,
				EFI_SIMPLE_POINTER_STATE *State);
	EFI_EVENT	WaitForInput;
	EFI_SIMPLE_POINTER_MODE	*Mode;
}EFI_SIMPLE_POINTER_PROTOCOL;


////graphics

typedef struct {
	UINT8	Blue;
	UINT8	Green;
	UINT8	Red;
	UINT8	Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL_FORMAT;

typedef enum{
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBotMask,
	PixelBltOnly,
	PixelFormatMax,
}EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct{
	UINT32	RedMask;
	UINT32	GreenMask;
	UINT32	BlueMask;
	UINT32	ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct{
	UINT32	Version;
	UINT32	HorizontalResolution;
	UINT32	VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT	PixelFormat;
	EFI_PIXEL_BITMASK	PixelInformation;

	UINT32	PixcelsPerScanLine;
}EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct{
	UINT32	MaxMode;
	UINT32	Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION	*Info;
	UINTN	SizeOfInfo;
	UINTN	FrameBufferBase;
	UINTN	FramBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL{
	EFI_STATUS mode[3];
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE	*Mode;
}EFI_GRAPHICS_OUTPUT_PROTOCOL;

////////////System Table
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
	EFI_STATUS	_bufP[9];

	//Image Services
	EFI_STATUS	_bufI[5];

	//Miscellaneous Services
	EFI_STATUS	_bufMi[2];
	EFI_STATUS	(*SetWatchdogTimer)(
				UINT64 Timeout,
				UINT64 WatchdogCode,
				UINT64 DataSize,
				UINT16 *WatchdogData);

	//DriverSupport
	EFI_STATUS	_bufD[2];

	//open and close protocol
	EFI_STATUS	_bufOC[3];

	//library
	EFI_STATUS	_bufL[2];
	EFI_STATUS	(*LocateProtocol)(
				EFI_GUID *protocol,
				void *Registration,
				void **Interface);

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

#include"lib.h"

void putc(CHAR16 c)
{
	CHAR16 str[2] = L" ";
	str[0] = c;

	SysTbl->ConOut->OutPutString(SysTbl->ConOut, str);
}

void puts(CHAR16 *s)
{
	SysTbl->ConOut->OutPutString(SysTbl->ConOut, s);
}

void putxval(UINT64 val, UINT8 column)
{
	CHAR16 buf[9];

	CHAR16 *p;
	p = &buf[9];
	if(!val && !column){
		column++;
	}
	*p = L'\0';
	p--;
	for(UINT8 i = 0; i < column; i++){
		*p = L"0123456789abcdef"[val & 0x0f];
		p--;
		val = (val >> 4);
	}
	puts(p+1);
	return;
}

CHAR16 getc(void)
{
	UINTN waitidx;
	EFI_INPUT_KEY key;
	SysTbl->BootServices->WaitForEvent(1,
								&(SysTbl->ConIn->WaitForKey),
								&waitidx);
	SysTbl->ConIn->ReadKeyStroke(SysTbl->ConIn, &key);//may cause error

	return key.UnicodeChar;
}

UINT32 gets(CHAR16 *buf, UINT32 buf_size)
{
	UINT32 i;
	for(i = 0; i < buf_size - 1;i++){
		buf[i] = getc();
		putc(buf[i]);
		if(buf[i] == L'\r'){
			putc(L'\n');
			break;
		}
	}
	buf[i] = L'\0';
	return i;
}

int strcmp(const CHAR16 *s1, const CHAR16 *s2)
{
	while(*s1 || *s2){
		if(*s1 != *s2){
			return (*s1 > *s2) ? 1 : -1;
		}
		s1++;
		s2++;
	}
	return 0;
}

void memset(void *p, int n, int size)
{
	UINT8 *start = (UINT8 *)p;
	for(int i = 0; i < size; i++){
		start[i] = n;
	}
}

void Assert(EFI_STATUS stat, CHAR16 *str)
{
	if(!stat){
		return;
	}
	puts(L"\r\n\r\n");
	puts(str);
	puts(L"  ");
	putxval(stat, 8);

	while(1){

	}
}

void strncpy(CHAR16 *buf, const CHAR16 *str, UINT32 size)
{
	UINT32 i;
	for(i = 0; i < size; i++){
		if(str[i] == L'\0'){
			break;
		}
		buf[i] = str[i];
	}
	for(; i < size; i++){
		buf[i] = L'\0';
	}
}

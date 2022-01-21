#include"lib.h"

void putc(CHAR16 c)
{
	CHAR16 str[2] = L" ";
	str[0] = c;

	SysTbl->ConOut->OutPutString(SysTbl->ConOut, str);
}

void puts(CHAR16 *s)
{
	while(*s){
		putc(*s);
		s++;
	}
}

void putxval(UINT64 val, UINT64 column)
{
	 
	if(!val && !column){
		column++;
	}
	CHAR16 p[column + 2];
	p[column + 1] = L'\0';
	while(column || val){
		p[column] = L"0123456789abcdef"[val & 0xf];
		val = val >> 4;
		column--;
	}
	puts(p+1);
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

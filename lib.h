#ifndef _LIB_H_
#define _LIB_H_
#include"defines.h"
#include"efi.h"

void putc(CHAR16 c);
void puts(CHAR16 *s);
void putxval(UINT64 val, UINT8 column);
CHAR16 getc(void);
UINT32 gets(CHAR16 *buf, UINT32 buf_size);
int strcmp(const CHAR16 *s1, const CHAR16 *s2);
void memset(void *p, int n, int size);

#endif

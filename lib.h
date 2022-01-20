#ifndef _LIB_H_
#define _LIB_H_
#include"defines.h"
#include"efi.h"

void putc(CHAR16 c);
void puts(CHAR16 *s);
CHAR16 getc(void);
UINT32 get(CHAR16 *buf, UINT32 buf_size);
int strncmp(const CHAR16 *s1, const CHAR16 *s2);

#endif

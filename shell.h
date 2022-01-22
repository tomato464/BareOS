#ifndef _SHELL_H_
#define _SHELL_H_
#include"defines.h"
#include"efi.h"
#include"lib.h"
#include"graphics.h"
#include"gui.h"
#include"file.h"
extern RECT rec;

void cat(CHAR16 *file_name);
UINT32 ls(void);
void shell(void);

#endif

#ifndef ENCRYP_PNG
#define ENCRYP_PNG

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include "list.h"

void read_png_file(char *filename);

void write_png_file(char *filename);

char BitToChar(Lista *MsgBits);

void process_png_file_hide(Lista *BitsMensagem);

void process_png_file_print(void);

void hide(char *FilenameINPUT, char *FilenameOUTPUT, char *msg);

void print_message(char *filename);

#endif
#pragma once

#include "MySimpleComputer.h"

int bc_get_bigcharpos(unsigned int *big, int x, int y, bool *value);
int bc_set_bigcharpos(unsigned int *big, int x, int y, bool *value);
int bc_printbigchar(unsigned int BIG[2], int x, int y, COLOR col, COLOR col2);
int bc_big_char_write (int fd, unsigned int * BIG, int count);
int bc_bigcharread (int fd, unsigned int * BIG, int need_count, int * count);
void func(COLOR color);

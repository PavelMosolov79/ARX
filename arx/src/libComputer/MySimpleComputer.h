#pragma once

enum COLOR {
	BLACK=0,
	RED=1,
	GREEN=2,
	YELLOW=3,
	BLUE=4,
	PURPLE=5,
	CYAN=6,
	WHITE=7,
};

int mt_clrscr();
int mt_gotoXY(int down, int right);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(COLOR col);
int mt_setbgcolor(COLOR col);
int bc_printA(char str);
int bc_box(int x1, int y1, int x2, int y2);

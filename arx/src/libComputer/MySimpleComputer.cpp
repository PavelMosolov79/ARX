#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "MySimpleComputer.h"

using namespace std;

#define ESC "\033"

int mt_clrscr() {
	printf(ESC "[H" ESC "[J");
	return 0;
}

int mt_gotoXY(int down, int right) {
	printf("\033[%d;%dH", right, down);
	return 0;
}

int mt_getscreensize(int *rows, int *cols) {
	winsize ws;
	if(!ioctl(1, TIOCGWINSZ, &ws)) {
		*rows=ws.ws_col;
		*cols=ws.ws_row;
		return 0;
	}
	return -1;
}

int mt_setfgcolor(COLOR col) {
	printf("\E[3%dm", col);
	return 0;
}

int mt_setbgcolor(COLOR col) {
	printf("\033[48;5;%dm", col);
	return 0;
}

int bc_printA(char str) {
	printf("\033(0%c\033(B", str);
	return 0;
}

void func(COLOR color){
	mt_setfgcolor(color);
    mt_gotoXY(27, 1);
    cout << "Memory";
    mt_gotoXY(66, 1);
    cout << "accumulator";
    mt_gotoXY(69, 2);
    cout << "+9999";
    mt_gotoXY(63, 4);
    cout << "instructionCounter";
    mt_gotoXY(69, 5);
    cout << "+0000";
    mt_gotoXY(67, 7);
    cout << "Operation";
    mt_gotoXY(67, 8);
    cout << "+00 : 00";
    mt_gotoXY(69, 10);
    cout << "Flags";
    mt_gotoXY(69, 11);
    cout << "O Z E V M";
    mt_gotoXY(51, 13);
    cout << "Keys:";
    mt_gotoXY(50, 14);
    cout << "l - load";
    mt_gotoXY(50, 15);
    cout << "s - save";
    mt_gotoXY(50, 16);
    cout << "r - run";
    mt_gotoXY(50, 17);
    cout << "t - step";
    mt_gotoXY(50, 18);
    cout << "i - reset";
    mt_gotoXY(50, 19);
    cout << "F5 - accumulator";
    mt_gotoXY(50, 20);
    cout << "F6 - instructionCounter";
}

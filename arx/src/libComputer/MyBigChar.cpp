#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "MyBigChar.h"
#include "MySimpleComputer.h"


using namespace std;

int bc_box(int x1, int y1, int x2, int y2) {
	for(int i=x1; i<x2;i++) {
			mt_gotoXY(i, y1);
			bc_printA('q');
			mt_gotoXY(i, y2);
			bc_printA('q');
	}
	for(int i=y1; i<y2;i++) {
			mt_gotoXY(x1, i);
			bc_printA('x');
			mt_gotoXY(x2, i);
			bc_printA('x');
	}
	//left up
	mt_gotoXY(x1, y1);
	bc_printA('l');
	//left down
	mt_gotoXY(x1, y2);
	bc_printA('m');
	//right up
	mt_gotoXY(x2, y1);
	bc_printA('k');
	//right down
	mt_gotoXY(x2, y2);
	bc_printA('j');
    mt_gotoXY(50, 50);
	return 0;
}

int bc_get_bigcharpos(unsigned int *big, int x, int y, bool *value) {
	if((x<0)||(x>7)||(y<0)||(y>7)) {
		return -1;
	}
	if(big[int(y/4)]&(1<<(8*(y%4)+(7-x)))) {
		*value = true;
	} else {
		*value = false;
	}
	return 0;
}

int bc_set_bigcharpos(unsigned int *big, int x, int y, bool *value) {
	if((x<0)||(x>7)||(y<0)||(y>7)) {
		return -1;
	}
	if(value) {
		big[int(y/4)] |= (1<<(8*(y%4)+(7-x)));
	} else {
		big[int(y/4)] &= (1<<(8*(y%4)+(7-x)));
	}
	return 0;
}

int bc_printbigchar(unsigned int BIG[2], int x, int y, COLOR col, COLOR col2) {
	mt_setfgcolor(col);
	mt_setbgcolor(col2);
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			mt_gotoXY(x+1+i, y+1+j);
			bool value;
			if(bc_get_bigcharpos(BIG, i, j, &value)) {
				return -1;
			}
			if(value) {
				bc_printA('a');
			} else {
				printf("%c",' ');
			}
		}
	}
/*
	for(int i=0; i<32; i++) {
		if(i%8==0)
			mt_gotoXY(x, y+4 - i/8);
		if((BIG[0]&1)>0)
			bc_printA('a');
		else
			bc_printA(' ');
		BIG[0]>>=1;
	}
	for(int i=0; i<32; i++) {
		if(i%8==0)
			mt_gotoXY(x, y+8 - i/8);
		if((BIG[1]&1)>0)
			bc_printA('a');
		else
			bc_printA(' ');
		BIG[1]>>=1;
	}*/
	printf("\E[0m");
	mt_gotoXY(0, 25);

	return 0;
}

int bc_big_char_write (int fd, unsigned int * BIG, int count) {
        if (write (fd, BIG, count * sizeof(unsigned int))) {
            return (-1);
        }
      return (0);
  }

int bc_bigcharread (int fd, unsigned int * BIG, int need_count, int * count) {
    *count = 0;
    for(int i=0; i<need_count*2; i++) {
        if(read (fd, &BIG[i], sizeof(unsigned int)) == -1) {
            return -1;
        }
        if(!((i+1) % 2)) {
            (*count)++;
        }
    }
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <time.h>

#include "libComputer/MyReadKey.h"
#include "libComputer/MySimpleMemory.h"
#include "libComputer/MyBigChar.h"
#include "libComputer/MySimpleComputer.h"

using namespace std;

int main() {
	srand(time(NULL));
	unsigned int BIGCock[19][2] = {
        {0xC3C3C33C, 0x3CC3C3C3},
		{0x1818F818, 0xFF181818},
		{0xC06C33C, 0xFF603018},
		{0xC03C33C, 0x3CC30303},
		{0xCCCCC0C0, 0xC0C0CFF},
		{0xFCC0C0FF, 0xFC030303},
		{0xFCC0C33C, 0x3CC3C3C3},
		{0xC0603FF, 0x18181818},
		{0x3CC3C33C, 0x3CC3C3C3},
		{0x3FC3C33C, 0x3CC30303},
		{0xC3C3C318, 0xC3C3FFC3},
		{0xFCC3C3FC, 0xFCC3C3C3},
		{0xC0C0C33C, 0x3CC3C0C0},
		{0xC3C3C3FC, 0xFCC3C3C3},
		{0xFCC0C0FF, 0xFFC0C0C0},
		{0xFCC0C0FF, 0xC0C0C0C0},
		{0x18180000, 0x1818FF},
		{0x0, 0xFF},
	};
	mt_clrscr();
	
	int x,y;
	mt_gotoXY(90, 90);
	mt_getscreensize(&x,&y);
	std::cout << x << " " << y;
	memory_init();
    mt_setfgcolor(GREEN);
	
	int current_memory_cell = 0;
	bool is_ui = true;
	keys key;
		
	for(int i=0; i<100; i++){
		memory_set(i, rand()%25666);
	}
		
    do {
        int mem=0;
	    for(int i=0; i<100; i++){
	    	mt_gotoXY(((i%10)*6)+2, (i/10)+2);
	    	memory_get(i, &mem);
	    	if ((i) == current_memory_cell) {
				mt_setbgcolor(RED);
			}
			mt_setfgcolor(GREEN);
			printf("+%x", mem);
			printf("\E[0m");
		}
		

		int value = 0;
		memory_get(current_memory_cell, &value);
		bc_printbigchar(BIGCock[16], 2, 13, WHITE, BLACK);
		if (!(value >> 13) & 1) {
			bc_printbigchar(BIGCock[16], 2, 13, WHITE, BLACK);
		}
		for (int i = 0; i < 4; ++i) {
			int id_symbol = (value & (0xF << (4 * (3 - i)))) >> (4 * (3 - i));
			bc_printbigchar(BIGCock[id_symbol], 2 + 8 * (i + 1) + 1 * (i + 1), 13, WHITE, BLACK);
		}
		
		bc_box(1, 1, 61, 12);
    	bc_box(62, 1, 81, 3);
    	bc_box(62, 4, 81, 6);
    	bc_box(62, 7, 81, 9);
    	bc_box(62, 10, 81, 12);
    	bc_box(1, 13, 48, 22);
    	bc_box(49, 13, 81, 22);
    	func(GREEN);
        
        read_key(&key);
        
        switch(key) {
            case KEY_UP:
            	if (current_memory_cell < 10) {
            		current_memory_cell += 90;
				} else {
					current_memory_cell -= 10;
				}
            	
            	break;
    
            case KEY_RIGHT:
            	if((current_memory_cell + 1) % 10 == 0) {
            		current_memory_cell -= 9;
				} else {
					current_memory_cell += 1;
				}
				
				//set_memory_cell_value();
            	
            	break;
            	
            case KEY_DOWN:
            	if (current_memory_cell >= 90) {
            		current_memory_cell -= 90;
				} else {
					current_memory_cell += 10;
				}
            	
            	break;
            	
            case KEY_LEFT:
            	if(current_memory_cell % 10 == 0) {
            		current_memory_cell += 9;
				} else {
					current_memory_cell -= 1;
				}
            	
				break;
				
            case KEY_L:
            	memory_load("memory.bin");
            	break;
            	
            case KEY_S:
            	cout << "AAAAAAAAAAAAAAA";
            	memory_save("memory.bin");
            	break;
            	
            case KEY_R:
            	break;
            	
            case KEY_T:
            	break;
            	
            case KEY_I:
				break;
				
            case KEY_F5:
            	
            	break;
            	
            case KEY_F6:
				break;
            	
            	break;
            	
            case KEY_OTHER:
				break;
				
            case KEY_ESC:
            	is_ui = false;
				break;
				
			default:
				break;
        }
        
        key = KEY_OTHER;
        
    } while (is_ui);
	printf("\E[0m");
    
//    int fd = open ("BigChar.txt", O_WRONLY);
//	bc_big_char_write (fd, BIGCock[1], 2);
//    bc_bigcharread (fd, BIGCock[1], 2, &x);
//    cout << x;
}

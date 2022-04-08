#include <termios.h>
#include <cstdio>
#include <unistd.h>

#include "MyReadKey.h"

termios save;

int read_key(enum keys *key) {
	fflush(stdout);								// ������� ������ ������	
	terminal_change_regime(0, 30, 0, 0, 0);		// ������ ����� ������ ���������	
    char buffer[5] = "\0";						// ������ �����   
    read(fileno(stdin), buffer, 5);				// ������ ����� � �����   
	terminal_restore();							// ��������������� ��������� ���������
    
    /* ����� � ������ ���� �� ���� ������ ������� */
    if (key == NULL) {
    	return 0;
	}

	/* ��������� ������� ������� */
    if (buffer[0] == '\033') {										// ����������� ������ "escape"
    	if (buffer[1] == '\0') {
    		*key = KEY_ESC;											// ������� "ESC"
		}
		
        else if (buffer[1] == '[') {
        	if (buffer[2] == 'A' && buffer[3] == '\0') {
        		*key = KEY_UP;										// ������� "�����"
			}
			
			else if (buffer[2] == 'B' && buffer[3] == '\0') {
				*key = KEY_DOWN;									// ������� "����"
			}
			
			else if (buffer[2] == 'C' && buffer[3] == '\0') {
				*key = KEY_RIGHT;									// ������� "������"
			}
			
			else if (buffer[2] == 'D' && buffer[3] == '\0') {
				*key = KEY_LEFT;									// ������� "�����"
			}
			
			else if (buffer[2] == '1' && buffer[3] == '5') {
				*key = KEY_F5;										// ������� "F5"
			}
			
			else if (buffer[2] == '1' && buffer[3] == '7') {
				*key = KEY_F6;										// ������� "F6"
			}
			
			else {
				*key = KEY_OTHER;									// ������ �������
			}
		}
	
		else if (buffer[0] == '\n' && buffer[1] == '\0') {
//			*key = KEY_ENTER;										// ������� "enter"
		}
	}
//		 && buffer[1] == '\0'
// && buffer[1] == '\0'
		else {
			if (buffer[0] == 'l') {
				*key = KEY_L;										// ������� "L"
			}
			
			else if (buffer[0] == 's') {
				*key = KEY_S;										// ������� "S"
			}
			
			else if (buffer[0] == 'T' && buffer[1] == '\0') {
				*key = KEY_T;										// ������� "T"
			}
			
			else if (buffer[0] == 'I' && buffer[1] == '\0') {
				*key = KEY_I;										// ������� "I"
			}
			
			else {
				*key = KEY_OTHER;
			}
		}
	
        
    return 0;
}

int terminal_save() {
	/* �������� ��������� ��������� � ������� ������ � ��������� save */
	if (tcgetattr(fileno(stdin), &save)) {
		return -1;
	}
	
    return 0;
}

int terminal_restore() {
	/* ������������� ��������� ��������� �� ���������� ���������� */
	if(tcsetattr(fileno(stdin), TCSAFLUSH, &save)) {
		return -1;
	}
    return 0;
}

int terminal_change_regime(bool regime, unsigned int vtime, unsigned int vmin, bool echo, bool sigint) {
    struct termios current_terminal;
    
    /* �������� ������� ��������� ��������� */
    tcgetattr(fileno(stdin), &current_terminal);

    if (regime) {
    	current_terminal.c_lflag |= ICANON;			// �������� ������������ �����
	} else {
		current_terminal.c_lflag &= ~ICANON;		// ��������� ������������ �����
		
		if (echo) {
			current_terminal.c_lflag |= ECHO;		// �������� ����������� �������� ��������
		} else {
			current_terminal.c_lflag &= ~ECHO;		// ��������� ����������� �������� ��������
		}
		
		if (sigint) {
			current_terminal.c_lflag |= ISIG;		// ��������� �������� � ����������� ������, ���������� � �.�.
		} else {
			current_terminal.c_lflag &= ~ISIG;		// ����������� ��������� �������� � ����������� ������, ���������� � �.�.
		}
		
		current_terminal.c_cc[VTIME] = vtime;		// ������������� ����������� ���������� �������� ��� ��������������� ������
		current_terminal.c_cc[VMIN] = vmin;			// ������������� ����� �������� � ������������ ��� ��������������� ������
	}

    tcsetattr(0, TCSAFLUSH, &current_terminal);

    return 0;
}

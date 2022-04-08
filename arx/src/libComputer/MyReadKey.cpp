#include <termios.h>
#include <cstdio>
#include <unistd.h>

#include "MyReadKey.h"

termios save;

int read_key(enum keys *key) {
	fflush(stdout);								// очистка буфера вывода	
	terminal_change_regime(0, 30, 0, 0, 0);		// мен€ем режим работы терминала	
    char buffer[5] = "\0";						// буффер ввода   
    read(fileno(stdin), buffer, 5);				// чтение ввода в буфер   
	terminal_restore();							// восстанавливаем настройки терминала
    
    /* выход в случае если не была нажата клавиша */
    if (key == NULL) {
    	return 0;
	}

	/* обработка нажатой клавиши */
    if (buffer[0] == '\033') {										// управл€ющий символ "escape"
    	if (buffer[1] == '\0') {
    		*key = KEY_ESC;											// клавиша "ESC"
		}
		
        else if (buffer[1] == '[') {
        	if (buffer[2] == 'A' && buffer[3] == '\0') {
        		*key = KEY_UP;										// клавиша "вверх"
			}
			
			else if (buffer[2] == 'B' && buffer[3] == '\0') {
				*key = KEY_DOWN;									// клавиша "вниз"
			}
			
			else if (buffer[2] == 'C' && buffer[3] == '\0') {
				*key = KEY_RIGHT;									// клавиша "вправо"
			}
			
			else if (buffer[2] == 'D' && buffer[3] == '\0') {
				*key = KEY_LEFT;									// клавиша "влево"
			}
			
			else if (buffer[2] == '1' && buffer[3] == '5') {
				*key = KEY_F5;										// клавиша "F5"
			}
			
			else if (buffer[2] == '1' && buffer[3] == '7') {
				*key = KEY_F6;										// клавиша "F6"
			}
			
			else {
				*key = KEY_OTHER;									// другие клавиши
			}
		}
	
		else if (buffer[0] == '\n' && buffer[1] == '\0') {
//			*key = KEY_ENTER;										// клавиша "enter"
		}
	}
//		 && buffer[1] == '\0'
// && buffer[1] == '\0'
		else {
			if (buffer[0] == 'l') {
				*key = KEY_L;										// клавиша "L"
			}
			
			else if (buffer[0] == 's') {
				*key = KEY_S;										// клавиша "S"
			}
			
			else if (buffer[0] == 'T' && buffer[1] == '\0') {
				*key = KEY_T;										// клавиша "T"
			}
			
			else if (buffer[0] == 'I' && buffer[1] == '\0') {
				*key = KEY_I;										// клавиша "I"
			}
			
			else {
				*key = KEY_OTHER;
			}
		}
	
        
    return 0;
}

int terminal_save() {
	/* передаем настройки терминала в текущий момент в структуру save */
	if (tcgetattr(fileno(stdin), &save)) {
		return -1;
	}
	
    return 0;
}

int terminal_restore() {
	/* устанавливаем настройки терминала из последнего сохранени€ */
	if(tcsetattr(fileno(stdin), TCSAFLUSH, &save)) {
		return -1;
	}
    return 0;
}

int terminal_change_regime(bool regime, unsigned int vtime, unsigned int vmin, bool echo, bool sigint) {
    struct termios current_terminal;
    
    /* получаем текущие настройки терминала */
    tcgetattr(fileno(stdin), &current_terminal);

    if (regime) {
    	current_terminal.c_lflag |= ICANON;			// включаем канонический режим
	} else {
		current_terminal.c_lflag &= ~ICANON;		// выключаем канонический режим
		
		if (echo) {
			current_terminal.c_lflag |= ECHO;		// включаем отображение вводимых символов
		} else {
			current_terminal.c_lflag &= ~ECHO;		// выключаем отображение вводимых символов
		}
		
		if (sigint) {
			current_terminal.c_lflag |= ISIG;		// генераци€ сигналов о прекращении работы, прерывании и т.п.
		} else {
			current_terminal.c_lflag &= ~ISIG;		// отключаение генерации сигналов о прекращении работы, прерывании и т.п.
		}
		
		current_terminal.c_cc[VTIME] = vtime;		// устанавливаем минимальное количество символов дл€ неканонического чтени€
		current_terminal.c_cc[VMIN] = vmin;			// устанавливаем врем€ ожидани€ в децисекундах дл€ неканонического чтени€
	}

    tcsetattr(0, TCSAFLUSH, &current_terminal);

    return 0;
}

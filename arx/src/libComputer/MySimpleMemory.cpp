#include "MySimpleMemory.h"
#include <iostream>

#define OVERFLOW 0
#define DIVISION_ERROR_BY_ZERO 1
#define OUT_MEMORY 2
#define IGNORING_CLOCK_PULSES 3
#define INVALID_COMMAND 4

using namespace std;

int memory[cells];
uint8_t register_flag;

void memory_init() {
    for (int i = 0; i < cells; ++i) {
        memory[i] = 0;
    }
}

void register_init() {
    register_flag = 0;
}

void memory_set(int address, int value) {
    try {
        if (address < 0 || address > cells) {
            throw overflow_error("!!!Going beyond the boundaries of memory!!!");
        }
        memory[address] = value;
	}
	catch (overflow_error &error) {
        register_set(OUT_MEMORY, 1);
        cout << error.what() << "\n";
    }
}

void memory_get(int address, int *value) {
    try {
        if (address < 0 || address > cells) {
            throw overflow_error("!!!Going beyond the boundaries of memory!!!\n");
        }
        *value = memory[address];
	}
	catch (overflow_error &error) {
        register_set(OUT_MEMORY, 1);
        cout << error.what() << "\n";
    }
}

void memory_save(const string &_file_name) {
    ofstream file(_file_name, ios::binary);
    try {
        if (!file.is_open()) {
            throw runtime_error("ERROR! CAN NOT OPEN FILE " + _file_name + "\n");
        }
        file.write((char *) &(memory), sizeof(memory));
	}
	catch (runtime_error &error) {
        cout << error.what() << "\n";
    }
    file.close();
}

void memory_load(const string &_file_name) {
    ifstream file(_file_name, ios::binary);
    try {
        if (!file.is_open()) {
            throw runtime_error("ERROR! CAN NOT OPEN FILE " + _file_name + "\n");
        }
        file.read((char *) &(memory), sizeof(memory));
	}
	catch (runtime_error &error) {
        cout << error.what() << "\n";
    }
    file.close();
}

void register_set(int regist, int value) {
    try {
        if (regist < 0 || regist >= number_of_registers) {
            throw overflow_error("!!!Invalid register value!!!\n");
        }
        if (value != 0 && value != 1) {
            throw invalid_argument("!!!Invalid argument value!!!\n");
        }
		if (value == 1) {
			register_flag |= (1 << regist);
		}
		else {
			register_flag &= ~(1 << regist);
		}
    }
	catch (exception &error) {
        cout << error.what() << "\n";
    }
}

void register_get(int regist, int *value) {
    try {
        if (regist < 0 || regist >= number_of_registers) {
            throw overflow_error("ERROR! INVALID REGISTER\n");
        }
		if (register_flag & (1 << regist)) {
			*value = 1;
		}
		else {
			*value = 0;
		}
    }
	catch (overflow_error &error) {
        cout << error.what() << "\n";
    }
}

void command_encode (int command, int operand, int *value){
    try {
        if (!(command > 0x9 && command < 0x12) && !(command > 0x19 && command < 0x22) && !(command > 0x29 && command < 0x34) && !(command > 0x39 && command < 0x77))
            throw std::invalid_argument("ERROR\tInvalid command") ;
        if ((operand < 0) || (operand >= 128))
            throw std::invalid_argument("ERROR\tInvalid command") ;
        * value =  0 ;
        /* Операнд */
        for (int i = 0 ; i < 7 ;  i++) {
            int bit = (operand >> i) & 1;
            *value |= (bit << i);
        }
        /* Команда */
        for (int i = 0 ; i < 7 ;  i++) {
            int8_t bit = (command >> i) & 1;
            *value |= (bit << (i + 7));
        }
    }
    catch (std::invalid_argument &err){
        std::cout << err.what() << std::endl;
    }

}

void command_decode (int value, int *command, int *operand){
    try {
        int tmpCom = 0, tmpOp  = 0 ;
        if ((value >> 14) & 1)
            throw std::invalid_argument("ERROR\tInvalid command");

        for (int i = 0 ; i < 7 ; i++) {
            int bit = (value >> i) & 1;
            tmpOp |= (bit << i);
        }

        for (int i = 0 ; i < 7 ; i++) {
            int bit = (value >> (i + 7)) & 1;
            tmpCom |= (bit << i);
        }

        if (!(tmpCom > 0x9 && tmpCom < 0x12) && !(tmpCom > 0x19 && tmpCom < 0x22) && !(tmpCom > 0x29 && tmpCom < 0x34) && !(tmpCom > 0x39 && tmpCom < 0x77))
            throw std::invalid_argument("ERROR\tFailed to decode") ;
        if ((tmpOp < 0) || (tmpOp >= 128))
            throw std::invalid_argument("ERROR\tFailed to decode") ;

        * command = tmpCom ;
        * operand = tmpOp ;
    }
    catch (std::invalid_argument &error){
        register_set(INVALID_COMMAND, 1) ;
        std::cout << error.what() << std::endl;
    }

}

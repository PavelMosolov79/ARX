#ifndef LAB_1_MYSIMPLECOMPUTER_H
#define LAB_1_MYSIMPLECOMPUTER_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

static const int cells = 100;
static const int number_of_registers = 5;
extern int memory[cells];
extern uint8_t register_flag;

void memory_init();
void register_init();
void memory_set(int address, int value);
void memory_get(int address, int *value);
void memory_save(const string &_file_name);
void memory_load(const string &_file_name);
void register_set(int regist, int value);
void register_get(int regist, int *value);
void command_encode(int command, int operand, int *value);
void command_decode(int value, int *command, int *operand);

#endif

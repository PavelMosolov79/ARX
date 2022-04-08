#ifndef MYREADKEY_H
#define MYREADKEY_H

#include <termios.h>
#include <cstdio>
#include <unistd.h>

extern termios save;

enum keys {
    KEY_L,
    KEY_S,
    KEY_R,
    KEY_T,
    KEY_I,
    KEY_F5,
    KEY_F6,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_ESC,
    KEY_OTHER
};

int pause(int time);
int read_key(enum keys *key);
int terminal_save();
int terminal_restore();
int terminal_change_regime(bool regime, unsigned int vtime, unsigned int vmin, bool echo, bool sigint);

#endif

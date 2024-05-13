fo#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

void init_stdin();
int getchar_no_block();

#endif
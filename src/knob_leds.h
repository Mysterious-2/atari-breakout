#ifndef SPILED_H
#define SPILED_H

#include <stdint.h>
#include <stdio.h>
#include "mzapo_phys.h"
#include "mzapo_regs.h"

int init_knob_leds();
void show_lives(int lives);
void get_knob(int *moved, int *pressed);

#endif
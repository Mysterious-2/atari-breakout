#ifndef GAME_H
#define GAME_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include "types.h"
#include "font_types.h"
#include "lcd.h"
#include "menus.h"
#include "knob_leds.h"
#include "draw_game.h"
#include "paddle_control.h"

int play_game(menu_item_t difficulty_menu_item, int *score);

#endif
#ifndef MENUS_H
#define MENUS_H

#include <unistd.h>
#include "types.h"
#include "lcd.h"
#include "font_types.h"
#include "knob_leds.h"
#include "keyboard.h"
#include "paddle_control.h"

menu_item_t display_main_menu();
void display_final_screen(int score, int won);

#endif
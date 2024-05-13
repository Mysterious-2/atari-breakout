#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H

#include <stdio.h>
#include "types.h"
#include "font_types.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"

int init_lcd();
void fb_clear();
void fb_draw_pixel(int x, int y, int c);
void fb_update();
int fb_draw_char(int x, int y, int size, int ch, font_descriptor_t *fdsc, int c, int c_bg);
int fb_draw_text(int x, int y, const char *text, font_descriptor_t *fdsc, int c, int c_bg, int scale);

#endif
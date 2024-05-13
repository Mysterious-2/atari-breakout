#ifndef DRAW_GAME_H
#define DRAW_GAME_H

#include "types.h"
#include "lcd.h"

void draw_paddle(Paddle *paddle, uint16_t color);
void draw_ball(Ball *ball, uint16_t color);
void draw_brick(Brick *brick, uint16_t color);

#endif
#include "draw_game.h"

void draw_paddle(Paddle *paddle, uint16_t color)
{
  int x, y;

  for (x = paddle->x; x < paddle->x + paddle->width; x++)
  {
    for (y = paddle->y; y < paddle->y + paddle->height; y++)
    {
      fb_draw_pixel(x, y, color);
    }
  }
}

void draw_ball(Ball *ball, uint16_t color)
{
  int x, y;

  for (x = ball->x; x < ball->x + ball->size; x++)
  {
    for (y = ball->y; y < ball->y + ball->size; y++)
    {
      fb_draw_pixel(x, y, color);
    }
  }
}

void draw_brick(Brick *brick, uint16_t color)
{
  int i, j;

  if (!brick->active)
  {
    return;
  }

  for (i = 0; i < brick->width; i++)
  {
    for (j = 0; j < brick->height; j++)
    {
      fb_draw_pixel(brick->x + i, brick->y + j, brick->color);
    }
  }
}
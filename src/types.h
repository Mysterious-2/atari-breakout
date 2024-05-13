#ifndef BREAKOUT_TYPES_H
#define BREAKOUT_TYPES_H

#include <stdint.h>

#define FB_WIDTH 480
#define FB_HEIGHT 320
#define PADDLE_WIDTH 80
#define PADDLE_HEIGHT 10
#define BALL_SIZE 10
#define BRICK_ROWS 5
#define BRICK_COLS 10
#define BRICK_WIDTH 40
#define BRICK_HEIGHT 20
#define BALL_SPEED 6.0

typedef enum {
    MENU_EASY,
    MENU_NORMAL,
    MENU_HARD,
    MENU_EXIT,
} menu_item_t;

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Paddle;

typedef struct {
  int x;
  int y;
  int size;
  int dx;
  int dy;
} Ball;

typedef struct {
  int x;
  int y;
  int width;
  int height;
  int active;
  int points;
  uint16_t color;
} Brick;

typedef struct {
  uint16_t *pixels;
  int width;
  int height;
} fb_t;

#endif
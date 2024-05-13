#include "game.h"

int ball_collides_with_paddle(Ball *ball, Paddle *paddle, float *new_angle)
{
  if ((ball->x + ball->size > paddle->x && ball->x < paddle->x + paddle->width) &&
      (ball->y + ball->size > paddle->y && ball->y < paddle->y + paddle->height))
  {

    float contact_point = ((float)ball->x - paddle->x) / paddle->width;
    *new_angle = (1 - contact_point) * 3.14 / 2 + 3.14 / 4;

    return 1;
  }

  return 0;
}

int ball_collides_with_brick(Ball *ball, Brick *brick)
{
  if (!brick->active)
    return 0;

  return (ball->x + ball->size > brick->x && ball->x < brick->x + brick->width) &&
         (ball->y + ball->size > brick->y && ball->y < brick->y + brick->height);
}

void init_brick(Brick *brick, int col, int row)
{
  brick->x = col * (BRICK_WIDTH + 5) + 20;
  brick->y = row * (BRICK_HEIGHT + 5) + 35;
  brick->width = BRICK_WIDTH;
  brick->height = BRICK_HEIGHT;
  brick->active = 1;

  int brick_type = rand() % 3;
  switch (brick_type)
  {
  case 0:
    brick->color = 0xF800; // Red
    brick->points = 1;
    break;
  case 1:
    brick->color = 0x07E0; // Green
    brick->points = 2;
    break;
  case 2:
    brick->color = 0x001F; // Blue
    brick->points = 3;
    break;
  }
}

void init_ball_paddle(Paddle *paddle, Ball *ball)
{
  // initialize paddle
  paddle->x = FB_WIDTH / 2 - PADDLE_WIDTH / 2;
  paddle->y = FB_HEIGHT - 30;
  paddle->width = PADDLE_WIDTH;
  paddle->height = PADDLE_HEIGHT;

  // initialize ball
  uint32_t ball_angle = 1.5;
  ball->x = FB_WIDTH / 2;
  ball->y = FB_HEIGHT - PADDLE_HEIGHT - BALL_SIZE - 20;
  ball->size = BALL_SIZE;
  ball->dx = cos(ball_angle) * BALL_SPEED;
  ball->dy = -sin(ball_angle) * BALL_SPEED;
}

void init_game(Paddle *paddle, Ball *ball, Brick bricks[][BRICK_COLS], int *lives, menu_item_t difficulty_menu_item)
{
  int row, col;

  init_ball_paddle(paddle, ball);

  // initialize bricks
  for (row = 0; row < BRICK_ROWS; row++)
  {
    for (col = 0; col < BRICK_COLS; col++)
    {
      init_brick(&bricks[row][col], col, row);
    }
  }

  // set number of lives
  switch (difficulty_menu_item)
  {
  case MENU_NORMAL:
    *lives = 2;
    break;
  case MENU_HARD:
    *lives = 1;
    break;
  default:
    *lives = 3;
    break;
  }
  show_lives(*lives);
}

void update_ball_position(Ball *ball)
{
  ball->x += ball->dx;
  ball->y += ball->dy;
}

void handle_paddle_collision(Ball *ball, Paddle *paddle, float *new_angle)
{
  if (ball_collides_with_paddle(ball, paddle, new_angle))
  {
    ball->dx = cos(*new_angle) * BALL_SPEED;
    ball->dy = -sin(*new_angle) * BALL_SPEED;
  }
}

void handle_brick_collision(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], int *score, int *bricks_left)
{
  for (int row = 0; row < BRICK_ROWS; row++)
  {
    for (int col = 0; col < BRICK_COLS; col++)
    {
      if (ball_collides_with_brick(ball, &bricks[row][col]))
      {
        bricks[row][col].active = 0;
        ball->dy = -ball->dy;
        *score += bricks[row][col].points;

        (*bricks_left)--;
        if (*bricks_left == 0)
        {
          return;
        }
      }
    }
  }
}

void handle_wall_collisions(Ball *ball)
{
  if (ball->x <= 0 || ball->x + ball->size >= FB_WIDTH)
  {
    ball->dx = -ball->dx;
  }
  if (ball->y <= 0)
  {
    ball->dy = -ball->dy;
  }
}

void reset_ball(Ball *ball, int *lives)
{
  (*lives)--;
  show_lives(*lives);

  if (*lives == 0)
  {
    return;
  }

  // Reset the ball position and direction
  ball->x = FB_WIDTH / 2;
  ball->y = FB_HEIGHT - PADDLE_HEIGHT - BALL_SIZE - 20;

  float ball_angle = 1.0;
  ball->dx = cos(ball_angle) * BALL_SPEED;
  ball->dy = -sin(ball_angle) * BALL_SPEED;
}

void draw_game_elements(Brick bricks[BRICK_ROWS][BRICK_COLS], Paddle *paddle, Ball *ball, int *score)
{
  fb_clear();

  for (int row = 0; row < BRICK_ROWS; row++)
  {
    for (int col = 0; col < BRICK_COLS; col++)
    {
      draw_brick(&bricks[row][col], 0xffff);
    }
  }

  draw_paddle(paddle, 0xffff);
  draw_ball(ball, 0xffff);

  char score_text[32];
  sprintf(score_text, "Score: %d", *score);
  fb_draw_text(10, 10, score_text, &font_rom8x16, 0xffff, 0x0, 1);

  fb_update();
}

int play_game(menu_item_t difficulty_menu_item, int *score)
{
  Brick bricks[BRICK_ROWS][BRICK_COLS];
  Paddle paddle;
  Ball ball;
  int lives;
  float new_angle;
  int bricks_left = BRICK_ROWS * BRICK_COLS;

  init_game(&paddle, &ball, bricks, &lives, difficulty_menu_item);

  while (1)
  {
    update_paddle_pos(&paddle);
    update_ball_position(&ball);
    handle_paddle_collision(&ball, &paddle, &new_angle);
    handle_brick_collision(&ball, bricks, score, &bricks_left);
    handle_wall_collisions(&ball);

    if (ball.y > FB_HEIGHT)
    {
      reset_ball(&ball, &lives);
    }

    draw_game_elements(bricks, &paddle, &ball, score);

    if (bricks_left == 0)
    {
      return 1;
    }

    if (lives == 0)
    {
      return 0;
    }
  }
}

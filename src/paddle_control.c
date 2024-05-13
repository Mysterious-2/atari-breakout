#include "paddle_control.h"

int move_paddle_with_keyboard(Paddle *paddle)
{
    int c = getchar_no_block();

    switch (c)
    {
    case 'q':
        exit(0);
    case 'a':
        paddle->x -= 20;
        return 1;
    case 'd':
        paddle->x += 20;
        return 1;
    }

    return 0;
}

void move_paddle_with_knob(Paddle *paddle)
{
    int moved, pressed;
    get_knob(&moved, &pressed);

    if (moved == 1)
    {
        paddle->x -= 20;
    }
    else if (moved == -1)
    {
        paddle->x += 20;
    }
}

void update_paddle_pos(Paddle *paddle)
{
    int moved = move_paddle_with_keyboard(paddle);
    if (!moved)
    {
        move_paddle_with_knob(paddle);
    }

    // limit paddle position to screen edges
    if (paddle->x < 0)
    {
        paddle->x = 0;
    }
    if (paddle->x > FB_WIDTH - PADDLE_WIDTH)
    {
        paddle->x = FB_WIDTH - PADDLE_WIDTH;
    }
}
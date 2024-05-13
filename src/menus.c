#include "menus.h"

char *menu_items[] = {"Easy", "Normal", "Hard", "Exit Game"};
const int menu_items_count = 4;

void draw_main_menu_items(int selected_idx)
{
    uint16_t color, color_bg;

    fb_clear();

    int next_x = fb_draw_text(50, 20, "SNAKE", &font_rom8x16, 0xFFFF, 0x0000, 4);
    fb_draw_text(next_x, 20, "APO", &font_rom8x16, 31 << 11, 0x0000, 4);

    for (int i = 0; i < menu_items_count; i++)
    {
        color = i == selected_idx ? 0xFFFF : 0x7BEF;
        color_bg = i == selected_idx ? 0x7BEF : 0x0000;
        fb_draw_text(100, 100 + 40 * i, menu_items[i], &font_rom8x16, color, color_bg, 2);
    }

    fb_update();
}

void get_user_input(int *pressed, int *selected_index)
{
    int moved;
    int c;

    get_knob(&moved, pressed);
    c = getchar_no_block();

    if (moved == -1 || c == 's')
    {
        *selected_index = (*selected_index + 1) % menu_items_count;
    }
    else if (moved == 1 || c == 'w') 
    {
        *selected_index = (*selected_index - 1) % menu_items_count;
        if (*selected_index < 0)
        {
            *selected_index = menu_items_count - 1;
        }
    }

    *pressed = *pressed || c == ' ';
}

menu_item_t display_main_menu()
{
    int prev_index = -1;
    int selected_index = 0;
    int pressed;

    while (1)
    {
        get_user_input(&pressed, &selected_index);

        if (pressed)
        {
            return (menu_item_t)selected_index;
        }

        if (selected_index != prev_index)
        {
            draw_main_menu_items(selected_index);
            prev_index = selected_index;
        }

        usleep(1000);
    }
}

void display_final_screen(int score, int won)
{
    char score_text[50];
    int moved, pressed = 0;

    sprintf(score_text, "Final Score: %d", score);

    fb_clear();
    fb_draw_text(100, 50, won ? "You Win" : "Game Over", &font_rom8x16, 0xFFFF, 0x0, 4);
    fb_draw_text(100, 140, score_text, &font_rom8x16, 0xFFFF, 0x0, 2);
    fb_draw_text(100, 180, "Main Menu", &font_rom8x16, 0xFFFF, 0x7BEF, 2);
    fb_update();

    while (!pressed)
    {
        get_knob(&moved, &pressed);
        if (getchar_no_block() == ' ')
        {
            break;
        }
    }
}
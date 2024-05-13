#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"

#include "lcd.h"
#include "knob_leds.h"
#include "keyboard.h"
#include "game.h"
#include "menus.h"

int main(int argc, char *argv[])
{
  // Serialize execution of applications
  if (serialize_lock(1) <= 0)
  {
    printf("System is occupied\n");

    if (1)
    {
      printf("Waiting\n");
      serialize_lock(0);
    }
  }

  printf("game started\n");

  srand(time(NULL));

  // setup peripherals
  if (init_lcd())
  {
    printf("Failed to initialize LCD\n");
    return -1;
  }

  if (init_knob_leds())
  {
    printf("Failed to initialize LEDs\n");
    return -1;
  }

  init_stdin();

  // play game
  while (1)
  {
    menu_item_t selected_item = display_main_menu();

    if (selected_item == MENU_EXIT)
    {
      break;
    }

    int score = 0;
    int won = play_game(selected_item, &score);

    display_final_screen(score, won);
    usleep(1000 * 200); // 200 ms debounce
  }

  // Release the lock
  serialize_unlock();

  return 0;
}

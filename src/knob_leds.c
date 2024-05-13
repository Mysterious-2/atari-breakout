#include "knob_leds.h"

const int LED_PRESETS[] = {0b0, 0b1, 0b11, 0b111};
volatile void *spiled_base;
int last_knob_val = -1;

int init_knob_leds()
{
    spiled_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (spiled_base == NULL)
    {
        printf("failed to map knob & LED physical address\n");
        return -1;
    }

    return 0;
}

void show_lives(int lives)
{
    *(volatile uint32_t *)(spiled_base + SPILED_REG_LED_LINE_o) = LED_PRESETS[lives];
}

void get_knob_raw(int *value, int *pressed)
{
    uint32_t raw = *(volatile uint32_t *)(spiled_base + SPILED_REG_KNOBS_8BIT_o);
    *value = 255 - (raw & 0xFF);
    *pressed = (raw >> 24) & 1;
}

void get_knob(int *moved, int *pressed)
{
    int val;
    get_knob_raw(&val, pressed);

    int knob_diff = val - last_knob_val;

    if (knob_diff > 127)
    {
        knob_diff -= 256;
    }
    else if (knob_diff < -127)
    {
        knob_diff += 256;
    }

    if (knob_diff > 2)
    {
        *moved = 1;
        last_knob_val = val;
    }
    else if (knob_diff < -2)
    {
        *moved = -1;
        last_knob_val = val;
    }
    else
    {
        *moved = 0;
    }
}
  #include "lcd.h"

  uint16_t fb_pixels[FB_WIDTH * FB_HEIGHT];
  volatile void *parlcd_base;

  int init_lcd()
  {
    parlcd_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_base == NULL)
    {
      printf("failed to map LCD physical address\n");
      return -1;
    }

    return 0;
  }

  void fb_clear()
  {
    int l;

    for (l = 0; l < FB_WIDTH * FB_HEIGHT; l++)
    {
      fb_pixels[l] = 0;
    }
  }

  void fb_draw_pixel(int x, int y, int c)
  {
    if (x < 0 || x >= FB_WIDTH || y < 0 || y >= FB_HEIGHT)
    {
      return;
    }

    fb_pixels[x + y * FB_WIDTH] = c;
  }

  void fb_update()
  {
    int l = 0;

    *(volatile uint16_t *)(parlcd_base + PARLCD_REG_CMD_o) = 0x2c; // reset position
    for (l = 0; l < FB_WIDTH * FB_HEIGHT; l += 2)
    {
      *(volatile uint32_t *)(parlcd_base + PARLCD_REG_DATA_o) = fb_pixels[l] | (fb_pixels[l + 1] << 16); // write color (RGB565)
    }
  }

  void draw_char_pixel(int x, int y, int size, int c)
  {
    for (int h_repeat = 0; h_repeat < size; h_repeat++)
    {
      for (int v_repeat = 0; v_repeat < size; v_repeat++)
      {
        fb_draw_pixel(
            x + h_repeat,
            y + v_repeat,
            c);
      }
    }
  }

  int calculate_character_properties(int ch, font_descriptor_t *fdsc, int *ch_width, uint16_t **pbits, int *ch_byte_count)
  {
    // index too low
    if (ch < fdsc->firstchar)
    {
      return 0;
    }
    ch -= fdsc->firstchar;

    // index too high
    if (ch >= fdsc->size)
    {
      return 0;
    }

    if (fdsc->width != NULL)
    {
      // variable width
      *ch_width = fdsc->width[ch];
    }
    else
    {
      // fixed width
      *ch_width = fdsc->maxwidth;
    }

    *ch_byte_count = ((*ch_width + 15) / 16) * fdsc->height;

    if (fdsc->offset != NULL)
    {
      // offsets provided
      *pbits = fdsc->bits + fdsc->offset[ch];
    }
    else
    {
      // calculate offset
      *pbits = fdsc->bits + ch * (*ch_byte_count);
    }

    return 1;
  }

  int fb_draw_char(int x, int y, int size, int ch, font_descriptor_t *fdsc, int c, int c_bg)
  {
    uint16_t *pbits;
    int ch_width;
    int ch_byte_count;
    int written_rows = 0, written_cols = 0;
    int byte_offset, bit_offset;
    uint8_t bit;

    if (!calculate_character_properties(ch, fdsc, &ch_width, &pbits, &ch_byte_count))
    {
      return 0;
    }

    for (byte_offset = 0; byte_offset < ch_byte_count; byte_offset++)
    {
      for (bit_offset = 7; bit_offset >= 0; bit_offset--)
      {
        bit = *(pbits + byte_offset) >> (bit_offset + 8) & 0x01;

        draw_char_pixel(x + written_cols * size, y + written_rows * size, size, bit ? c : c_bg);

        written_cols = (written_cols + 1) % ch_width;
        if (written_cols == 0)
        {
          written_rows += 1;
        }
      }
    }

    return ch_width * size;
  }

  int fb_draw_text(int x, int y, const char *text, font_descriptor_t *fdsc, int c, int c_bg, int scale)
  {
    int ch_width;

    while (*text)
    {

      ch_width = fb_draw_char(x, y, scale, *text, fdsc, c, c_bg);
      x += ch_width;
      text++;
    }

    return x;
  }
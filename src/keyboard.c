#include "keyboard.h"

void init_stdin()
{
  struct termios old_tio, new_tio;

  tcgetattr(STDIN_FILENO, &old_tio);
  cfmakeraw(&new_tio);
  new_tio.c_oflag &= ~OPOST;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

int getchar_no_block()
{
  fd_set readfds;
  struct timeval tv;
  int res;
  char c;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  res = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
  if (res > 0)
  {
    if (FD_ISSET(STDIN_FILENO, &readfds))
    {
      read(STDIN_FILENO, &c, 1);
      return c;
    }
  }

  return 0;
}

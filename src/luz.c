#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include <math.h>
#include <string.h>
#include <curses.h>

void cast_light(int radius, int cols, int **map, int rows, posicao_player *player)
{

  for (int i = 0; i < 360; i += 1)
  {
    double dx = cos(i * M_PI / 180.0);
    double dy = sin(i * M_PI / 180.0);
    int x = (int)player->x;
    int y = (int)player->y;
    for (int j = 1; j <= radius; j++)
    {
      if (x < 0 || y < 0 || x >= cols || y >= rows)
      {
        break;
      }
      x = (int)(player->x + dx * j);
      y = (int)(player->y + dy * j);
      if (x < 0 || y < 0 || x >= cols || y >= rows)
      {
        break;
      }
      double distance = sqrt((x - player->x) * (x - player->x) + (y - player->y) * (y - player->y));
      if (distance > radius)
      {
        break;
      }
      int cx = (int)player->x;
      int cy = (int)player->y;
      int delta_x = abs(x - cx);
      int delta_y = abs(y - cy);
      int sign_x = cx < x ? 1 : -1;
      int sign_y = cy < y ? 1 : -1;
      int error = delta_x - delta_y;
      bool blocked = false;
      while (cx != x || cy != y)
      {
        if (map[cy][cx] == '#' || map[cy][cx] == '*' || map[cy][cx] == '/')
        {
          blocked = true;
          break;
        }
        int error2 = error * 2;
        if (error2 > -delta_y)
        {
          error -= delta_y;
          cx += sign_x;
        }
        if (error2 < delta_x)
        {
          error += delta_x;
          cy += sign_y;
        }
      }
      if (blocked)
      {
        break;
      }
      
      if (map[y][x] == '#')
      {
        attron(COLOR_PAIR(5));
        mvaddch(y, x, '#');
        attroff(COLOR_PAIR(5));
      }
      else if (map[y][x] == '*')
      {
        attron(COLOR_PAIR(3));
        mvaddch(y, x, '*');
        attroff(COLOR_PAIR(3));
      }
      else if (map[y][x] == '/')
      {
        attron(COLOR_PAIR(3));
        mvaddch(y, x, '/');
        attroff(COLOR_PAIR(3));
      }
      else if (map[y][x] == 't')
      {
        attron(COLOR_PAIR(6));
        mvaddch(y, x, 't');
        attroff(COLOR_PAIR(6));
      }
      else
      {
        attron(COLOR_PAIR(1));
        mvaddch(y, x, '.');
      }
    }
  }
}

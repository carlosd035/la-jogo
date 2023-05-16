#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"

void gerar_player(int rows, int cols, int **map,posicao_player* player,bool *p_place)
{

  if (*p_place == 0)
  {
    while (1) /// gerar random o "@"
    {
      player->y = rand() % rows;
      player->x = rand() % cols;
      if (map[player->y][player->x] == ' ')
      {
        break;
      }
    }
    *p_place = 1;
  }
  attron(COLOR_PAIR(4));
  mvaddch(player->y, player->x, '@');
  attroff(COLOR_PAIR(4));
}

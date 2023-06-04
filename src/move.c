#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"



void movimentacao(int c, int **map, posicao_player* player)
{
  //switch (c)
  //{
  //case 'w':
  //  if (map[player->y - 1][player->x] != '#' && map[player->y - 1][player->x] != '/')
  //    player->y--;
  //  break;
  //case 's':
  //  if (map[player->y + 1][player->x] != '#' && map[player->y + 1][player->x] != '/')
  //    player->y++;
  //  break;
  //case 'a':
  //  if (map[player->y][player->x - 1] != '#' && map[player->y][player->x - 1] != '/')
  //    player->x--;
  //  break;
  //case 'd':
  //  if (map[player->y][player->x + 1] != '#' && map[player->y][player->x + 1] != '/')
  //    player->x++;
  //  break;
  //default:
  //
  //  break;
  //}
//
  switch (c)
  {
  case '8':
    if (map[player->y - 1][player->x] != '#' && map[player->y - 1][player->x] != '/')
      player->y--;
    break;
  case '2':
    if (map[player->y + 1][player->x] != '#' && map[player->y + 1][player->x] != '/')
      player->y++;
    break;
  case '4':
    if (map[player->y][player->x - 1] != '#' && map[player->y][player->x - 1] != '/')
      player->x--;
    break;
  case '6':
    if (map[player->y][player->x + 1] != '#' && map[player->y][player->x + 1] != '/')
      player->x++;
    break;
  default:
  
    break;
  }
}

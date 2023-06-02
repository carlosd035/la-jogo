#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"

void check_w(posicao_player*player,int **map,int c,bool *w_on){

    if (map[player->y][player->x]== '!'&& c == 'b'){
          map[player->y][player->x] = ' ';
          *w_on = 1 ; 
    }


    
}

void weapon(int rows, int cols, int **map, posicao_player *player,bool *w_place,posicao_arma*w,int c,bool *w_on)
{
  if (*w_place == 0)
  {
    for (int i = 0; i < 4; i++)
    {
      do
      {
        // Gerar posição aleatória
        w->wy = rand() % (rows - 2) + 1; // para não gerar na primeira nem na última linha
        w->wx = rand() % (cols - 2) + 1; // para não gerar na primeira nem na última coluna
      } while (map[w->wy][w->wx] != ' ');

      map[w->wy][w->wx] = '!';
    }

    *w_place = 1;
  }

  check_w(player,map,c,w_on);
}

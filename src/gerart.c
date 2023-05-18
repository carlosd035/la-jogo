#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"
#include "corredores.h"

void check_t (int rows, int cols, int **map, int c,int *level,bool*p_place,int *r_place,posicao_player* player,posicao_t *t,bool*t_place,bool *a_place,bool *f_place){
  if (player->y == t->ty && player->x == t->tx && c == 'm')
  { 
    *r_place = 0;
    *t_place = 0;
    *a_place = 0;
    *p_place = 0;
    *f_place = 0 ;

    dungeon_gen(rows, cols, map,r_place);

    *level = *level +1;
  }
}

void gerar_t(int rows, int cols, int **map, int c,int *level,bool*p_place,int *r_place,posicao_player* player,posicao_t *t,bool *t_place,bool *a_place,bool *f_place)
{

  if (*t_place == 0)
  {

    do
    {
      // gerar t aleatoriamente
      t-> ty = rand() % rows - 1; // para não gerar na última linha
      t-> tx = rand() % cols;
    } while (map[t->ty][t->tx] != ' ');

    *t_place = 1;
  }
  map[t->ty][t->tx] = 't';
  
  check_t (rows,cols,map,c,level,p_place,r_place,player,t,t_place,a_place,f_place);
}



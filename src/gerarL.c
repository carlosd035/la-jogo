#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"
#include "corredores.h"

void check_l (int rows, int cols, int **map, int c,int *level,bool*p_place,int *r_place,posicao_player* player,posicao_t *t,bool*t_place,bool *a_place,bool *f_place,bool *v_place,bool*w_place){
  if (player->y == t->ty && player->x == t->tx && c == 'l')
  { 
    *r_place = 0;
    *t_place = 0;
    *a_place = 0;
    *p_place = 0;
    *f_place = 0;
    *v_place = 0;
    *w_place = 0;

    dungeon_gen(rows, cols, map,r_place);

    *level = *level +1;
  }
}

void gerar_l(int rows, int cols, int **map, int c, int *level, bool *p_place, int *r_place, posicao_player *player, posicao_t *t, bool *t_place, bool *a_place, bool *f_place,bool *v_place,bool *w_place) {
    if (*t_place == 0) {
        do {
            // Gerar posição aleatória para 'l'
            t->ty = rand() % (rows - 1);  // Ajustado para gerar entre 0 e rows - 2
            t->tx = rand() % cols;
        } while (map[t->ty][t->tx] != ' ');

        *t_place = 1;
    }
    map[t->ty][t->tx] = 'L';

    check_l(rows, cols, map, c, level, p_place, r_place, player, t, t_place, a_place, f_place,v_place,w_place);
}

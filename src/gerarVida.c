#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"



void life(int *vida, posicao_player *player, int **map, int c,posicao_vida *v,int rows,int cols) {
  if (map[player->y][player->x] == '+' && c == 'v') {
    *vida += 10;
    map[player->y][player->x] = ' ';
      do {
        v->vy = rand() % (rows - 1); // Alterado para gerar valores até rows - 1
        v->vx = rand() % cols;
      } while (map[v->vy][v->vx] != ' ');
      
      map[v->vy][v->vx] = '+';
  }
}

void g_vida(int rows, int cols, int **map, int c, posicao_player *player, bool *v_place, int *vida, posicao_vida *v) {
  if (*v_place == 0) {
    for (int i = 0; i < 13; i++) {
      do {
        v->vy = rand() % (rows - 1); // Alterado para gerar valores até rows - 1
        v->vx = rand() % cols;
      } while (map[v->vy][v->vx] != ' ');
      
      map[v->vy][v->vx] = '+';
    }
    *v_place = 1;
  }
  
  life(vida, player, map, c,v,rows,cols);
}

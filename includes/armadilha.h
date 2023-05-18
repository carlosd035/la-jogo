#ifndef __ARMADILHA_H__
#define __ARMADILHA_H__

void check_armadilha(int *vida, posicao_player *player, int rows, int cols,int **map);
void check_vida2(int *vida, int rows, int cols);
void trap(int rows, int cols, int **map, bool *f_place, posicao_armadilha *f, int *vida, posicao_player *player);

#endif
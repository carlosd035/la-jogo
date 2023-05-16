#ifndef __ARMADILHA_H__
#define __ARMADILHA_H__


void check_armadilha(int rows, int cols, int *vida, int *level,posicao_player *player,posicao_armadilha *a);
void armadilha(int rows, int cols, int **map, int *vida, posicao_player *player, bool *a_place, int *level,posicao_armadilha *a);
#endif
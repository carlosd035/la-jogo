#ifndef __MONSTRO_H__
#define __MONSTRO_H__

void check_vida(int *vida, int rows, int cols);
void monster(int rows, int cols, int **map, int *vida, posicao_player *player, bool *a_place,posicao_monstro *a);
#endif
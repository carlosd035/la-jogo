#ifndef __GERARVIDA_H__
#define __GERARVIDA_H__


void g_vida(int rows, int cols, int **map, int c,posicao_player* player,bool *v_place,int *vida,posicao_vida *v);
void life(int *vida, posicao_player *player, int **map, int c,posicao_vida *v,int rows,int cols);

#endif
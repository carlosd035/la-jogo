#ifndef __gerart_H__
#define __gerart_H__


void gerar_t(int rows, int cols, int **map, int c,int *level,bool*p_place,int *r_place,posicao_player* player,posicao_t* t,bool *t_place,bool *a_place);

void check_t (int rows, int cols, int **map, int c,int *level,bool*p_place,int *r_place,posicao_player* player,posicao_t *t,bool*t_place,bool *a_place);
#endif
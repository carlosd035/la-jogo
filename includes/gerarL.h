#ifndef __GERARL_H__
#define __GERARL_H__


void gerar_l(int rows, int cols, int **map, int c, int *level, bool *p_place, int *r_place, posicao_player *player, posicao_t *t, bool *t_place, bool *a_place, bool *f_place,bool *v_place,bool *w_place) ;
void check_l (int rows, int cols, int **map, int c,int *level,bool*p_place,int *r_place,posicao_player* player,posicao_t *t,bool*t_place,bool *a_place,bool *f_place,bool *v_place,bool *w_place);

#endif
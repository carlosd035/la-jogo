#ifndef __CORREDORES_H__
#define __CORREDORES_H__

int dungeon_gen(int rows, int cols, int **map,int *r_place);
void generate_room(int rows, int cols, int **map, int *r_place);
bool check_colisao(int **map, int y, int x);
void fill_borders(int rows, int cols, int **map);


#endif
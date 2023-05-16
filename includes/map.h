#ifndef __MAP_H__
#define __MAP_H__

int ** criarMatriz(int rows, int cols);

void guarda_valores(int rows, int cols, int ** map);

int dungeon_draw(int rows, int cols, int ** map);



#endif
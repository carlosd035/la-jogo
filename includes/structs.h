#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct posicao_p
{
  int y;
  int x;
} posicao_player;


typedef struct posicao_tt
{

  int ty;
  int tx; // coordenadas do t
} posicao_t;


typedef struct posicao_m
{
  int ay;
  int ax;

} posicao_monstro ;

typedef struct posicao_a
{
  int fy;
  int fx;
} posicao_armadilha;

typedef struct posicao_v
{
  int vy;
  int vx;
} posicao_vida;

typedef struct posicao_arm
{
  int wy;
  int wx;
} posicao_arma;




#define M_PI 3.14159265358979323846

#endif
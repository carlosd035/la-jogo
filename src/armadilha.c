#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"



void check_vida2(int *vida, int rows, int cols)
{
  if (*vida <= 0)
  {
    clear();                                          
    attron(A_BOLD);                                 
    mvprintw(rows / 2, (cols - 18) / 2, "GAME OVER"); 
    attroff(A_BOLD);                                  
    refresh();                                     
    getch();                                          
    endwin();                                         
    exit(0);                                          
  }
}

void check_armadilha(int *vida, posicao_player *player, int rows, int cols,int **map)
{  
  if (map[player->y][player->x] == '*')
  {
    
    *vida = *vida - 2;
    check_vida2(vida, rows, cols);
  }
}

void trap(int rows, int cols, int **map, bool *f_place, posicao_armadilha *f, int *vida, posicao_player *player)
{
  if (!*f_place)
  {
    for (int i = 0; i < 25; i++)
    {
      do
      {
        // Gerar posição aleatória
        f->fy = rand() % (rows - 2) + 1; // para não gerar na primeira nem na última linha
        f->fx = rand() % (cols - 2) + 1; // para não gerar na primeira nem na última coluna
      } while (map[f->fy][f->fx] != ' ');

      map[f->fy][f->fx] = '*';
    }

    *f_place = true;
  }

  check_armadilha(vida, player, rows, cols,map);
}

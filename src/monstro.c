#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"
void check_vida(int *vida, int rows, int cols)
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

void monster(int rows, int cols, int **map, int *vida, posicao_player *player, bool *a_place, posicao_monstro *a)
{

  // Verificar se os monstros já foram colocados no mapa
  if (*a_place == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      do
      {
        // Gerar posições iniciais aleatórias
        a[i].ay = rand() % (rows - 2); // para não gerar na última linha
        a[i].ax = rand() % cols - 2;
      } while (map[a[i].ay][a[i].ax] != ' ');

      map[a[i].ay][a[i].ax] = 'M';
    }

    *a_place = 1;
  }

  // Atualizar a posição de cada monstro
  for (int i = 0; i < 10; i++)
  {
    map[a[i].ay][a[i].ax] = ' ';

    int direction = 0;
    int distanceX = abs(player->x - a[i].ax);
    int distanceY = abs(player->y - a[i].ay);

    if (distanceX + distanceY <= 9)
    {
      if (player->x < a[i].ax)
        direction = 2; // Esquerda
      else if (player->x > a[i].ax)
        direction = 3; // Direita
      else if (player->y < a[i].ay)
        direction = 0; // Cima
      else if (player->y > a[i].ay)
        direction = 1; // Baixo

      if (distanceX <= 1 && distanceY <= 1)
      {
        (*vida)--;
        check_vida(vida, rows, cols);
      }
    }
    else
    {
      direction = rand() % 4;
    }

    int next_ay = a[i].ay;
    int next_ax = a[i].ax;

    if (direction == 0)
      next_ay--;
    else if (direction == 1)
      next_ay++;
    else if (direction == 2)
      next_ax--;
    else if (direction == 3)
      next_ax++;

    if (next_ay >= 0 && next_ay < rows && next_ax >= 0 && next_ax < cols &&
        map[next_ay][next_ax] == ' ' && (next_ay != player->y || next_ax != player->x))
    {
      a[i].ay = next_ay;
      a[i].ax = next_ax;
    }

    map[a[i].ay][a[i].ax] = 'M';
  }
}
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "structs.h"

void check_armadilha(int rows, int cols, int *vida, int *level,posicao_player *player,posicao_armadilha *a)
{
  if (player->y == a->ay && player->x == a->ax)
  {
    *vida = *vida - 25;
    if (*vida <= 0)
    {
      clear();                                          // Limpa a tela
      attron(A_BOLD);                                   // Ativa o atributo de texto A_BOLD
      mvprintw(rows / 2, (cols - 18) / 2, "GAME OVER"); // Exibe a mensagem centralizada
      attroff(A_BOLD);                                  // Desativa o atributo de texto A_BOLD
      refresh();                                        // Atualiza a tela
      getch();                                          // Aguarda a entrada do usuário
      endwin();                                         // Restaura as configurações do terminal
      exit(0);                                          // Encerra o programa
    }
  }
  mvprintw(rows, 0, "LEVEL: %d  VIDA: %d", *level, *vida);
}

void armadilha(int rows, int cols, int **map, int *vida, posicao_player *player, bool *a_place, int *level,posicao_armadilha *a)
{

  if (*a_place == 0)
  {
    do
    {
      // gerar t aleatoriamente
      a->ay = rand() % rows - 1; // para não gerar na última linha
      a->ax = rand() % cols;
    } while (map[a->ay][a->ax] != ' ');

    *a_place = *a_place +1;
  }
  attron(COLOR_PAIR(2));
  mvaddch(a->ay, a->ax, '*');
  map[a->ay][a->ax] = '*';
  attroff(COLOR_PAIR(2));
  check_armadilha(rows, cols, vida,level,player,a);
}
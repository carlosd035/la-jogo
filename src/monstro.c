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

void monster(int rows, int cols, int **map, int *vida, posicao_player *player, bool *a_place, posicao_monstro *a)
{
  if (!*a_place)
  {
    do
    {
      // Gerar posições iniciais aleatórias
      a->ay = rand() % (rows - 1); // para não gerar na última linha
      a->ax = rand() % cols;
    } while (map[a->ay][a->ax] != ' ');

    *a_place = true;
  }

  map[a->ay][a->ax] = 'M';

  int direction = 0;

  // Verificar se o jogador está dentro do raio de visão da armadilha
  int distanceX = abs(player->x - a->ax);
  int distanceY = abs(player->y - a->ay);

  if (distanceX + distanceY <= 9)
  {
    // Determinar a direção para perseguir o jogador
    if (player->x < a->ax)
      direction = 2; // Esquerda
    else if (player->x > a->ax)
      direction = 3; // Direita
    else if (player->y < a->ay)
      direction = 0; // Cima
    else if (player->y > a->ay)
      direction = 1; // Baixo

    // Se o monstro já tocou o jogador, reduzir a vida do jogador se ele estiver dentro do raio de 2 células
    if (distanceX <= 1 && distanceY <= 1)
    {
      (*vida)--;
      check_vida(vida, rows, cols);
    }
  }
  else
  {
    // Escolher uma direção aleatória
    direction = rand() % 4;
  }

  int next_ay = a->ay;
  int next_ax = a->ax;

  if (direction == 0)
    next_ay--;
  else if (direction == 1)
    next_ay++;
  else if (direction == 2)
    next_ax--;
  else if (direction == 3)
    next_ax++;

  // Verificar se a próxima posição está dentro dos limites, não é uma parede e não é o jogador
  if (next_ay >= 0 && next_ay < rows && next_ax >= 0 && next_ax < cols &&
      map[next_ay][next_ax] == ' ' && (next_ay != player->y || next_ax != player->x))
  {
    // Atualizar a posição do monstro
    map[a->ay][a->ax] = ' '; // Limpar a posição atual
    a->ay = next_ay;
    a->ax = next_ax;
  }

  map[a->ay][a->ax] = 'M';
}

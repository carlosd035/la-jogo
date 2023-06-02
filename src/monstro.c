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
/*
void initialize_monsters(posicao_monstro a[]) {
  for (int i = 0; i < 7; i++) {
    a[i].vidam = 100;
  }
}


void attack_player(posicao_player *player, posicao_monstro a[], int **map)
{


  // Verificar a posição do jogador em relação aos monstros
  for (int i = 0; i < 7; i++)
  {
    int distance = abs(player->x - a[i].ax) + abs(player->y - a[i].ay);

    if (distance <= 1)
    {
      a[i].vidam -= 15;
    }

    // Verificar se o monstro foi derrotado
    if (a[i].vidam <= 0)
    {
      // Remover o monstro do mapa
      map[a[i].ay][a[i].ax] = ' ';
    }
  }
}
*/
void monster(int rows, int cols, int **map, int *vida, posicao_player *player, bool *a_place, posicao_monstro *a)
{
  // Verificar se os monstros já foram colocados no mapa
  if (!*a_place)
  {
    for (int i = 0; i < 7; i++)
    {
      do
      {
        // Gerar posições iniciais aleatórias
        a[i].ay = rand() % (rows - 1); // para não gerar na última linha
        a[i].ax = rand() % cols;
      } while (map[a[i].ay][a[i].ax] != ' ');

      map[a[i].ay][a[i].ax] = 'M';
    }

    *a_place = true;
  }

  // Atualizar a posição de cada monstro
  for (int i = 0; i < 7; i++)
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

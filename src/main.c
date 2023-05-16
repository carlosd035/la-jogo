
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>
#include "map.h"
#include "corredores.h"
#include "structs.h"
#include "move.h"
#include "gerarPlayer.h"
#include "gerart.h"
#include "armadilha.h"
#include "luz.h"


int game_loop(int rows, int c, int cols, int **map, int *r_place, int *vida, posicao_player *player, bool *p_place, int *level, posicao_t *t, bool *t_place, bool *a_place,posicao_armadilha *a)
{ 
  srand(clock());
  dungeon_gen(rows, cols, map, r_place);
  dungeon_draw(rows, cols, map);

  armadilha(rows, cols, map, vida, player, a_place, level,a);
  gerar_t(rows, cols, map, c, level, p_place, r_place, player, t, t_place, a_place);
  movimentacao(c, map, player);
  cast_light(11, cols, map, rows,player);

  gerar_player(rows, cols, map, player, p_place);
  return 0;
}

int main()
{
  initscr();
  keypad(stdscr, 1);
  noecho();
  cbreak();
  curs_set(0);
  int r_place = 0;
  int vida = 100;
  bool p_place = 0;
  int level = 0;
  bool t_place = 0;
  bool a_place = 0;

  posicao_player *player = malloc(sizeof(posicao_player));
  (*player).x = -1;
  (*player).y = -1;
  posicao_t *t = malloc(sizeof(posicao_t));
  (*t).tx = -1;
  (*t).ty = -1;

   posicao_armadilha *a = malloc(sizeof(posicao_armadilha));
   (*a).ax = -1;
   (*a).ay = -1;


  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_pair(6, COLOR_GREEN, COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  attroff(COLOR_PAIR(1));

  int ch;
  mvprintw(rows / 2, (cols - strlen("Bem-vindo ao jogo!")) / 2, "Bem-vindo ao jogo!");
  attron(A_BOLD);
  mvprintw(rows / 2 + 2, (cols - strlen("Pressione 'p' para jogar.")) / 2, "Pressione 'p' para jogar.");
  attroff(A_BOLD);
  refresh();

  while (true)
  {
    ch = getch();
    if (ch == 'p')
      break;
  }

  int c = ' ';
  // int map [rows][cols];
  int **map = criarMatriz(rows, cols);

  do
  {
    game_loop(rows - 1, c, cols - 1, map, &r_place, &vida, player, &p_place, &level, t, &t_place, &a_place,a);
  } while ((c = getch()) != 'q');

  endwin();
  return 0;
}

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "bordas.c"
#include "gerarmapa.c"




int x, y;
int ty, tx; // coordenadas do t
bool p_place = 0;
int r_placed = 0;
bool t_place = 0;
int p_goid;






int game_loop(int rows, int c, int cols, char (*map)[cols]) /// forma de pssar um arra
{
  srand(time(NULL));

  dungeon_gen(rows , cols , r_placed, map);
  dungeon_draw (rows , cols , map);

  

  // draw ' ' empty space
  for (int yy = 0; yy <= rows; yy++)
  {
    for (int xx = 0; xx <= cols; xx++)
    {
      if (map[yy][xx] == ' ')
      {
        mvaddch(yy, xx, ' ');
      }
      else if (yy == 0 || yy == rows - 1)
      {

        mvaddch(yy, xx, 'O');
      }
      else if ((xx == 0 || xx == cols) && yy != rows) /// colocar as bordas do mapa / aqui damos print ao que vei sendo guardado no array 2d
      {

        mvaddch(yy, xx, 'O');
      }

      else if (yy == rows)
      {
        mvaddch(yy, xx, ' ');
      }
      else
      {
        mvaddch(yy, xx, '#');
      }
    }
  }

  /// parte da movimnetcao
  if (c == 'w' && map[y - 1][x] == ' ')
    y--;
  else if (c == 's' && map[y + 1][x] == ' ') //// movimentaco
    y++;
  else if (c == 'a' && map[y][x - 1] == ' ')
    x--;
  else if (c == 'd' && map[y][x + 1] == ' ')
    x++;

  ///  gerar random o t e o "@"
  if (p_place == 0)
  {
    while (1) /// gerar random o "@"
    {
      y = rand() % rows;
      x = rand() % cols;
      if (map[y][x] == ' ')
      {
        break;
      }
    }
    p_place = 1;
  }

  if (t_place == 0)
  {

    do
    {
      /// gerar t random
      ty = rand() % rows - 1; // para nao gerar na linh do fim
      tx = rand() % cols;
    } while (map[ty][tx] != ' ');

    t_place = 1;
  }

  if (y == ty && x == tx && c == 'm')
  {
    t_place = 0;

    p_goid += rand() % 10 + 1;
  }

  mvaddch(y, x, '@');
  mvaddch(ty, tx, 't');
  mvprintw(rows, 0, "GOLD: %d", p_goid);
  return 0;
}

///////

int main()
{
  int c = ' ';
  int rows, cols;
  

  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, rows, cols);

  char map[rows][cols];
  do
  {
    game_loop(rows - 1, c, cols - 1, map);

  } while ((c = getch()) != 'q');
  refresh();

  if (c != 'q') // q termina o progrma e "m" da o random das salas novamente
    getch();

  endwin();

  return 0;
}

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>

int **criarMatriz(int rows, int cols)
{
  int **map = (int **)calloc(rows, sizeof(int *));
  for (int R = 0; R < rows; R++)
    map[R] = (int *)calloc(cols, sizeof(int));

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
    {
      map[i][j] = ' ';
    }

  return map;
}

int dungeon_draw(int rows, int cols, int **map, int *vida, int *level, bool *w_on, int c)
{

  for (int yy = 0; yy <= rows; yy++)
  {
    for (int xx = 0; xx <= cols; xx++)
    {
      if (yy == rows)
      {
        mvaddch(yy, xx, ' ');
      }

      else if (map[yy][xx] == '#' && c == 'k')
      {
        attron(COLOR_PAIR(1));
        mvaddch(yy, xx, '#');
        attroff(COLOR_PAIR(1));
      }
      // else if (map[yy][xx] == 'L')
      //{
      //  attron(COLOR_PAIR(1));
      //  mvaddch(yy, xx, 'L');
      //  attroff(COLOR_PAIR(1));
      //}
      else
      {

        attron(COLOR_PAIR(2));
        mvaddch(yy, xx, '#');
        attroff(COLOR_PAIR(2));
      }
    }
  }
  if (*w_on == 1)
  {
    mvprintw(rows, 0, "LEVEL: %d  LIFE: %d YOU HAVE A GUN", *level, *vida);
  }
  mvprintw(rows, 0, "LEVEL: %d  LIFE: %d", *level, *vida);

  return 0;
}

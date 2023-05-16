#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>


int ** criarMatriz(int rows, int cols) {
  int ** map = (int **) calloc(rows, sizeof(int *));
  for(int R = 0; R < rows; R++)
    map[R] = (int *) calloc(cols, sizeof(int));

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      map[i][j] = ' ';
    }

  return map;
}

void guarda_valores(int rows, int cols, int ** map)
{

  for (int yy = 0; yy <= rows; yy++)
  {
    for (int xx = 0; xx <= cols; xx++)
    {
      if (yy == 0 || yy == rows - 1)
        map[yy][xx] = '/';
      else if ((xx == 0 || xx == cols) && yy != rows)
        map[yy][xx] = '/';
      else if (map[yy][xx] != ' ')
        map[yy][xx] = '#';
    }
  }
}

int dungeon_draw(int rows, int cols, int ** map)
{

  for (int yy = 0; yy <= rows; yy++)
  {
    for (int xx = 0; xx <= cols; xx++)
    {
      if (map[yy][xx] == ' ')
      {
        attron(COLOR_PAIR(2));
        mvaddch(yy, xx, '.');
        attroff(COLOR_PAIR(2));
      }
      else if (yy == 0 || yy == rows - 1)
      {
        attron(COLOR_PAIR(2));
        mvaddch(yy, xx, '/');
        attroff(COLOR_PAIR(2));
      }
      else if ((xx == 0 || xx == cols) && yy != rows)
      {
        attron(COLOR_PAIR(2));
        mvaddch(yy, xx, '/');
        attroff(COLOR_PAIR(2));
      }
      else if (yy == rows)
      {
        mvaddch(yy, xx, ' ');
      }

      else
      {

        attron(COLOR_PAIR(2));
        mvaddch(yy, xx, '#');
        attroff(COLOR_PAIR(2));
      }
    }
  }

  guarda_valores(rows, cols, map);
  return 0;
}
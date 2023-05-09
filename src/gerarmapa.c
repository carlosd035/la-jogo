#include <ncurses.h>

int dungeon_draw(int rows, int cols, int map[][cols])
{

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
      else if ((xx == 0 || xx == cols) && yy != rows)
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
  

  return 0;
}

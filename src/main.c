#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int x, y;
int ty, tx; // coordenadas do t
bool p_place = 0;
int r_placed = 0;
bool t_place = 0;
int p_goid;


int dungeon_draw(int rows, int cols, char (*map)[cols])
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

int dungeon_gen(int rows, int cols, char (*map)[cols])
{

  if (!r_placed)
  {
    int ry, rx;             // room coords
    int r_size_y, r_size_x; // room size
    int r_center_y = 0, r_center_x = 0;
    int r_old_center_y, r_old_center_x;
    int room_num = rand() % 40 +30;
    bool collision;

    // fill dungeon with walls and borders
    for (int y = 0; y <= rows; y++)
    {
      for (int x = 0; x <= cols; x++)
      {
        // borders
        if (y == 0 || y == 1 || y == rows - 1 || x == 0 ||
            x == cols || y == rows)
          map[y][x] = 'O';
        // walls
        else
          map[y][x] = '#';
      }
    }

    while (r_placed < room_num)
    {
      int try_counter = 0; // number of tries for prototyping

      // prototyping the room until no collisions
      do
      {
        collision = 0;

        // room coords
        ry = rand() % (rows - 4) + 1;
        rx = rand() % (cols - 4) + 1;

        // room sizes
        r_size_y = rand() % 3 + 4;
        r_size_x = rand() % 10 + 8;

        try_counter++;
        if (try_counter > 100)
        {
          ry = rx = 3;
          r_size_y = r_size_x = 3;
          break;
        }

        // check for collision
        for (int y = ry; y <= ry + r_size_y; y++)
        {
          for (int x = rx; x <= rx + r_size_x; x++)
          {
            if (map[y][x] == 'O' || map[y][x] == ' ' ||
                map[y + 2][x] == ' ' || map[y - 2][x] == ' ' ||
                map[y][x + 2] == ' ' || map[y][x - 2] == ' ')
            {
              collision = 1;
              y = ry + r_size_y + 1; // exit upper loop..
              break;                 // ..exit from current loop
            }
          }
        }
      } while (collision == 1);

      // fill DB map with rooms
      for (int y = ry; y <= ry + r_size_y; y++)
      {
        for (int x = rx; x <= rx + r_size_x; x++)
        {
          if (map[y][x] == 'O')
          {
            y = ry + r_size_y + 1; // exit upper loop..
            break;                 // ..exit from current loop
          }
          else
            map[y][x] = ' ';
        }
      }

      r_placed++;

      // corridors
      if (r_placed > 1)
      {
        r_old_center_y = r_center_y;
        r_old_center_x = r_center_x;
      }

      r_center_y = ry + (r_size_y / 2);
      r_center_x = rx + (r_size_x / 2);

      if (r_placed > 1)
      {
        int path_y;

        for (path_y = r_old_center_y; path_y != r_center_y;)
        {
          if (map[path_y][r_old_center_x] != 'O')
            map[path_y][r_old_center_x] = ' ';

          if (r_old_center_y < r_center_y)
            path_y++;
          else if (r_old_center_y > r_center_y)
            path_y--;
        }

        for (int path_x = r_old_center_x; path_x != r_center_x;)
        {
          if (map[path_y][path_x] != 'O')
            map[path_y][path_x] = ' ';

          if (r_old_center_x < r_center_x)
            path_x++;
          else if (r_old_center_x > r_center_x)
            path_x--;
        }
      }
    }
  }

  return 0;
}

void movimentacao (int c,int cols,char (*map)[cols]){
  /// parte da movimnetcao
  if (c == 'w' && map[y - 1][x] == ' ')
    y--;
  else if (c == 's' && map[y + 1][x] == ' ') //// movimentaco
    y++;
  else if (c == 'a' && map[y][x - 1] == ' ')
    x--;
  else if (c == 'd' && map[y][x + 1] == ' ')
    x++;
  }


int game_loop(int rows, int c, int cols, char (*map)[cols]) /// forma de pssar um arra
{
  srand(time(NULL));

  dungeon_gen(rows, cols, map);
  dungeon_draw(rows, cols, map);
  movimentacao(c,cols,map);

//  gerar random o t e o "@"
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
  bool color;

  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, rows, cols);

  // Inicia o suporte a cores
  start_color();
  //init_color(2,COLOR_RED,COLOR_BLUE);

  // Define o par de cores 1 como vermelho no fundo e branco no texto
  init_pair(1,COLOR_WHITE,COLOR_BLUE);
  bkgd(COLOR_PAIR(1));  
  attroff(COLOR_PAIR(1));

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

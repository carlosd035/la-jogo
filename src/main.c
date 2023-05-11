#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define M_PI 3.14159265358979323846
// #include "gerarmapa.c"

struct posicao_player
{
  int y;
  int x;
};
struct posicao_player posicao_player;

struct posicao_t
{

  int ty;
  int tx; // coordenadas do t
};
struct posicao_t posicao_t;

struct posicao_armadilha
{
  int ay;
  int ax;
};
struct posicao_armadilha posicao_armadilha;

bool p_place = 0;
int r_placed = 0;
bool t_place = 0;
int level = 0;
bool a_place = 0;
int vida = 100;
bool luz_ativada = true;

int dungeon_draw(int rows, int cols, int map[][cols])
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
        map[yy][xx] = '/';
        attroff(COLOR_PAIR(2));
      }
      else if ((xx == 0 || xx == cols) && yy != rows)
      {
        attron(COLOR_PAIR(2));
        mvaddch(yy, xx, '/');
        map[yy][xx] = '/';
        attroff(COLOR_PAIR(2));
      }
      else if (yy == rows)
      {
        mvaddch(yy, xx, ' ');
      }

      else
      {

        attron(COLOR_PAIR(1));
        mvaddch(yy, xx, '#');
        map[yy][xx] = '#';
        attroff(COLOR_PAIR(1));
      }
    }
  }

  return 0;
}
int dungeon_gen(int rows, int cols, int map[][cols])
{

  if (!r_placed)
  {
    int ry, rx;             // room coords
    int r_size_y, r_size_x; // room size
    int r_center_y = 0, r_center_x = 0;
    int r_old_center_y, r_old_center_x;
    int room_num = rand() % 45 + 40;
    bool collision;

    // fill dungeon with walls and borders
    for (int y = 0; y <= rows; y++)
    {
      for (int x = 0; x <= cols; x++)
      {
        // borders
        if (y == 0 || y == 1 || y == rows - 1 || x == 0 ||
            x == cols - 1 || y == rows)
          map[y][x] = '/';
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
        r_size_y = rand() % 5 + 4;
        r_size_x = rand() % 12 + 11;

        try_counter++;
        if (try_counter > 1000)
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
            if (map[y][x] == '/' || map[y][x] == ' ' ||
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
          if (map[y][x] == '/')
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
          if (map[path_y][r_old_center_x] != '/')
            map[path_y][r_old_center_x] = ' ';

          if (r_old_center_y < r_center_y)
            path_y++;
          else if (r_old_center_y > r_center_y)
            path_y--;
        }

        for (int path_x = r_old_center_x; path_x != r_center_x;)
        {
          if (map[path_y][path_x] != '/')
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
void movimentacao(int c, int cols, int map[][cols])
{
  switch (c)
  {
  case 'w':
    if (map[posicao_player.y - 1][posicao_player.x] != '#' && map[posicao_player.y - 1][posicao_player.x] != '/')
      posicao_player.y--;
    break;
  case 's':
    if (map[posicao_player.y + 1][posicao_player.x] != '#' && map[posicao_player.y + 1][posicao_player.x] != '/')
      posicao_player.y++;
    break;
  case 'a':
    if (map[posicao_player.y][posicao_player.x - 1] != '#' && map[posicao_player.y][posicao_player.x - 1] != '/')
      posicao_player.x--;
    break;
  case 'd':
    if (map[posicao_player.y][posicao_player.x + 1] != '#' && map[posicao_player.y][posicao_player.x + 1] != '/')
      posicao_player.x++;
    break;
  default:
    // handle invalid input
    break;
  }
}

void gerar_player(int rows, int cols, int map[][cols], int c)
{

  if (p_place == 0)
  {
    while (1) /// gerar random o "@"
    {
      posicao_player.y = rand() % rows;
      posicao_player.x = rand() % cols;
      if (map[posicao_player.y][posicao_player.x] == ' ')
      {
        break;
      }
    }
    p_place = 1;
  }
  attron(COLOR_PAIR(4));
  mvaddch(posicao_player.y, posicao_player.x, '@');
  attroff(COLOR_PAIR(4));
}

///////////////////////////////////////////
void gerar_t(int rows, int cols, int map[][cols], int c)
{

  if (t_place == 0)
  {

    do
    {
      // gerar t aleatoriamente
      posicao_t.ty = rand() % rows - 1; // para não gerar na última linha
      posicao_t.tx = rand() % cols;
    } while (map[posicao_t.ty][posicao_t.tx] != ' ');

    t_place = 1;
  }

  attron(COLOR_PAIR(2));

  mvaddch(posicao_t.ty, posicao_t.tx, 't');
  map[posicao_t.ty][posicao_t.tx] = 't';
  attroff(COLOR_PAIR(2));

  if (posicao_player.y == posicao_t.ty && posicao_player.x == posicao_t.tx && c == 'm')
  {
    t_place = 0;
    a_place = 0;
    p_place = 0;
    r_placed = 0;

    dungeon_gen(rows, cols, map);

    level++;
  }
}

void armadilha(int rows, int cols, int map[][cols])
{

  if (a_place == 0)
  {

    do
    {
      // gerar t aleatoriamente
      posicao_armadilha.ay = rand() % rows - 1; // para não gerar na última linha
      posicao_armadilha.ax = rand() % cols;
    } while (map[posicao_armadilha.ay][posicao_armadilha.ax] != ' ');

    a_place = 1;
  }
  attron(COLOR_PAIR(2));
  mvaddch(posicao_armadilha.ay, posicao_armadilha.ax, '*');
  map[posicao_armadilha.ay][posicao_armadilha.ax] = '*';
  attroff(COLOR_PAIR(2));

  if (posicao_player.y == posicao_armadilha.ay && posicao_player.x == posicao_armadilha.ax)
  {
    vida = vida - 25;
  }

  mvprintw(rows, 0, "LEVEL: %d  VIDA: %d", level, vida);
}

void cast_light(int radius, int cols, int map[][cols], int rows)
{
  if (luz_ativada){
  for (int i = 0; i < 360; i += 1)
  {
    double dx = cos(i * M_PI / 180.0);
    double dy = sin(i * M_PI / 180.0);
    int x = (int)posicao_player.x;
    int y = (int)posicao_player.y;
    for (int j = 1; j <= radius; j++)
    {
      x = (int)(posicao_player.x + dx * j);
      y = (int)(posicao_player.y + dy * j);
      if (x < 0 || y < 0 || x >= cols || y >= rows)
      {
        break;
      }
      double distance = sqrt((x - posicao_player.x) * (x - posicao_player.x) + (y - posicao_player.y) * (y - posicao_player.y));
      if (distance > radius)
      {
        break;
      }
      int cx = (int)posicao_player.x;
      int cy = (int)posicao_player.y;
      int delta_x = abs(x - cx);
      int delta_y = abs(y - cy);
      int sign_x = cx < x ? 1 : -1;
      int sign_y = cy < y ? 1 : -1;
      int error = delta_x - delta_y;
      bool blocked = false;
      while (cx != x || cy != y)
      {
        if (map[cy][cx] == '#' || map[cy][cx] == '*' || map[cy][cx] == '/')
        {
          blocked = true;
          break;
        }
        int error2 = error * 2;
        if (error2 > -delta_y)
        {
          error -= delta_y;
          cx += sign_x;
        }
        if (error2 < delta_x)
        {
          error += delta_x;
          cy += sign_y;
        }
      }
      if (blocked)
      {
        break;
      }
      if (map[y][x] == '#')
      {
        attron(COLOR_PAIR(5));
        mvaddch(y, x, '#');
        attroff(COLOR_PAIR(5));
      }
      else if (map[y][x] == '*')
      {
        attron(COLOR_PAIR(3));
        mvaddch(y, x, '*');
        attroff(COLOR_PAIR(3));
      }
      else if (map[y][x] == '/')
      {
        attron(COLOR_PAIR(3));
        mvaddch(y, x, '/');
        attroff(COLOR_PAIR(3));
      }
      else if (map[y][x] == 't')
      {
        attron(COLOR_PAIR(6));
        mvaddch(y, x, 't');
        attroff(COLOR_PAIR(6));
      }
      else
      {
        attron(COLOR_PAIR(1));
        mvaddch(y, x, '.');
      }
    }
  }
}
}

int game_loop(int rows, int c, int cols, int map[][cols]) /// forma de pasar um arra
{
  srand(time(NULL));
  if (c == 'l')
  {
    luz_ativada = !luz_ativada; // inverte o valor atual da variável
  }

  dungeon_gen(rows, cols, map);
  dungeon_draw(rows, cols, map);
  //
  armadilha(rows, cols, map);
  gerar_t(rows, cols, map, c);
  movimentacao(c, cols, map);
  cast_light(11, cols, map, rows);
  //
  gerar_player(rows, cols, map, c);
}
int main()
{
  initscr();
  keypad(stdscr, 1);
  noecho();
  cbreak();
  curs_set(0);

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
  int map[rows][cols];
  do
  {
    game_loop(rows - 1, c, cols - 1, map);
  } while ((c = getch()) != 'q');

  endwin();
  return 0;
}

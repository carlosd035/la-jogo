#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
// #include "gerarmapa.c"
struct posicao_player_t
{
  int y;
  int x;
  int ty;
  int tx; // coordenadas do t
};
struct posicao_player_t posicao_player_t;

struct posicao_armadilha
{
  int ay;
  int ax;
};
struct posicao_armadilha posicao_armadilha;

bool p_place = 0;
int r_placed = 0;
bool t_place = 0;
int p_goid;
bool a_place = 0;
 int vida = 100;

int dungeon_draw(int rows, int cols, int map[][cols])
{

  for (int yy = 0; yy <= rows; yy++)
  {
    for (int xx = 0; xx <= cols; xx++)
    {
      if (map[yy][xx] == ' ')
      {
        // attron(COLOR_PAIR(5));
        mvaddch(yy, xx, ' ');
        // attroff(COLOR_PAIR(5));
      }
      else if (yy == 0 || yy == rows - 1)
      {
        attron(COLOR_PAIR(3));
        mvaddch(yy, xx, '/');
        attroff(COLOR_PAIR(3));
      }
      else if ((xx == 0 || xx == cols) && yy != rows)
      {
        attron(COLOR_PAIR(3));
        mvaddch(yy, xx, '/');
        attroff(COLOR_PAIR(3));
      }
      else if (yy == rows)
      {
        mvaddch(yy, xx, ' ');
      }

      else
      {

        attron(COLOR_PAIR(4));
        mvaddch(yy, xx, '#');
        attroff(COLOR_PAIR(4));
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
            x == cols || y == rows)
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
        r_size_y = rand() % 3 + 4;
        r_size_x = rand() % 10 + 8;

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
    if (map[posicao_player_t.y - 1][posicao_player_t.x] == ' ')
      posicao_player_t.y--;
    break;
  case 's':
    if (map[posicao_player_t.y + 1][posicao_player_t.x] == ' ')
      posicao_player_t.y++;
    break;
  case 'a':
    if (map[posicao_player_t.y][posicao_player_t.x - 1] == ' ')
      posicao_player_t.x--;
    break;
  case 'd':
    if (map[posicao_player_t.y][posicao_player_t.x + 1] == ' ')
      posicao_player_t.x++;
    break;
  default:
    // handle invalid input
    break;
  }
}

void gerar_player_t(int rows, int cols, int map[][cols], int c)
{

  if (p_place == 0)
  {
    while (1) /// gerar random o "@"
    {
      posicao_player_t.y = rand() % rows;
      posicao_player_t.x = rand() % cols;
      if (map[posicao_player_t.y][posicao_player_t.x] == ' ')
      {
        break;
      }
    }
    p_place = 1;
  }
  attron(COLOR_PAIR(2));
  mvaddch(posicao_player_t.y, posicao_player_t.x, '@');
  attroff(COLOR_PAIR(2));

  ///////////////////////////////////////////
  // int g = rand() % 4 + 1;

  if (t_place == 0)
  {

    do
    {
      // gerar t aleatoriamente
      posicao_player_t.ty = rand() % rows - 1; // para não gerar na última linha
      posicao_player_t.tx = rand() % cols;
    } while (map[posicao_player_t.ty][posicao_player_t.tx] != ' ');

    t_place = 1;
  }

  // attron(COLOR_PAIR(5));
  mvaddch(posicao_player_t.ty, posicao_player_t.tx, 't');
  //\ attroff(COLOR_PAIR(5));

  if (posicao_player_t.y == posicao_player_t.ty && posicao_player_t.x == posicao_player_t.tx && c == 'm')
  {
    t_place = 0;
    a_place = 0;
    p_place = 0;
    r_placed = 0;

    dungeon_gen(rows, cols, map);

    p_goid += rand() % 10 + 1;
  }

  // mvaddch(posicao_player_t.ty, posicao_player_t.tx, 't');
  // mvprintw(rows, 0, "GOLD: %d", p_goid);
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
  attron(COLOR_PAIR(5));
  mvaddch(posicao_armadilha.ay, posicao_armadilha.ax, '*');
  attroff(COLOR_PAIR(5));

  if (posicao_player_t.y == posicao_armadilha.ay && posicao_player_t.x == posicao_armadilha.ax)
  {
    vida = vida - 25;
  
  }

mvprintw(rows, 0,"GOLD: %d  vida : %d", p_goid, vida);
}

int game_loop(int rows, int c, int cols, int map[][cols]) /// forma de pasar um arra
{
  srand(time(NULL));

  dungeon_gen(rows, cols, map);
  dungeon_draw(rows, cols, map);
  movimentacao(c, cols, map);
  gerar_player_t(rows, cols, map, c);
  armadilha(rows, cols, map);
}

int main()
{
  int c = ' ';
  int rows, cols;

  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, rows, cols);
  /*
    typedef struct {
      char ch;
      bool walkable;
  } TIle;

  TIle ** matrixSetup (int rows, int cols) {
    // aloca memória para um array de ponteiros para "Tile"
    TIle **map = (TIle**) calloc (rows, sizeof(TIle*));

    // aloca memória para cada linha da matriz
    for (int R = 0; R < rows; R++) {
      map[R] = (Tile*) calloc(cols, sizeof(Tile));
    }

    // preenche cada elemento da matriz com valores iniciais
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++)  {
        map[i][j].ch = ' ';
        map[i][j].walkable = false;
      }
    }

    // retorna o ponteiro para a matriz alocada
    return map;
  }

  */
  // Inicia o suporte a cores
  start_color();
  // init_color(2,COLOR_RED,COLOR_BLUE);

  // Define o par de cores 1 como vermelho no fundo e branco no texto
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  attroff(COLOR_PAIR(1));

  int map[rows][cols];

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


#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <curses.h>

#include <stdbool.h>
#include <stdlib.h>

void fill_borders(int rows, int cols, int **map)
{
  for (int y = 0; y <= rows; y++)
  {
    for (int x = 0; x <= cols; x++)
    {
      if (y == 0 || y == 1 || y == rows - 1 || x == 0 || x == cols || y == rows)
      {
        map[y][x] = '/'; // Código para tratar a borda do mapa
      }
      else
      {
        map[y][x] = '#';
      }
    }
  }
}

bool check_colisao(int **map, int y, int x)
{
  return (map[y][x] == '/' || map[y][x] == ' ' ||
          map[y + 2][x] == ' ' || map[y - 2][x] == ' ' ||  
          map[y][x + 2] == ' ' || map[y][x - 2] == ' ');
}

void generate_room(int rows, int cols, int **map, int *r_place)
{
  int coordinates_y, coordinates_x; // room coords
  int room_size_y, room_size_x;     // room size
  bool colisao;
  int centro_y = 0, centro_x = 0;
  int centro_a_y, centro_a_x;
  int room_num = rand() % 40 + 35;

  fill_borders(rows, cols, map);

  while (*r_place < room_num)
  {
    int contador = 0; // numero de tentativas

    do
    {
      colisao = false;

      coordinates_y = rand() % (rows - 4) + 1;
      coordinates_x = rand() % (cols - 4) + 1;
      room_size_y = rand() % 6 + 4;
      room_size_x = rand() % 13 + 11;

      contador++;
      if (contador > 1000)
      {
        coordinates_y = coordinates_x = 3;
        room_size_y = room_size_x = 3;
        break;
      }

      for (int y = coordinates_y; y <= coordinates_y + room_size_y; y++)
      {
        for (int x = coordinates_x; x <= coordinates_x + room_size_x; x++)
        {
          if (check_colisao(map, y, x))
          {
            colisao = true;
            y = coordinates_y + room_size_y + 1; // sai do ciclo  externo 
            break;                               
          }
        }
      }
    } while (colisao == true);

    for (int y = coordinates_y; y <= coordinates_y + room_size_y; y++)
    {
      for (int x = coordinates_x; x <= coordinates_x + room_size_x; x++)
      {
      map[y][x] = ' ';
      
      }
    }

    *r_place = *r_place + 1;
/////// corredores
    if (*r_place > 0)
    {
      centro_a_y = centro_y;
      centro_a_x = centro_x;
    }

    centro_y = coordinates_y + (room_size_y / 2);
    centro_x = coordinates_x + (room_size_x / 2);

    if (*r_place > 1)
    {
      int path_y;
 
      for (path_y = centro_a_y; path_y != centro_y;)
      {
        if (map[path_y][centro_a_x] != '/')
        {
          map[path_y][centro_a_x] = ' ';
        }

        if (centro_a_y < centro_y)
        {
          path_y++;
        }
        else if (centro_a_y > centro_y)
        {
          path_y--;
        }
      }

      for (int path_x = centro_a_x; path_x != centro_x;)
      {
        if (map[path_y][path_x] != '/')
        {
          map[path_y][path_x] = ' ';
        }

        if (centro_a_x < centro_x)
        {
          path_x++;
        }
        else if (centro_a_x > centro_x)
        {
          path_x--;
        }
      }
    }
  }
}

int dungeon_gen(int rows, int cols, int **map, int *r_place)
{
  if (!(*r_place))
  {
    generate_room(rows, cols, map, r_place);
  }

  return 0;
}

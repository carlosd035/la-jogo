#include <ncurses.h>

int dungeon_gen(int rows,int cols, char (*map)[cols],int r_placed){

  if (!r_placed)
    {
        int ry, rx; // room coords
        int r_size_y, r_size_x ; // room size
        int r_center_y= 0 , r_center_x = 0;
        int r_old_center_y, r_old_center_x;
        int room_num = rand() % 30 + 20;
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
                r_size_y = rand() % 5 + 4;
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
                            break; // ..exit from current loop
                        }
                    }
                }
            }
            while (collision == 1);
            
            // fill DB map with rooms
            for (int y = ry; y <= ry + r_size_y; y++)
            {
                for (int x = rx; x <= rx + r_size_x; x++)
                {
                    if (map[y][x] == 'O')
                    {
                        y = ry + r_size_y + 1; // exit upper loop..
                        break; // ..exit from current loop
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

                for (path_y = r_old_center_y; path_y != r_center_y; )
                {
                    if (map[path_y][r_old_center_x] != 'O')
                        map[path_y][r_old_center_x] = ' ';
                    
                    if (r_old_center_y < r_center_y)
                        path_y++;
                    else if (r_old_center_y > r_center_y)
                        path_y--;
                }
                
                for (int path_x = r_old_center_x; path_x != r_center_x; )
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
nt main()
{

  initscr();
  keypad(stdscr, 1);
  noecho();
  cbreak();
  curs_set(0);
  int ch = 0 ;
  printw("Bem-vindo ao jogo!\n\n");
  printw("Pressione 'p' jogar .\n");
  refresh();

if (ch = 'p'){
  int c = ' ';
  int rows, cols;

  getmaxyx(stdscr, rows, cols);
  int map[rows][cols];

  // int **map = malloc(rows * sizeof(int *));
  // for (int i = 0; i < rows; i++)
  // {
  //   map[i] = malloc(cols * sizeof(int));
  // }
  ////////////////////////////////////////////////////////////
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
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_pair(6, COLOR_GREEN, COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  attroff(COLOR_PAIR(1));

  // int map[rows][cols];

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
else endwin();
} 

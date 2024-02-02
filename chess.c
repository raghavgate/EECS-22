#include <stdio.h>

int main() {
  char board[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
  };

  
  for (int i = 0; i < 8; i++) {
    printf(" %d |", 8 - i);
    for (int j = 0; j < 8; j++) {
      if ((i + j) % 2 == 0) {
        printf("\033[47m ");
      } else {
        printf("\033[40m ");
      }
      if (board[i][j] == ' ') {
        printf(" ");
      } else if (board[i][j] >= 'a' && board[i][j] <= 'z') {
        printf("\033[31m%c", board[i][j]);
      } else {
        printf("\033[34m%c", board[i][j]);
      }
      printf("\033[0m");
      
    }
    printf("\n");
    
  }
  printf("     a b c d e f g h\n");

  return 0;
}

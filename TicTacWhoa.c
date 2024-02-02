
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gridclear ();
void printgrid ();
int availablemoves ();
void player1 ();
void player2 ();
char checkwin ();
void printstatus (char);


char grid[3][3];
char PLAY1 = 'X';
char PLAY2 = 'O';




int
main ()
{
  char win = '_';
  char playagain[3] = "yes";

  do
    {
      win = '_';

      gridclear ();

      while (win == '_' && availablemoves () != 0)
	{
	  printgrid ();

	  player1 ();
	  win = checkwin ();
	  if (win != '_' || availablemoves () == 0)
	    {
	      break;
	    }
	  printgrid ();
	  player2 ();
	  win = checkwin ();
	  if (win != '_' || availablemoves () == 0)
	    {
	      break;
	    }
	}

      printgrid ();
      printstatus (win);

      printf ("\nWould you like to play again? (Yes/No): ");
      scanf ("%s", playagain);
    }
  while (strcmp(playagain,"yes")==0);

  if (strcmp (playagain, "yes") == 0)
    {

      main ();
    }
  else
    {
      printf ("Thanks for playing!");
    }
  return 0;

}









void
gridclear ()
{
  for (int a = 0; a < 3; a++)
    {
      for (int b = 0; b < 3; b++)
	{
	  grid[a][b] = '_';
	}
    }
}

void
printgrid ()
{

  printf ("3 _%c_|_%c_|_%c_\n", grid[0][0], grid[0][1], grid[0][2]);
  printf ("2 _%c_|_%c_|_%c_\n", grid[1][0], grid[1][1], grid[1][2]);
  printf ("1  %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);
  printf ("   A   B   C\n");

}

int
availablemoves ()
{
  int emptyspaces = 9;

  for (int a = 0; a < 3; a++)
    {
      for (int b = 0; b < 3; b++)
	{
	  if (grid[a][b] != '_')
	    {
	      emptyspaces--;

	    }
	}
    }
  return emptyspaces;

}

void
player1 ()
{
  char input[6];
  int x;
  int y;

  do
    {
      printf ("enter position player1 : \n");
      scanf (" %s", input);
      if (strcmp (input, "quit") == 0)
	{
	  
	    printf ("\nThanks for playing");
	    exit (0);
	  
	}
      if (strlen(input)==2)
	{
	  if (strcmp (input, "A3") == 0)
	    {
	      x = 0;
	      y = 0;
	    }
	  if (strcmp (input, "A2") == 0)
	    {
	      x = 1;
	      y = 0;
	    }
	  if (strcmp (input, "A1") == 0)
	    {
	      x = 2;
	      y = 0;
	    }
	  if (strcmp (input, "B3") == 0)
	    {
	      x = 0;
	      y = 1;
	    }
	  if (strcmp (input, "B2") == 0)
	    {
	      x = 1;
	      y = 1;
	    }
	  if (strcmp (input, "B1") == 0)
	    {
	      x = 2;
	      y = 1;
	    }
	  if (strcmp (input, "C3") == 0)
	    {
	      x = 0;
	      y = 2;
	    }
	  if (strcmp (input, "C2") == 0)
	    {
	      x = 1;
	      y = 2;
	    }
	  if (strcmp (input, "C1") == 0)
	    {
	      x = 2;
	      y = 2;
	    }
	}
      else
	{
	  printf ("invalid input try again\n");
	  player1 ();
	}

      if (grid[x][y] != '_')
	{
	  printf ("Invalid Move\n");
	}

      else
	{
	  grid[x][y] = PLAY1;
	  break;
	}
    }
  while (grid[x][y] != '_');

}

void
player2 ()
{
  char input[4];
  int x;
  int y;

  do
    {
      printf ("enter position player2 : \n");
      scanf (" %s", input);

      if (strcmp (input, "quit") == 0)
	{


	  printf ("\nThanks for playing");
	  exit (0);

	}
      if (strlen (input) == 2)
	{
	  if (strcmp (input, "A3") == 0)
	    {
	      x = 0;
	      y = 0;
	    }
	  if (strcmp (input, "A2") == 0)
	    {
	      x = 1;
	      y = 0;
	    }
	  if (strcmp (input, "A1") == 0)
	    {
	      x = 2;
	      y = 0;
	    }
	  if (strcmp (input, "B3") == 0)
	    {
	      x = 0;
	      y = 1;
	    }
	  if (strcmp (input, "B2") == 0)
	    {
	      x = 1;
	      y = 1;
	    }
	  if (strcmp (input, "B1") == 0)
	    {
	      x = 2;
	      y = 1;
	    }
	  if (strcmp (input, "C3") == 0)
	    {
	      x = 0;
	      y = 2;
	    }
	  if (strcmp (input, "C2") == 0)
	    {
	      x = 1;
	      y = 2;
	    }
	  if (strcmp (input, "C1") == 0)
	    {
	      x = 2;
	      y = 2;
	    }
	}
      else
	{
	  printf ("invalid input try again");
	  player2 ();
	}

      if (grid[x][y] != '_')
	{
	  printf ("Invalid Move\n");
	}

      else
	{
	  grid[x][y] = PLAY2;
	  break;
	}
    }
  while (grid[x][y] != '_');

}



char
checkwin ()
{
  for (int a = 0; a < 3; a++)
    {
      if (grid[a][0] == grid[a][1] && grid[a][1] == grid[a][2])
	{
	  return grid[a][0];
	}
    }

  for (int a = 0; a < 3; a++)
    {
      if (grid[0][a] == grid[1][a] && grid[1][a] == grid[2][a])
	{
	  return grid[0][a];
	}
    }

  if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
    {
      return grid[0][0];
    }
  if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
    {
      return grid[0][2];
    }

  return '_';
}


void
printstatus (char win)
{
  if (win == PLAY1)
    {
      printf ("Player 1 wins!");
    }
  else if (win == PLAY2)
    {
      printf ("Player 2 wins!");
    }
  else
    {
      printf ("TIE");
    }
}

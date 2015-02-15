// Authors: Cindy Chao & Daniel Chen
// Program looks for a path in a maze

#include <stdio.h>

int find_path(char line[][8], int i, int j);

int main(int argc, char *argv[])
{
  int i, j;
  char line[8][8];
  FILE *fp = fopen(argv[1], "r");
  
  for(i = 0; i < 8; i++) 
  {
    for(j = 0; j < 8; j++)
    {
      fscanf(fp, "%c", &line[i][j]);
      if (line[i][j] == '\n')    
        j--;
    }
  }

  if (line[0][0] == 'X' && line[0][2] == 'X' && line[1][1] == 'X')
    printf("No path was found.\n");
  else if (find_path(line, 7, 7) == -1)
    printf("No path was found.\n");
  
  fclose(fp);
 
  return 0;
} // main()

int find_path(char line[][8], int i, int j)
{
  if ((line[i][j] == 'X') || (line[0][1] == 'X') || i>7 || j>7 || i<0 || j<0)
    return -1; 
  
  line[i][j] = 'X';
  
  if ((i == 0) && (j == 1)){
    printf("(%d, %d)\n", i, j);
    return 1;
  }

  if ((find_path(line, i, j+1) == 1) ||
      (find_path(line, i-1, j) == 1) ||
      (find_path(line, i, j-1) == 1) ||
      (find_path(line, i+1, j) == 1))
  {
    printf("(%d, %d)\n", i, j);
    return 1;
  }

  return 0;
} // find_path()

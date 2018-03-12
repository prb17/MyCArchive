#include<stdio.h>
#include<stdlib.h>

void func(int **x, int idx)
{
  int *temp = x[0];
  x[0] = x[1] + 1;
  x[1][idx] = *temp;
}

int main(int argc, char **argv)
{
  int a = 21;
  int b[4] = {3, 9, 7, 13};
  int **c = (int **)malloc(2 * sizeof(int*));
  c[0] = &a;
  c[1] = b;
  for(int i = 0; i <4; i++)
    {
      func(c, i);
    }
  fprintf(stderr, "%d %d\n", *c[0], *c[1]);
  for(int i = 0; i<4; i++)
    {
      fprintf(stderr, "%d ", b[i]);
    }
  fprintf(stderr, "\n");
  free(c);
  return 0;
}

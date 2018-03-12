//tester for exam problems
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc,char **argv)
{
  if (argc != 3)
    {
      exit(1);
    }
  if (strlen(argv[1]) > 8 || strlen(argv[2]) > 8)
    {
      exit(2);
    }

  int first = atoi(argv[1]);
  int second = atoi(argv[2]);

  char *strNum = 0;
  int sum = 0, ignore = 0, stacker = 1;
  while(fscanf(stdin, "%ms", &strNum) != EOF)
    {
      int num = atoi(strNum);
      if (!ignore)
	{
	  if (first > num)
	    {
	      ignore = 1;
	    }
	  if ((num > first && num < second) || (num > second && num < first))
	    {
	      sum += (num * stacker);
	      stacker = 1;
	    }
	  if (num > second)
	    {
	      stacker *= 2;
	    }
	}
      else
	{
	  ignore = 0;
	}
    }
  fprintf(stdout, "%d\n", sum);
  return 0;
}

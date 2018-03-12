//Group 3: Simon Yang, George Qiao, Peter Brady
#include<stdio.h>
//#include<math.h>
int main(int args, char **argv)
{
  char colon = ':';
  
  char word[10];
  word[0] = 'a';
  word[1] = 'p';
  word[2] = 'p';
  word[3] = 'l';
  word[4] = 'e';
  word[5] = 's';
  word[6] = 'a';
  word[7] = 'u';
  word[8] = 'c';
  word[9] = 'e';
  word[10] = '\0';

  for (int i = 1; i < 100; i++) 
    {
      for (int j = 0; j < 10; j++)
	{
	  if (i%10 == 1)
	    {//right aligned
	      fprintf(stdout, "%d%c ", j, colon);
	      //     	      fprintf(stdout, "%s", &colon);
	      fprintf(stdout, "%12d\n",(i*j)+(7500*(i-50)));
	    }
	  if (i%10 == 2)
	    {//left aligned
	      fprintf(stdout, "%-*d %c ", 3, j, colon);
	      //fprintf(stdout, "%s ", &colon1);
	      fprintf(stdout, "%-*d\n", 12, (i*j)+(7500*(i-50)));
	    }
	  if (i%10 == 3)
	    {
	      fprintf(stdout, "+%-*d %c", 3, j, colon);
	      //fprintf(stdout, "+%s ", &colon1[0]);
	      fprintf(stdout, "+%-*d\n", 12, (i*j)+(7500*(i-50)));
	    }
	}
    }
  return 0;
} 

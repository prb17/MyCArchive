//Kelly To, Peter Brady, Huy Hoang
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char **argv)
{
  float number = 0;
  fprintf(stdout, "Enter a number: ");
  fscanf(stdin, "%f", &number);
  fprintf(stdout, "You entered %f\n", number);

  if (number == 1)
    {
      float number1 = 0;
      float number2 = 0;
      fprintf(stdout, "Enter two more numbers:");
      fscanf(stdin, "%f %f", &number1, &number2);
      fprintf(stdout, "\nYou entered '%f' and '%f'\n", number1, number2);
    }
  if (number == 2)
    {
      char word[10];
      fprintf(stdout, "Enter a word:");
      fscanf(stdin, "%s", &word[0]);
      fprintf(stdout, "You entered: '%s'\n", &word[0]);
    }
  if (number == 3)
    {
      char word1[6];
      char word2[6];
      fprintf(stdout, "Enter a word:");
      fscanf(stdin, "%5s", &word1[0]);
      fscanf(stdin, "%5s", &word2[0]);
      fprintf(stdout, "First and Second word are '%s' and '%s' respectively.\n", word1, word2);
    }
  if (number == 4)
    {
      char *word1 = NULL;
      char *word2 = NULL;
      char letter = '\0';
      word1 = (char *)malloc(10 * sizeof(char));
      word2 = (char *)malloc(10 * sizeof(char));
     
      fscanf(stdin, "%c", &letter);
      fprintf(stdout, "Enter two words");
      fscanf(stdin, "%5s %5s", &word1[0], &word2[0]);
      fscanf(stdin, "%c", &letter);
      
      fprintf(stdout, "You entered: %s and %s\n", &word1[0], &word2[0]);
      free(word1);
      free(word2);
      word1 = NULL;
      word2 = NULL;
    }
  if (number == 5)
    {
      char letter = '\0';
      char *word = NULL;
      fprintf(stdout, "Enter five words: ");
      fscanf(stdin, "%c", &letter);
      for(int i = 0; i < 5; i++)
	{
	  //fscanf(stdin, "%c", &letter);
	  scanf("%ms", &word);
	  fscanf(stdin, "%c", &letter);
	  fprintf(stdout, "%s\n", &word[0]);
	  free(word);
	  word = NULL;
	}
    }
  if (number == 6)
    {
      char letter = '\0';
      char *word = NULL;
      int number = 0;
      
      fprintf(stdout, "Enter any number: ");
      fscanf(stdin, "%c", &letter);
	  fscanf(stdin, "%m[^\n]s", &word);
	  fscanf(stdin, "%c", &letter);
	  number = word - '0';
      fprintf(stdout,"You entered: %s and difference is %d\n", &word[0], number);
    }

  return 0;
}

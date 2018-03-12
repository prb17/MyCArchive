/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  <Text Rearanger>
  Program #1
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<getopt.h>

void reverseWords(char* line)
{
  int lengthOfLine = strlen(line);
  int i,j,k,startOfWord = 0, endOfWord = 0;
  for(i = startOfWord; i < lengthOfLine; i++)
    {
      if(!isspace(line[i]))
	{
	  startOfWord = i;
	  for(j = startOfWord; j < lengthOfLine; j++)
	    {
	      if(isspace(line[j]))
	      {
		endOfWord = j - 1;
		break;
	      }
	    }
	  if(endOfWord == -1)
	    {
	      endOfWord = lengthOfLine - 1;
	    }
	  for(k = startOfWord ; k <= (startOfWord + endOfWord) / 2 ; k++)
	    {
	      char charHolder = line[k];
	      line[k] = line[endOfWord - (k - startOfWord)];
	      line[endOfWord - (k - startOfWord)] = charHolder;
	    }
	  i = endOfWord;
	}
    }
}

void reverseLine(char* line)
{
  char letter;
  
  for (int i = 0, j = strlen(line) - 2; i < j; i++, j--)
    {
      letter = line[j];
      line[j] = line[i];
      line[i] = letter;
    }
}

void toggle(char* line)
{
  for (int i = 0; i < strlen(line); i++)
    {
      if(isupper(line[i]))
	{
	 line[i] = tolower(line[i]);
	}
      else
	{
	 line[i] = toupper(line[i]);
	}
    }
}

void lineSwap(char* line)
{
  
}


int main(int argc, char **argv)
{
  int revWords = 0;
  int revLine = 0;
  int changeCase = 0;
  int swapLines = 0;
  int cLineArgs;
    
  while((cLineArgs = getopt(argc, argv, "rets")) != -1)
    {
      switch(cLineArgs)
	{
	case 'r': revWords = 1;
	  break;
	case 'e': revLine = 1; 
	  break;
	case 't': changeCase = 1;
	  break;
	case 's': swapLines = 1;
	  break;
	default: return 1;
	}
    }

  size_t lineLength = 100;
  char *line = (char *)malloc(lineLength * sizeof(char));

  while(fgets(line, lineLength, stdin) != NULL)
    {
      if (swapLines != 0)
	{
	  lineSwap(line);
	}
      if (revWords != 0)
	{
	 reverseWords(line);
	}
      if (revLine != 0)
	{
	  reverseLine(line);
	}
      if (changeCase != 0)
	{
	  toggle(line);
	}
      printf("%s", line);
    }

  free(line);
  line = NULL;
  return 0;
}

/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  <Bucket Maker: stores strings in chunks>
  Program #2
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char **argv)
{
  int X = 100;

  //Didn't check for case when argv[i] < 20 or > 100000
  if (argc <= 2)
    {
      X = atoi(argv[1]);
    }
  else
    {
      fprintf(stdout, "Command Line arguments invalid\n");
      return 1;
    }
  
  char *word = NULL;
  int numberOfChunks = 0;
  char **bucket = NULL;
  int *chunkSpacesLeft = NULL;
  int bucketCap = 0;
  int createNewChunk = 0;
  
  while(fscanf(stdin, "%ms", &word) != EOF)
    {
      if (numberOfChunks == 0)
	{
	  createNewChunk = 1;
	}
      for (int i = 0; i < numberOfChunks; i++)
	{
	  int spacesCheck = 0;
	  spacesCheck = chunkSpacesLeft[i] - (strlen(word)+1);
	  if (spacesCheck >= 0)
	    {
	      for(int j = 0; j <= strlen(word); j++)
		{
		  if(j == strlen(word))
		    {		      
		      if(chunkSpacesLeft[i] > 0)
			{
			  bucket[i][(X-chunkSpacesLeft[i])] = '\0';
			  chunkSpacesLeft[i]--;
			}
		    }
		  else
		    {
		      bucket[i][(X-chunkSpacesLeft[i])] = word[j];
		      chunkSpacesLeft[i]--;
		    }
		}
	      break;
	    }
	  if (i == numberOfChunks-1 && spacesCheck < 0)
	    {
	      createNewChunk = 1;
	    }
	}
      if(createNewChunk == 1)
	{
	  bucketCap++;
	  char **tempBucket = (char **)malloc(bucketCap * sizeof(char *));
	  int *tempChunkSpacesCounter = (int *)malloc(bucketCap * sizeof(int));
	  for(int i = 0; i < numberOfChunks; i++)
	    {
	      tempBucket[i] = bucket[i];
	      tempChunkSpacesCounter[i] = chunkSpacesLeft[i]; 
	    }
	  free(bucket);
	  free(chunkSpacesLeft);
	  bucket = tempBucket;
	  chunkSpacesLeft = tempChunkSpacesCounter;
	  numberOfChunks++;
	  bucket[numberOfChunks - 1] = (char *)malloc(X * sizeof(char));
	  chunkSpacesLeft[numberOfChunks - 1] = X;
	  for(int j = 0; j <= strlen(word); j++)
	    {
	      if(j == strlen(word))
		{
		  bucket[numberOfChunks-1][(X-chunkSpacesLeft[numberOfChunks-1])] = '\0';
		  chunkSpacesLeft[numberOfChunks-1]--;
		}
	      else
		{
		  bucket[numberOfChunks-1][(X-chunkSpacesLeft[numberOfChunks-1])] = word[j];
		  chunkSpacesLeft[numberOfChunks-1]--;
		}
	    }
	  createNewChunk = 0;
	}
      free(word);
      word = NULL;
    }
  for (int i = 0; i < numberOfChunks; i++)
    {
      if (numberOfChunks != 0)
	{
	  fprintf(stdout, "%*d: ", 6, X-chunkSpacesLeft[i]);
	  for(int j = 0; j < (X-chunkSpacesLeft[i]); j++)
	    {
	      if (j == (X-chunkSpacesLeft[i])-1)
		{

		}
	      else if (bucket[i][j] == '\0')
		{
		  fprintf(stdout," ");
		}
	      else
		{
		  fprintf(stdout, "%c", bucket[i][j]);
		}
	    }
	  printf("\n");
	}
      free(bucket[i]);
    }
  free(bucket);
  free(chunkSpacesLeft);
  
  return 0;
}

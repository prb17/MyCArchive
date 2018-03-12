/*
  Group 9
  Peter Brady
  Luojia Liu
  Mike hollingsworth
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
  int x = 0;
  int done = 0;
  
  while(done == 0)
    {
      fscanf(stdin, "%d", &x);
      fprintf(stdout, "%d\n", x);
      if (x == 1)
	{
	  done = 1;
	  continue;
	}
      if (x == 2)
	{
	  int *nums = (int *)malloc(3 * sizeof(int));
	  size_t capacity = 3;
	  int value = 0;
	  int count = 0;
	  int done2 = 0;
	  while(done2 == 0)
	    {
	      fscanf(stdin, "%d", &value);
	  if (value == 0)
	    {
	      done2 = 1;
	      continue;
	    }
	  if(count == capacity)
		{
		  int *temp = (int *)malloc((capacity + 1) * sizeof(int));
		  capacity++;
		  for(size_t i = 0; i < capacity; i++)
		    {
		      temp[i] = nums[i];
		    }
		  free(nums);
		  nums = temp;
		}
	      nums[count] = value;
	      count++;
	      
	    }
	  int sum = 0;
	  for(int i = 0; i < count; i++)
	    {
	      fprintf(stdout, "%d", nums[i]);
	      sum += nums[i];
	      printf("\n");
	    }
	  fprintf(stdout, "%d", sum); 
	}
      if (x == 3)
	{
	  int *nums = (int *)malloc(3 * sizeof(int));
	  size_t capacity = 3;
	  int value = 0;
	  int count = 0;
	  int done3 = 0;
	  while(done3 == 0)
	    {
	      fscanf(stdin, "%d", &value);
	      if (value == 0)
		{
		  done3 = 1;
		  continue;
		}
	      if(count == capacity)
		{
		  int *temp = (int *)malloc((capacity * 2) * sizeof(int));
		  capacity++;
		  for(size_t i = 0; i < capacity; i++)
		    {
		      temp[i] = nums[i];
		    }
		  free(nums);
		  nums = temp;
		}
	      nums[count] = value;
	      count++;

	    }
	  int sum = 0;
	  for(int i = 0; i < count; i++)
	    {
	      fprintf(stdout, "%d", nums[i]);
	      sum += nums[i];
	      printf("\n");
	    }
	  fprintf(stdout, "%d", sum);
	}
      if (x == 4)
	{
	  int *words = (int *)malloc(2 * sizeof(int));
	  //size_t capacity = 8;
	  int value = 0;
	  int count = 0;
	  //int done3 = 0;
	  fscanf(stdin, "%9x", &value);
	  words[0] = value;
	  fprintf(stdout, "%x\n", &words[0]);	  
	  
	}
      done = 1;
	
    }
  
}

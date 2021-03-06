#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	int *nums = (int *)malloc(10 * sizeof(int));
	size_t size = 0;
	size_t capacity = 10;

	int value = 0;
	while(fscanf(stdin, "%d", &value) != EOF)
	{
		nums[size] = value;
		size++;
	}


	for(size_t i=0; i<size; i++)
	{
		fprintf(stdout, "%d", nums[i]);
		if((i+1) < size)
		{
			fprintf(stdout, ", ");
		}
	}
	fprintf(stdout, "\n");

	char *buffer = (char *)malloc(20 * sizeof(char));
	for(size_t i=0; i<19; i++)
	{
		buffer[i] = 'A' + i;
	}
	buffer[19] = '\0';

	fprintf(stdout, "Buffer: %s\n", &buffer[0]);

	for(size_t i=0; i<size; i++)
	{
		fprintf(stdout, "%d", nums[i]);
		if((i+1) < size)
		{
			fprintf(stdout, ", ");
		}
	}
	fprintf(stdout, "\n");


	free(buffer);
	buffer = NULL;
	free(nums);
	nums = NULL;
	return 0;
}

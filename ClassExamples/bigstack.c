#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
//	int array[10000000];
//	int array[1000000];
	int *array = (int *)malloc(10000000 * sizeof(int));
	array[0] = 15;

	fprintf(stdout, "%d\n", array[0]);
	return 0;
}

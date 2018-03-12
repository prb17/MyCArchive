#include<stdlib.h>
#include<stdio.h>

int func(int array[4])
{
	array = NULL;	
	fprintf(stdout, "%ld\n", sizeof(array));
//	fprintf(stdout, "%ld\n", sizeof(int[4]));
	return 0;
}


int main(int argc, char **argv)
{
	int data[4] = {1,2,3,4};
	func(data);

	int hmm[10] = {1,2,3,4,5,6,7,8,9,10};
	func(hmm);

//	data = NULL;

	return 0;
}

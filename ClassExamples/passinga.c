#include<stdio.h>
#include<stdlib.h>


void swap(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}

void otherSwap(int first, int second)
{
	return swap(&first, &second);
}


int main(int argc, char **argv)
{
	int number = 5;
	int value = 10;

	fprintf(stdout, "Number: %d, Value: %d\n", number, value);
	swap(&number, &value);
	fprintf(stdout, "Number: %d, Value: %d\n", number, value);
	otherSwap(number, value);
	fprintf(stdout, "Number: %d, Value: %d\n", number, value);




	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char **argv)
{
	int first = 0x20101000;
	char word[10];
	int second = 0x20101000;
	int nums[10];

	fprintf(stdout, "Enter a word:\n");

	//Unsafe scanf:
	fscanf(stdin, "%s", &word[0]);
	fscanf(stdin, "%d", &nums[13]);

	fprintf(stdout, "Values (0x20101000): %x, %x\n", first, second);
	fprintf(stdout, "Word: '%s'\n", &word[0]);


	return 0;
}

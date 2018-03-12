#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

void printBinary(FILE*, int);

int main(int argc, char **argv)
{
	int number = 0;
	fprintf(stdout, "Enter a number: ");
	fscanf(stdin, "%d", &number);

	char *buffer = (char *)malloc(10 * sizeof(char));
	fprintf(stdout, "Enter an operation: ");
	fscanf(stdin, "%2s", buffer);

	int operand = 0;
	fprintf(stdout, "Enter second number: ");
	fscanf(stdin, "%d", &operand);

	printBinary(stdout, number);
	fprintf(stdout, "Operation: %s\n", buffer);
	printBinary(stdout, operand);

	fprintf(stdout, "------------------------------------\n");

	if(!strcmp(buffer, "&&"))
	{
		int result = number && operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "&"))
	{
		int result = number & operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "||"))
	{
		int result = number | operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "|"))
	{
		int result = number | operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "^"))
	{
		int result = number ^ operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "<<"))
	{
		int result = number << operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, ">>"))
	{
		int result = number >> operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "+"))
	{
		int result = number + operand;
		printBinary(stdout, result);
	}
	else if(!strcmp(buffer, "-"))
	{
		int result = number - operand;
		printBinary(stdout, result);
	}






	free(buffer);
	buffer = NULL;
	return 0;
}

void printBinary(FILE* outFile, int num)
{
	//FILE* outFile = argument[0]
	//int num = argument[1]

	char *buffer = (char *)malloc(33 * sizeof(char));
	buffer[32] = '\0';

	int div = 2;

	for(int i=31; i>=0; i--)
	{
		if(num & 0x1)
		{
			buffer[i] = '1';
		}
		else
		{
			buffer[i] = '0';
		}
		num = num >> 1;
//		num = num / div;
	}
	//One possibility, swap all the characters.
	fprintf(outFile, "%s 0x", buffer);

	for(int i=0; i<32; i+=4)
	{
		int value = 0;
		for(int j=i; j<(i+4); j++)
		{
			value <<= 1;
			if(buffer[j] == '1')
			{
				value += 1;
			}
		}

		assert((value >= 0) && (value <= 15));
//		if(value >= 16)
//		{
//			fprintf(stderr, "I done screwed up.\n");
//			exit(1);
//		}
		if(value < 10)
		{
			fprintf(outFile, "%d", value);
		}
		else
		{
			int diff = value - 10;
			char letter = 'A' + diff;
			fprintf(outFile, "%c", letter);
		}
	}

	fprintf(outFile, "\n");
	free(buffer);
	buffer = NULL;
}

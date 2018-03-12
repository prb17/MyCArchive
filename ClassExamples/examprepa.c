#include<stdio.h>

int main(int argc, char **argv)
{
/*	int num = 0;
	fscanf(stdin, "%2d", &num);

	fprintf(stdout, "%d\n", num);
*/
	if(argc != 2)
	{
		exit(1);
	}

	char *ignore = argv[1];

	char letter, previous = '\0';
	int doPrint = 1;
	while(fscanf(stdin, "%c", &letter) != EOF)
	{
		int doIgnore = 0;
		for(int i=0; i<strlen(ignore); i++)
		{
			if(ignore[i] == letter)
			{
				doIgnore = 1;
			}
		}

		if(doIgnore)
		{
			continue;
		}

		if(isupper(previous))
		{
			fprintf(stdout, "%c", previous);
		}

		if(islower(letter))
		{
			if(doPrint)
			{
				fprintf(stdout, "%c", letter);
				doPrint = 0;
			}
			else
			{
				doPrint = 1;
			}
		}

		previous = letter;
	}

	return 0;
}

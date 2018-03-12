#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	fprintf(stdout, "Num of args: %d\n", argc);
	for(int i=0; i<argc; i++)
	{
		fprintf(stdout, "Arg %d: %s\n", i, argv[i]);
		fprintf(stdout, "Location %p\n", argv[i]);
		for(int j=0; j<strlen(argv[i]); j++)
		{
			argv[i][j]++;
			fprintf(stdout, "Char %d: %c\n", j, argv[i][j]);
		}
	}

	int number = 0;
	fprintf(stdout, "Enter a number: ");

	int *iPtr = &number;

	fscanf(stdin, "%d", &number);

	//iPtr = 15;
	*iPtr = 15;

	printf("%d\n", number);
//	int number = Scanner.nextInt();

//	char letter = '\0';
//	float fp = 0.0;
//	result = fscanf(stdin, "%c %f", &letter, &fp);

	//char word[10];
	char *word = NULL;
//	word = (char *)malloc(10 * sizeof(char));

	//result = fscanf(stdin, "%s", word);
	fprintf(stdout, "Enter a string\n");
	char letter = '\0';
	fscanf(stdin, "%c", &letter);
	fscanf(stdin, " %m[^\n]s", &word);
	fscanf(stdin, "%c", &letter);

	fprintf(stdout,"You entered '%s'\n", &word[0]);

	free(word);
	word = NULL;

	int running = 1;
	while(running)
	{
		size_t sizeOfWordAllocation = 0;
		ssize_t charsRead = getline(&word, &sizeOfWordAllocation, stdin);

		if((charsRead == -1) && (errno != 0))
		{
			fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
			return 1;
		}
		if((charsRead == -1) && (errno == 0))
		{
			running = 0;
		}
		if(charsRead > 0)
		{
			if(word[charsRead - 1] == '\n')
			{
				word[charsRead - 1] = '\0';
				charsRead--;
			}
		}

		fprintf(stdout, "We read: %ld\n", charsRead);
		fprintf(stdout, "We read the line: '%s'\n", &word[0]);
		fprintf(stdout, "Size of allocation: %ld\n", sizeOfWordAllocation);

		free(word);
		word = NULL;
	}



	return 0;
}

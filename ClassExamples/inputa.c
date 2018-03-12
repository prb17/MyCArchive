#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	fprintf(stdout, "Argc: %d\n", argc);

	for(int i=0; i<argc; i++)
	{
		fprintf(stdout, "Arg %d: '%s'\n", i, argv[i]);
		fprintf(stdout, "Location %p\n", argv[i]);
		for(int j=0; j<strlen(argv[i]); j++)
		{
//			argv[i][j]++;
			fprintf(stdout, "Char %d: %c\n", j, argv[i][j]);
		}
	}

	int number = 0;
	fprintf(stdout, "Enter a number: ");
	int result = fscanf(stdin, "%d", &number);
	if(result == EOF)
	{
		fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
	}

	fprintf(stdout, "You entered %d\n", number);

	int *iPtr = &number;
	*iPtr = 15;

	fprintf(stdout, "I changed it to %d\n", number);

	//fscanf(stdin, "%d %d %d", &number, &number, &number);
	//fprintf(stdout, "Final changed to %d\n",number);

	char *word = NULL;
	//word = (char *)malloc(10 * sizeof(char));
	//fscanf(stdin, "%s", &word[0]);
	char letter = '\0';
	fscanf(stdin, "%c", &letter);
	fscanf(stdin, "%m[^\n]s", &word);
	fscanf(stdin, "%c", &letter);

	if(word)
	{
		fprintf(stdout, "You entered: '%s'\n", &word[0]);
	}
	else
	{
		fprintf(stdout, "Word is invalid\n");
	}
	free(word);
	word = NULL;

	int running = 1;
	while(running)
	{
		size_t memorySizeOfWord = 0;
		ssize_t charsRead = getline(&word, &memorySizeOfWord, stdin);

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

		fprintf(stdout, "We read: %ld characters\n", charsRead);
		fprintf(stdout, "The line read: '%s'\n", &word[0]);
		fprintf(stdout, "Word allocation size: %ld\n", memorySizeOfWord);

		free(word);
		word = NULL;
	}


	

	return 0;
}

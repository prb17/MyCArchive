#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	char *word = NULL, *otherWord = NULL;
//	char *word = (char *)malloc(6 * sizeof(char));
//	char *otherWord = (char *)malloc(31 * sizeof(char));;
	fprintf(stdout, "Enter two words\n");
	fscanf(stdin, "%ms", &word);
	fscanf(stdin, "%ms", &otherWord);


	fprintf(stdout,"You entered '%s' and '%s'\n", word, otherWord);
	if(!strcmp(word, otherWord))
	{
		fprintf(stdout, "Strings are identical\n");
	}
	else
	{
		fprintf(stdout, "Strings not identical\n");
	}

	size_t totalLength = strlen(word) + strlen(otherWord);
	char *newWord = (char *)malloc(sizeof(char) * (totalLength+1));
	strcpy(&word[2], &word[0]);
	strcpy(newWord, word);
	strcat(newWord, otherWord);
	fprintf(stdout,"You entered '%s' and '%s'\n", word, otherWord);
	fprintf(stdout,"Combined word is: '%s'\n", newWord);

	free(word);
	free(otherWord);
	word = NULL;
	otherWord = NULL;
	free(newWord);
	newWord = NULL;
	return 0;
}

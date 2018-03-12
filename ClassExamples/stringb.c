#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	char *word = NULL, *otherWord = NULL;
//	char *word = (char *)malloc(6 * sizeof(char));
//	char *otherWord = (char *)malloc(7 * sizeof(char));
	fprintf(stdout, "Enter in two words\n");
	fscanf(stdin, "%ms", &word);
	fscanf(stdin, "%ms", &otherWord);

	fprintf(stdout, "You entered '%s' and '%s'\n", word, otherWord);
	fprintf(stdout, "Length of word: %ld\n", strlen(word));
	fprintf(stdout, "Length of otherWord: %ld\n", strlen(otherWord));

	if(!strcmp(word, otherWord))
	{
		fprintf(stdout, "The words match\n");
	}
	else
	{
		fprintf(stdout, "The words differ\n");
	}

	size_t spaceNeeded = strlen(word) + strlen(otherWord) + 1;
	char *newWord = (char *)malloc(spaceNeeded * sizeof(char));
	for(size_t i=0; i<=strlen(word); i++)
	{
		newWord[i] = word[i];
	}
	//newWord[strlen(word)] = '\0';
	strcpy(newWord, word);

//	strcpy(&newWord[2], &newWord[0]);
//	strcpy(newWord + 2, newWord + 0);
//	strcpy(newWord, "applebanana");

	free(word);
	word = newWord;
	newWord = NULL;

	strcat(word, otherWord);
	fprintf(stdout, "The concatenated word is '%s'\n", word);
	fprintf(stdout, "Word 1: '%s' Word 2: '%s'\n", word, otherWord);

	free(word);
	word = NULL;
	free(otherWord);
	otherWord = NULL;
	return 0;
}

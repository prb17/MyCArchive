#include<stdio.h>

int main(int argc, char **argv)
{
	fprintf(stdout, "Hello world!\n");

	int number = 5;
	float floatnum = 37.42;
//	int x = (int)floatnum;
	char letter = 'a';

	fprintf(stdout, "The number is: %d\n", number);
	fprintf(stdout, "The float is %f and the letter is %c\n", floatnum, letter);

	//Static declaration of an array of 10 chars
	char word[10];
	word[0] = 'a';
	word[1] = 'p';
	word[2] = 'p';
	word[3] = 'l';
	word[4] = 'e';
	word[5] = '\0';

	fprintf(stdout, "The word is '%s'\n", &word[0]);
	fprintf(stdout, "The word is '%s'\n", word);
	//fprintf(stdout, "The word is '%s'\n", &word);


	char bird[10] = "bird";
	fprintf(stdout, "'%s' is the word.\n", &bird[0]);
	fprintf(stdout, "'%s' is the word.\n", bird);


	return 0;
}


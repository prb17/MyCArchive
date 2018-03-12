#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

struct complex
{
	int a, b, c;
	double d, e, f;
	short g, h;
	void *i;
};

int main(int argc, char **argv)
{
/*
	FILE* outfile = stdout;
	fprintf(outfile, "Word\n");

	outfile = fopen("simple", "w+");
	fprintf(outfile, "Bird\n");

	fclose(outfile);
*/
//	int file = open("simple", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	int file = open("simple", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(file == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}

	int value = 0x65001161;

	ssize_t writeResult = write(file, &value, 4);
	if(writeResult == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}

	cout << "Value: " << value << endl;
	value = 0;
	cout << "Value: " << value << endl;

	lseek(file, 0, SEEK_SET);

	ssize_t readResult = read(file, &value, 4);
	if(readResult == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}
	cout << "Value: " << value << endl;

	srand(100);
	unsigned char *buffer = (unsigned char *)malloc(20 * sizeof(unsigned char));
	for(size_t i=0; i<20; i++)
	{
		int randData = rand() % 256;
		buffer[i] = randData;
		cout << "Inserting " << randData << " into location: " << i << endl;
	}
	write(file, buffer, 20);
	memset(buffer, 0, 20);

	lseek(file, 4, SEEK_SET);
	read(file, buffer, 20);
	for(size_t i=0; i<20; i++)
	{
		cout << "Read " << (int)buffer[i] << " from location: " << i << endl;
	}


	complex junk;
	write(file, &junk, sizeof(complex));
	lseek(file, 24, SEEK_SET);
	read(file, &junk, sizeof(complex));


	free(buffer);
	buffer = NULL;

	if(close(file) == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}
	return 0;
}

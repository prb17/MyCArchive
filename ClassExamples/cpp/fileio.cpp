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
	int x, y, z;
	void* a;
	double b;
	short c;
};

int main(int argc, char **argv)
{
//	FILE* outfile = stdout;
//	fprintf(outfile, "Text\n");

//	outfile = fopen("sample", "w+");
//	fprintf(outfile, "Text\n");

//	fclose(outfile);

	int value = 0x65001161;

	int file = open("sample", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
//	int file = open("sample", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if(file == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}

	ssize_t writeResult = write(file, &value, 4);
	if(writeResult == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}

	cout << "Value: " << hex << value << dec << endl;
	value = 0;
	cout << "Value: " << setw(10) << value << endl;

	lseek(file, 0, SEEK_SET);

	ssize_t readResult = read(file, &value, 4);
	if(readResult == -1)
	{
		fprintf(stderr, "Error (%d): %s\n", errno, strerror(errno));
		return 1;
	}
	cout << "Value: " << hex << value << dec << endl;

	unsigned char *buffer = (unsigned char *)malloc(20 * sizeof(unsigned char));

	srand(100);

	for(int i=0; i<20; i++)
	{
		int randValue = rand() % 256;
		cout << "Going to store: " << randValue << " at location: " << i << endl;
		buffer[i] = (unsigned char)randValue;
	}
	write(file, buffer, 20);

	memset(buffer, 0, 20);

	lseek(file, 4, SEEK_SET);
	read(file, buffer, 20);

	for(int i=0; i<20; i++)
	{
		cout << "Read in: " << (int)buffer[i] << " from location: " << i << endl;
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

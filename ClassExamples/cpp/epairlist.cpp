#include<iostream>
#include<string>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

int main(int argc, char** argv)
{
	unsigned short cases = 1;

	//int commModel[4] = {0,1,2,3}; //1110 0100		-> e4
	//Both directions: 0001 1011		1b

	string cmd1 = "ls -la";
	string cmd2 = "pwd";

	int fd = open("file.con", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR, S_IWUSR);
	write(fd, &cases, sizeof(unsigned short));

	unsigned char cModel = 0xe4;
	write(fd, &cModel, sizeof(unsigned char));
	
	int sizeA = cmd1.size();
	int sizeB = cmd2.size();
	write(fd, &sizeA, sizeof(int));
	write(fd, &sizeB, sizeof(int));
	write(fd, cmd1.c_str(), sizeA);
	write(fd, cmd2.c_str(), sizeB);



	close(fd);


	return 0;
}

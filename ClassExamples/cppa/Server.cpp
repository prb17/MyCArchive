#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cstring>
#include<cerrno>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<unistd.h>
#include<signal.h>
#include<algorithm>

using namespace std;

void sigint_handler(int sig)
{
	write(STDOUT_FILENO, "Hello\n", 6);
	_exit(1);
}

void sigchld_handler(int sig)
{
	write(STDOUT_FILENO, "Sigchild handler\n", 17);
	int status;
	int waitValue;
	while((waitValue = waitpid(-1, &status, WNOHANG|WUNTRACED)) > 0)
	{
		write(STDOUT_FILENO, "Zombie cleaned\n", 15);
	}
	if((waitValue == -1) && (errno != ECHILD))
	{
		write(STDOUT_FILENO, "ERROR\n", 6);
		_exit(1);
	}
}

int main(int argc, char** argv)
{
	if(signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("Sigint override failed");
		exit(1);
	}

	if(signal(SIGCHLD, sigchld_handler) == SIG_ERR)
	{
		perror("Sigchld override failed");
		exit(1);
	}


	int mySocket;
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mySocket == -1)
	{
		perror("Socket creation failed");
		return 1;
	}

	sockaddr_in serve;
	memset(&serve, 0, sizeof(sockaddr_in));
	serve.sin_family = AF_INET;
	serve.sin_addr.s_addr = htonl(INADDR_ANY);

	bool retry = true;
	int bound = 0;
	unsigned short port = 10000;
	while(retry)
	{
		if(port > 10500)
		{
			perror("Tried and failed too many ports");
			return 1;
		}

		serve.sin_port = htons(port);
		bound = bind(mySocket, (sockaddr*)&serve, sizeof(sockaddr_in));
		if(bound == -1)
		{
			port++;
			continue;
		}

		linger linger_option = {1, 128};
		setsockopt(mySocket, SOL_SOCKET, SO_LINGER, &linger_option, sizeof(linger));

		if(listen(mySocket, 128) == -1)
		{
			port++;
			continue;
		}
		retry = false;
	}

	cout << "We are listening on port: " << port << endl;

	bool keepRunning = true;
	while(keepRunning)
	{
		sockaddr_in otherAddr;
		memset(&otherAddr, 0, sizeof(sockaddr_in));
		socklen_t otherLen;
		memset(&otherLen, 0, sizeof(socklen_t));
		otherLen = sizeof(sockaddr_in);

		cout << "Waiting for connection: " << endl;
		int otherSocket = accept(mySocket, (sockaddr*)&otherAddr, &otherLen);
		if(otherSocket == -1)
		{
			perror("Accept failed");
			continue;
		}

		pid_t cid = fork();
		if(cid == -1)
		{
			perror("Fork failed");
			return 1;
		}
		if(cid != 0)
		{
			//parent is lazy, let the child do everything.
			close(otherSocket);
			continue;
		}

		cout << "Connection from IP: ";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 24) & 0xff) << ".";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 16) & 0xff) << ".";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 8) & 0xff) << ".";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 0) & 0xff) << " ";
		cout << " port: " << ntohs(otherAddr.sin_port) << endl;

		write(otherSocket, "Apple", 5);

		char buffer[3];
		ssize_t totalRead = 0;
		ssize_t readAmt = 0;
		ssize_t want = 3;

		while(want > 0)
		{
			readAmt = read(otherSocket, buffer + totalRead, want);
			cerr << "Reading first 3 bytes: Got: " << readAmt << endl;
//			readAmt = read(otherSocket, &buffer[totalRead], want);
			if(readAmt == -1)
			{
				perror("Read failed");
				exit(1);
			}
			if(readAmt == 0)
			{
				cerr << "Not enough data" << endl;
				exit(1);
			}
			totalRead += readAmt;
			want -= readAmt;
		}

		want = atoi(buffer) - 3;
		if(want < 0)
		{
			cerr << "Incorrect number of bytes specified" << endl;
			exit(1);
		}
		char* data = new char[want+1];
		totalRead = 0;

		while(want > 0)
		{
			readAmt = read(otherSocket, data + totalRead, want);
			cerr << "Reading remaining bytes: Got: " << readAmt << endl;
			if(readAmt == -1)
			{
				perror("Read failed");
				exit(1);
			}
			if(readAmt == 0)
			{
				cerr << "Not enough data" << endl;
				exit(1);
			}
			totalRead += readAmt;
			want -= readAmt;
		}
		data[atoi(buffer)-3] = '\0';
		cout << data << endl;


		delete [] data;
/*
		char buffer[11];
		ssize_t readAmt = 0;
		while((readAmt = read(otherSocket, buffer, 10)) != 0)
		{
			if(readAmt == -1)
			{
				perror("Read failed");
				exit(errno);
			}
			buffer[readAmt] = '\0';
			cout << buffer << endl;

			for(ssize_t i=0; i<readAmt; i++)
			{
				buffer[i]++;
			}
			write(otherSocket, buffer, readAmt);
		}

*/
		cout << "Closing connection" << endl;
		close(otherSocket);
		close(mySocket);
		exit(0);
	}

	int status;
	while(wait(&status) != -1)
	{
		//check wait conditions
	}
	//check errors on wait (ECHILD is ok).

	close(mySocket);

	return 0;
}

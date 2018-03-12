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
	write(STDOUT_FILENO, "SIGCHLD\n", 8);

	int status;
	int waitValue;
	while((waitValue = waitpid(-1, &status, WNOHANG|WUNTRACED)) > 0)
	{
		if(waitValue != 0)
		{
			write(STDOUT_FILENO, "Zombie killed\n", 14);
		}
	}
	if((waitValue == -1) && (errno != ECHILD))
	{
		write(STDOUT_FILENO, "ERROR\n", 6);
		return;
	}
}

int main(int argc, char** argv)
{
	if(signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("SIGINT replacement failed");
		exit(1);
	}
	if(signal(SIGCHLD, sigchld_handler) == SIG_ERR)
	{
		perror("SIGCHLD replacement failed");
		exit(1);
	}
	


	//Create Socket
	int mySocket = 0;
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mySocket == -1)
	{
		perror("Socket creation failed");
		return 1;
	}

	//Initialize socket settings
	sockaddr_in serve;
	memset(&serve, 0, sizeof(sockaddr_in));
	serve.sin_family = AF_INET;
	serve.sin_addr.s_addr = htonl(INADDR_ANY);

	//Port acquisition:
	bool retry = true;
	int bound = 0;
	unsigned short port = 10000;
	while(retry)
	{
		if(port > 10500)
		{
			cerr << "Could not find a valid port: " << errno << " ";
			cerr << strerror(errno) << endl;
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
	//We have a port number and are able to accept connections.
	cout << "We have port number: " << port << endl;

	bool keepRunning = true;
	while(keepRunning)
	{
		sockaddr_in otherAddr;
		memset(&otherAddr, 0, sizeof(sockaddr_in));
		socklen_t otherLen;
		memset(&otherLen, 0, sizeof(socklen_t));
		otherLen = sizeof(sockaddr_in);


		cout << "About to wait to accept a connection" << endl;
		int otherSocket = accept(mySocket, (sockaddr*)&otherAddr, &otherLen);
		if(otherSocket == -1)
		{
			perror("Accept failed");
			return 2;
		}

		pid_t child = fork();
		if(child == -1)
		{
			perror("Fork failed");
			return 3;
		}
		if(child != 0)
		{
			//parent just closes its copy of the connection
			//Parent goes to wait for new connections
			close(otherSocket);
			continue;
		}

		cout << "Connection from IP: ";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 24) & 0xff) << ".";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 16) & 0xff) << ".";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 8) & 0xff) << ".";
		cout << ((ntohl(otherAddr.sin_addr.s_addr) >> 0) & 0xff) << ".";
		cout << " port number: " << ntohs(otherAddr.sin_port) << endl;

		write(otherSocket, "Hello", 5);

		char buffer[3];
		ssize_t want = 3;
		ssize_t totalRead = 0;
		ssize_t amtRead = 0;

		while((amtRead = read(otherSocket, buffer + totalRead, want)))
		{
			cerr << "Amount read: " << amtRead << endl;
			cerr << "Totalread: " << totalRead << endl;
			if(amtRead == -1)
			{
				perror("Read error");
				exit(1);
			}

			totalRead += amtRead;
			want -= amtRead;

		}

		if(totalRead != 3)
		{
			cerr << "Did not read enough" << endl;
			exit(1);
		}

		ssize_t leftover = atoi(buffer) - 3;
		cerr << "Leftover: " << leftover << endl;
		char* data = new char[leftover+1];
		totalRead = 0;
		while(leftover > 0)
		{
			cerr << "Amount read: " << amtRead << endl;
			cerr << "Totalread: " << totalRead << endl;
			amtRead = read(otherSocket, data + totalRead, leftover);
			if(amtRead == -1)
			{
				perror("Read2 error");
				exit(1);
			}
			if(amtRead == 0)
			{
				perror("Not enough data");
				exit(2);
			}
			totalRead += amtRead;
			leftover -= amtRead;
		}
		data[atoi(buffer) - 3] = '\0';

		cout << data << endl;

		delete [] data;

/*
		char buffer[11];
		ssize_t readResult = 0;
		while((readResult = read(otherSocket, buffer, 10)) > 0)
		{
			if(readResult == 0)
			{
				break;
			}
			if(readResult == -1)
			{
				perror("Read failed");
				break;
			}
			buffer[readResult] = '\0';
			cout << "Received: " << buffer << endl;
		}
*/
		close(otherSocket);
		exit(1);
	}

	int status;
	while(wait(&status) != -1)
	{
		//fill in messages
	}


	return 0;
}

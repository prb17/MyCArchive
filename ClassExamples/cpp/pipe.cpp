#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<iomanip>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>

using namespace std;

int main(int argc, char** argv)
{

	bool isChild = false;

	int pipefd[2];
	if(pipe(pipefd) == -1)
	{
		perror("Pipe failed: ");
		exit(2);
	}
	int readEnd = pipefd[0];
	int writeEnd = pipefd[1];


	if(fork() == 0)
	{
		char **args = (char **)malloc(argc * sizeof(char*));
		memset(args, 0, argc*sizeof(char*));
		for(int i=1; i<argc; i++)
		{
			args[i-1] = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(args[i-1], argv[i]);
		}
		args[argc-1] = NULL;

		close(STDOUT_FILENO);
		dup(writeEnd);

		close(readEnd);
		close(writeEnd);
		execvp(args[0], args);
		perror("Failed exec");

		for(int i=0; i<argc; i++)
		{
			free(args[i]);
		}
		free(args);
		exit(1);
	}

	dup2(readEnd, STDIN_FILENO);
	close(readEnd);
	close(writeEnd);
	cout << "Program ending" << endl;

	if(isChild)
	{
		int x;
		cin >> x;
		return x;
	}

	int pPipe[2];
	if(pipe(pPipe) == -1)
	{
		perror("pPipe error: ");
		exit(3);
	}

	if(fork() == 0)
	{
		dup2(pPipe[0], STDIN_FILENO);
		close(pPipe[1]);
		close(pPipe[0]);

		const char *args[2];
		string command = "cat";
		args[1] = NULL;
		args[0] = command.c_str();

		execvp(args[0], (char*const*)args);
		perror("Exec of cat failed: ");


		exit(1);
	}

	dup2(pPipe[1], STDOUT_FILENO);
	close(pPipe[0]);
	close(pPipe[1]);

	bool running = true;
	while(running)
	{
		char *buffer = (char *)malloc(100 * sizeof(char));

		ssize_t readAmt = read(STDIN_FILENO, buffer, 100);

		if(readAmt == -1)
		{
			perror("Read failed: ");
			exit(5);
		}
		if(readAmt == 0)
		{
			running = false;
		}
		else
		{
			for(ssize_t i=0; i<readAmt; i++)
			{
				buffer[i]++;
			}
			write(STDOUT_FILENO, buffer, readAmt);
		}



		free(buffer);
		buffer = NULL;
	}


	close(STDOUT_FILENO);

	int status = 0;
	pid_t child;
	while((child = wait(&status)) != -1)
	{
		if(WIFEXITED(status))
		{
			//Child Terminated Normally.
			int exitStatus = WEXITSTATUS(status);

			cerr << "Child " << child << " has terminated";
			cerr << " normally with value: " << exitStatus << endl;
		}
		else if(WIFSIGNALED(status))
		{
			int signalNum = WTERMSIG(status);
			cerr << "Child " << child << " has terminated ";
			cerr << "abnormally by signal: " << signalNum << endl;
		}
		else if(WIFSTOPPED(status))
		{
			int signalNum = WSTOPSIG(status);
			cerr << "Child " << child << " has stopped ";
			cerr << "by signal: " << signalNum << endl;
		}
		else if(WIFCONTINUED(status))
		{
			cerr << "Child " << child << " has been resumed" << endl;
		}
	}
	return 0;
}

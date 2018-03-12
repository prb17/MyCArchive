#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<cerrno>
#include<string.h>

using namespace std;

int main(int argc, char** argv)
{
	cout << "Enter a word: ";
	string input;
	cin >> input;

	bool isChild = false;
	for(size_t i=0; i<input.size(); i++)
	{
		if(!isChild)
		{
			pid_t childId = fork();
			if(childId == -1)
			{
				cout << "Fork failed: " << errno << ": " << strerror(errno) << endl;
				return 1;
			}
			if(childId == 0)
			{
				//argv[1] -> new argv[0],
				//argv[2] -> new argv[1],
				//NULL at the end.
				char** args = (char**)malloc(argc * sizeof(char*));
				for(int i=1; i<argc; i++)
				{
					args[i-1] = (char*)malloc((1 + strlen(argv[i])) * sizeof(char));
					strcpy(args[i-1], argv[i]);
				}
				args[argc-1] = NULL;

				execvp(args[0], args);

				perror("Failed exec");
//				isChild = true;
//				cout << "Child";
				for(int i=0; i<argc; i++)
				{
					free(args[i]);
				}
				free(args);

				return 1;
			}
		}
		cout << "Char " << setw(5) << i << ": " << input[i] << endl;
	}

	if(isChild)
	{
		cout << "Waiting child" << endl;
		int x;
		cin >> x;
		return x;
	}

	int status;
	pid_t childId;
	cout << "We are waiting for dead children" << endl;
	while((childId = wait(&status)) != -1)
	{
		if(WIFEXITED(status))
		{
			cout << "Child died normally: " << childId << endl;
			int exitStatus = WEXITSTATUS(status);
			cout << "Child returned " << exitStatus << endl;
		}
		else if(WIFSIGNALED(status))
		{
			int signalNum = WTERMSIG(status);
			cout << "Child died abnormally: " << childId << endl;
			cout << "Died by signal: " << signalNum << endl;
		}
		else if(WIFSTOPPED(status))
		{
			int signalNum = WSTOPSIG(status);
			cout << "Child was suspended: " << childId << endl;
			cout << "Suspended by signal: " << signalNum << endl;
		}
		else if(WIFCONTINUED(status))
		{
			cout << "Child was resumed: " << childId << endl;
		}
	}

	return 0;
}

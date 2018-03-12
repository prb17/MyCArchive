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
	string input;
	cout << "Enter in a single word: ";
	cin >> input;

	string depth = "child";
	bool isChild = false;
	for(size_t i=0; i<input.size(); i++)
	{
		if(!isChild)
		{
			if(fork() == 0)
			{
//				isChild = true;
//				cout << depth;
//				depth = "grand" + depth;
				char **args = (char **)malloc(argc * sizeof(char*));
				memset(args, 0, argc*sizeof(char*));

				for(int i=1; i<argc; i++)
				{
					args[i-1] = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
					strcpy(args[i-1], argv[i]);
				}
				args[argc-1] = NULL;

				execvp(args[0], args);

				perror("Failed exec");

				for(int i=0; i<argc; i++)
				{
					free(args[i]);
				}
				free(args);
//				kill(getpid(),9);
				exit(1);
			}
//			cout << "Something" << endl;
		}
		cout << "Char " << setw(5) << i << ": " << input[i] << endl;
	}

	cout << "Program ending" << endl;

	if(isChild)
	{
		int x;
		cin >> x;
		return x;
	}

	int status = 0;
	pid_t child;
	while((child = wait(&status)) != -1)
	{
		if(WIFEXITED(status))
		{
			//Child Terminated Normally.
			int exitStatus = WEXITSTATUS(status);

			cout << "Child " << child << " has terminated";
			cout << " normally with value: " << exitStatus << endl;
		}
		else if(WIFSIGNALED(status))
		{
			int signalNum = WTERMSIG(status);
			cout << "Child " << child << " has terminated ";
			cout << "abnormally by signal: " << signalNum << endl;
		}
		else if(WIFSTOPPED(status))
		{
			int signalNum = WSTOPSIG(status);
			cout << "Child " << child << " has stopped ";
			cout << "by signal: " << signalNum << endl;
		}
		else if(WIFCONTINUED(status))
		{
			cout << "Child " << child << " has been resumed" << endl;
		}
	}

	return 0;
}

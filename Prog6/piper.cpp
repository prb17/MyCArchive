/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Piper Program
  Program 6
*/

#include"ExecutionPair.h"
#include"Command.h"
#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>

using namespace std;

char** createArgsList(Command *C);

int main(int argc, char** argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "Unacceptable amount of arguments.\n");
      exit(1);
    }
  int fd = open(argv[1], O_CREAT | O_RDWR, S_IRUSR, S_IWUSR);
  if(fd == -1)
  {
    fprintf(stderr, "File could not be opened.\n");
    exit(2);
  }

  //Figure out how many cases exist
  unsigned char* fileContents = (unsigned char*)malloc(1000 * sizeof(unsigned char));
  read(fd, fileContents, 1000);
  unsigned short cases = fileContents[0] + fileContents[1];
  
  //Create the Execution Pairs
  ExecutionPair **epair = (ExecutionPair **)malloc(cases * sizeof(ExecutionPair *));
  for(int i = 0; i < cases; i++)
    {
      Command *C1 = new Command("");
      Command *C2 = new Command("");
      epair[i] = new ExecutionPair(C1, C2);
      epair[i]->setIO(fileContents[2]);
      int x = 0;
      int y = 0;
      for(int j = 3; j <= 6; j++)
	{
	  x += (int)fileContents[j];
	  y += (int)fileContents[j+4];
	}
      epair[i]->setSizeAB(x, y);
      string c1 = "";
      string c2 = "";
      string temp = "";
      for (int j = 11; j < 1000; j++)
	{
	  if(j-11 == epair[i]->getSizeA())
	    {
	      c1 = temp;
	      temp = "";
	    }
	  if(j-11-epair[i]->getSizeA() == epair[i]->getSizeB())
	    {
	      c2 = temp;
	      break;
	    }
	  temp += fileContents[j];
	}
      epair[i]->getCommands()[0]->setCommand(c1);
      epair[i]->getCommands()[1]->setCommand(c2);
    }
  for(int i = 0; i < cases; i++)
    {
      //defualt case
      if(epair[i]->getIO1()[0] == 0 && epair[i]->getIO2()[0] == 2 && epair[i]->getIO1()[1] == 1 && epair[i]->getIO2()[1] == 3)
	{
	  char*** args = (char ***)malloc(cases * sizeof(char **));
	  for(int k = 0; k < 2; k++)
	    {
	      args[i] = (char **)malloc(strlen(epair[i]->getCommands()[k]->getCommand().c_str()));
	      args[i] = createArgsList(epair[i]->getCommands()[k]);
	    }
	  
	  if(fork() == 0)
	    {
	      for(int k = 0; k < cases; k++)
		{
		  execvp(args[k][0], args[k]);
		}
	    }
	  
	}
      else
	{
	  int pipefd[2];
	  if(pipe(pipefd) == -1)
	    {
	      perror("Pipe failed: ");
	      exit(2);
	    }
	  
	  if(fork() == 0)
	    {
	      //close its pipes
	    }
	  if(fork() != 0)
	    {
	      
	    }
	} 
    }

  //Wait for child proceses to die and report behavior 
  int status = 0;
  pid_t child;
  while((child = wait(&status)) != -1)
    {
      if(WIFEXITED(status))
	{
	  //Child Terminated Normally.
	  int exitStatus = WEXITSTATUS(status);

	  cerr << "Child " << child << " terminated";
	  cerr << " with value " << exitStatus << "." << endl;
	}
      else if(WIFSIGNALED(status))
	{
	  int signalNum = WTERMSIG(status);
	  cerr << "Child " << child << " terminated ";
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

char** createArgsList(Command *C)
{
  char *arguments = (char *)malloc(strlen(C->getCommand().c_str()) * sizeof(char));
  for(int i = 0; i < (int)strlen(C->getCommand().c_str())+1; i++)
    {
      arguments[i] = (char)C->getCommand().c_str()[i];
    }
  string temp = "";
  int numArgs = 0;
  char** args = (char **)malloc(strlen(C->getCommand().c_str()) * sizeof(char *));;
  for(int i = 0; i < (int)strlen(arguments); i++)
    {
      if((char)arguments[i] == ' ' || i == (int)strlen(arguments)-1)
	{
	  args[numArgs] = (char *)malloc((strlen(temp.c_str())+1)*sizeof(char));
	  memset(args[numArgs], '\0', (strlen(temp.c_str())+1)*sizeof(char));
	  for(int j = 0; j < (int)strlen(temp.c_str()); j++)
	    {
	      args[numArgs][j] = (char)temp.c_str()[j];
	    }
	  temp = "";
	  numArgs++;
	}
      else if((char)arguments[i] == '.')
	{
	  args[numArgs] = (char *)malloc((strlen(temp.c_str())+1)*sizeof(char));
	  args[numArgs] = (char *)temp.c_str();
	  temp = "";
	}
      else
	{
	  temp += arguments[i];
	}
    }
  
  return args;
}

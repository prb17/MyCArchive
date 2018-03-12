/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Piper Program
  Program 6
*/

#include"ExecutionPair.h"
#include"Command.h"

using namespace std;

ExecutionPair::ExecutionPair()
{
  commands[0] = NULL;
  commands[1] = NULL;
}

ExecutionPair::ExecutionPair(Command *newCommand1, Command *newCommand2)
{
  commands = (Command **)malloc(2 * sizeof(Command *));
  commands[0] = (Command *)malloc(sizeof(Command));
  commands[0] = newCommand1;
  commands[1] = (Command *)malloc(sizeof(Command));
  commands[1] = newCommand2;
}

void ExecutionPair::setSizeAB(unsigned int a, unsigned int b)
{
  this->sizeA = a;
  this->sizeB = b;
}

int ExecutionPair::getSizeA()
{
  return this->sizeA;
}

int ExecutionPair::getSizeB()
{
  return this->sizeB;
}

void ExecutionPair::setIO(unsigned char cModel)
{
  this->oneIO[0] = cModel & 3; //1in
  this->oneIO[1] = (cModel & 12) >> 2; //1out
  this->twoIO[0] = (cModel & 48) >> 4; //2in
  this->twoIO[1] = (cModel & 192) >> 6; //2out
}
size_t* ExecutionPair::getIO1()
{
  return this->oneIO;
}

size_t* ExecutionPair::getIO2()
{
  return this->twoIO;
}

Command** ExecutionPair::getCommands()
{
  return this->commands;
}

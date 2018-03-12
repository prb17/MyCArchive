/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Piper Program
  Program 6
*/

#ifndef EXECUTIONPAIR_H
#define EXECUTIONPAIR_H
#include"Command.h"

using namespace std;

class ExecutionPair
{
public:
  ExecutionPair();
  ExecutionPair(Command*, Command*);
  ~ExecutionPair();

  void setSizeAB(unsigned int, unsigned int);
  void setIO(unsigned char);
  size_t* getIO1();
  size_t* getIO2(); 
  Command** getCommands(); 
  //Command* getCommand2();
  int getSizeA();
  int getSizeB();
  
private:
  Command** commands; //commands[0] = 1st command etc.
  int sizeA;
  int sizeB;
  size_t oneIO[2];
  size_t twoIO[2];
};

#endif

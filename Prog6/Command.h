/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Piper Program
  Program 6
*/
#ifndef COMMAND_H
#define COMMAND_H

#include<string>

using namespace std;

class Command
{
public:
  Command();
  Command(string c);
  ~Command();

  void setCommand(string);
  string getCommand();

private:
  string command;

};
#endif

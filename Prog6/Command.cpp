/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Piper Program
  Program 6
*/

#include"Command.h"
#include<string>

Command::Command()
  : command(NULL)
{
  command = "";
}

Command::Command(string newCommand)
  : command(newCommand)
{
  command = newCommand;
}

Command::~Command()
{}

void Command::setCommand(string newCommand)
{
  this->command = newCommand;
}

string Command::getCommand()
{
  return this->command;
}

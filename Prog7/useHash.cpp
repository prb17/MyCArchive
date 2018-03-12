/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Hash Slinging Slasher
  Program #7
*/

#include"Hash.h"
#include<vector>
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
  Hash_t* newHash = new Hash_t(12);
  char letter = '0';

  for(int i = 0; i < 20; i++)
    {
      newHash->insert((char)(letter + i));
    }
  char c = 'a';
  cout << newHash->toString(c) << endl;
  cout << newHash->toString((unsigned int)1) << endl;
  for(int i = 0; i < 12; i++)
    {
      if ( i == 8)
	{
	  cout << newHash->toString((unsigned int)1) << endl;
	}
      newHash->remove((char)(letter + i));
      cout << newHash->toString(letter) << endl;
      if ( i == 8)
	{
	  cout << newHash->toString((unsigned int)1) << endl;
	}
    }
  
  /*  newHash->remove('d');
  newHash->remove('p');
  newHash->remove('g');
  newHash->remove('[');
  newHash->remove('@');
  newHash->remove('y');
  */
  newHash->remove('W');
  cout << newHash->toString((unsigned int)1) << endl;
  cout << newHash->toString(c) << endl;

  //operator<<(cout, newHash);
  delete newHash;
  return 0;
}

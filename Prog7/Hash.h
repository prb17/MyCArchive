/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Hash Slinging Slasher
  Program #7
*/

#ifndef HASH_H
#define HASH_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Hash_t
{
public:
  unsigned int width;
  Hash_t();
  Hash_t(unsigned int buckets);
  Hash_t(unsigned int buckets, int(*hashfunc)(void*,size_t));
  ~Hash_t();  
  Hash_t* Copy(Hash_t* hash); 

  vector<vector<unsigned int> > getBuckets();
  bool insert(unsigned int);
  bool find(unsigned int);
  bool remove(unsigned int);
  string toString() const;
  string toString(unsigned int) const;
  
  bool insert(char);
  bool find(char);
  bool remove(char);
  string toString(char) const;
  
  size_t size() const;
  void incSize();
  void decSize();
private:
  int(*funcPtr)(void*, size_t);
  vector<vector<unsigned int> > buckets;
  size_t hashSize;
  size_t getIndex(void*,size_t) const;
  int getIndex(char) const;

  //private methods that can disassemble and reassemble unsigned ints
  //into chars*/
  unsigned int charPlacement(unsigned int) const;
  bool placeChar(size_t, size_t, unsigned int, unsigned int);
  bool switchChars(unsigned int, unsigned int, unsigned int, int, int);
};

ostream& operator<<(ostream& out, const Hash_t *rhs);

#endif

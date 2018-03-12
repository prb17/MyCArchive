/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Hash Slinging Slasher
  Program #7
*/

#include"Hash.h"
#include"Hasher.h"
#include<vector>
#include<string.h>
#include<iostream>
#include<openssl/evp.h>
#include<openssl/sha.h>
#include<sstream>

using namespace std;

Hash_t::Hash_t()
{
  width = 10;
  hashSize = 0;
  int(*b_h)(void*, size_t) = defaultHash;
  funcPtr = b_h;
  buckets.resize(width);
  for(size_t i = 0; i < width; i++)
    {
      buckets[i].resize(0);
    }
}

Hash_t::Hash_t(unsigned int buckets)
{
  width = buckets;
  hashSize = 0;
  int(*b_h)(void*, size_t) = basic_hash;
  funcPtr = b_h;
  this->buckets.resize(width);
  for(size_t i = 0; i < width; i++)
    {
      this->buckets[i].resize(0,0);
    }
}

Hash_t::Hash_t(unsigned int buckets, int(*hashfunc)(void*, size_t))
{
  width = buckets;
  hashSize = 0;
  funcPtr = hashfunc;
  this->buckets.resize(width);
  for(size_t i = 0; i < width; i++)
    {
      this->buckets[i].resize(0,0);
    }
}

Hash_t::~Hash_t()
{

}

Hash_t* Hash_t::Copy(Hash_t* hash)
{
  Hash_t* newHash = new Hash_t(hash->width, hash->funcPtr);
  return newHash;
}

/*Inserts an unsigned int element into the
  hash. True if inserted. No duplicates are allowed. Insert the data
  at the end of the bucket (since you have to search the bucket for a
  possible duplicate rst).*/
bool Hash_t::insert(unsigned int int2Add)
{
  //checks for no duplicates
  if(find(int2Add))
    {
      return false;
    }

  //gets which bucket to place data in
  size_t idx = getIndex(&int2Add, sizeof(unsigned int));
  
  //if no duplicates, insert at the last sport
  buckets[idx].push_back(int2Add);
  incSize();
  return true;
}

/*Inserts an unsigned int element into the
   hash. True if inserted. No duplicates are allowed. Insert the data
   at the end of the bucket (since you have to search the bucket for a
   possible duplicate rst).*/
bool Hash_t::insert(char char2Add)
{
  if(find(char2Add))
    {
      return false;
    }

    size_t idx = getIndex(&char2Add, sizeof(char));
    if(buckets[idx].size() == 0)
      {
	buckets[idx].resize(1);
      }
    //fucntion to get status bits and for the first available spot in
    //int--->check in this function if bucket index is full then make
    //a new one
    unsigned int placement;
    size_t i;
    //iterate through all ints in vector (each int being 4 slots for chars)
    for(i = 0; i <= buckets[idx].size(); i++)
      {
	//returns where in the current int to place the char 
	placement = charPlacement(buckets[idx][i]);
	//if there is no room for char and you reached the end of
	//vector, resize
	
	//if we found a place for our char, break
	if(placement < 15)
	  {
	    break;
	  }
	//if there is no room in int for char but more vector to
	//explore,keep going	
      }
    //function to mask char into spot
    return placeChar(idx, i, placement, (unsigned int)char2Add);
}

//places desired char into empty space
bool Hash_t::placeChar(size_t whichBucket, size_t idx, unsigned int place, unsigned int char2Add)
{
  unsigned int mask; //mask to make sure placement is zeroed out
  if(((place << 31) >> 31) == 0 )
    {
      char2Add <<= 4;
      mask = 4294965263;
      buckets[whichBucket][idx] &= mask;
      buckets[whichBucket][idx] += char2Add;
      buckets[whichBucket][idx] += 1;
    }
  else if(((place << 30) >> 31) == 0)
    {
      char2Add <<= (7+4);
      mask = 4294707199;
      buckets[whichBucket][idx] &= mask;
      buckets[whichBucket][idx] += char2Add;
      buckets[whichBucket][idx] += 2;
    }
  else if(((place << 29) >> 31) == 0)
    {
      char2Add <<= (14+4);
      mask = 4261675007;
      buckets[whichBucket][idx] &= mask;
      buckets[whichBucket][idx] += char2Add;
      buckets[whichBucket][idx] += 4;
    }
  else
    {
      char2Add <<= (21+4);
      mask = 33554431;
      buckets[whichBucket][idx] &= mask;
      buckets[whichBucket][idx] += char2Add;
      buckets[whichBucket][idx] += 8;
      //if there is no room for char and you reached the end of
      //vector, resize
      buckets[whichBucket].resize(buckets[whichBucket].size()+1);
    }
  incSize();
  return true;
}

bool Hash_t::switchChars(unsigned int flagInt, unsigned int flagStatus, unsigned int status, int bucket, int end)
{
  unsigned int char4 = 4261412864;
  unsigned int char3 = 33292288;
  unsigned int char2 = 260096;
  unsigned int char1 = 2032;
  unsigned int maskAdder4 = 33554416;
  unsigned int maskAdder3 = 4261674992;
  unsigned int maskAdder2 = 4294707184;
  unsigned int maskAdder1 = 4294965248;
  if(flagStatus == 1)
    {
      buckets[bucket][flagInt] &= 4294965263;
      if(((status << 28) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char4) >> 21;
	  buckets[bucket][end] &= (maskAdder4 + (status & 7));
	}
      else if(((status << 29) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char3) >> 14;
	  buckets[bucket][end] &= (maskAdder3 + (status & 3));
	}
      else if(((status << 30) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char2) >> 7;
	  buckets[bucket][end] &= (maskAdder2 + (status & 1));
	}
      else if(((status << 31) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char1);
	  buckets[bucket][end] &= (maskAdder1 + (status & 0));
	}
      unsigned int checkForLastChar = charPlacement(buckets[bucket][end]);
      if(checkForLastChar == 0)
	{	  
	  buckets[bucket].resize(buckets[bucket].size()-1, 0);
	}
    }
  else if(flagStatus == 2)
    {
      buckets[bucket][flagInt] &= 4294707199;
      if(((status << 28) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char4) >> 14;
	  buckets[bucket][end] &= (maskAdder4 + (status & 7));
	}
      else if(((status << 29) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char3) >> 7;
	  buckets[bucket][end] &= (maskAdder3 + (status & 3));
	}
      else if(((status << 30) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char2);
	  buckets[bucket][end] &= (maskAdder2 + (status & 1));
	}
      else if(((status << 31) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char1) << 7;
	  buckets[bucket][end] &= (maskAdder1 + (status & 0));
	}
    }
  else if(flagStatus == 4)
    {
      buckets[bucket][flagInt] &= 4261675007;
      if(((status << 28) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char4) >> 7;
	  buckets[bucket][end] &= (maskAdder4 + (status & 7));
	}
      else if(((status << 29) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char3);
	  buckets[bucket][end] &= (maskAdder3 + (status & 3));
	}
      else if(((status << 30) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char2) << 7;
	  buckets[bucket][end] &= (maskAdder2 + (status & 1));
	}
      else if(((status << 31) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char1) << 14;
	  buckets[bucket][end] &= (maskAdder1 + (status & 0));
	}
    }
  else
    {
      buckets[bucket][flagInt] &= 33554431;
      if(((status << 28) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char4);
	  buckets[bucket][end] &= (maskAdder4 + (status & 7));
	}
      else if(((status << 29) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char3) << 7;
	  buckets[bucket][end] &= (maskAdder3 + (status & 3));
	}
      else if(((status << 30) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char2) << 14;
	  buckets[bucket][end] &= (maskAdder2 + (status & 1));
	}
      else if(((status << 31) >> 31) == 1)
	{
	  buckets[bucket][flagInt] += (buckets[bucket][end] & char1) << 21;
	  buckets[bucket][end] &= (maskAdder1 + (status & 0));
	}
    }
  decSize();
  return true;
}

/*Removes a char element from the hash. True if
  removed. Only remove the rst occurence.*/
bool Hash_t::remove(char char2Rem)
{
  if(!find(char2Rem))
    {
      return false;
    }
  unsigned int mask = 127;
  unsigned int status = 0;
  unsigned int flagStatus = 0;
  unsigned int flagInt = 0;
  unsigned int foundIn = 0;
  bool found = false;
  unsigned int charCheck = 0;
  for(int i = 0; i < (int)width; i++)
    {
      for(int j = 0; j < (int)buckets[i].size(); j++)
	{
	  status = charPlacement(buckets[i][j]);
	  charCheck = buckets[i][j];
	  if(((status << 31) >> 31) == 1 )
	    {
	      if((char)((charCheck >> 4)& mask) == char2Rem)
		{
		  foundIn = i;
		  flagStatus = 1;
		  flagInt = j;
		  found = true;
		}
	    }
	  if(((status << 30) >> 31) == 1)
	    {
	      if((char)((charCheck >> (7+4)) & mask) == char2Rem)
		{
		  foundIn = i;
		  flagStatus = 2;
		  flagInt = j;
		  found = true;
		}
	    }
	  if(((status << 29) >> 31) == 1)
	    {
	      if((char)((charCheck >> (14+4))& mask) == char2Rem)
		{
		  foundIn = i;
		  flagStatus = 4;
		  flagInt = j;
		  found = true;
		}
	    }
	  if(((status << 28) >> 31) == 1)
	    {
	      if((char)((charCheck >> (21+4))& mask) == char2Rem)
		{
		  foundIn = i;
		  flagStatus = 8;
		  flagInt = j;
		  found = true;
		}
	    }
	  if(j == ((int)buckets[i].size() - 1))
	    {
	      if(found)
		{
		  unsigned int lastIntWithChars = j;
		  if(buckets[i][j] == 0)
		    {
		      lastIntWithChars--;
		    }
		  //status get char placements in last int
		  if(status == 0) //chars have been taken out of end
				 //int and end int no longer contains
				 //chars
		    {
		      status = charPlacement(buckets[foundIn][lastIntWithChars]);
		    }
		  //check the last char in the int
		  //swap the last char in int with flagged char to
		  //remove
		  found = false;
		  return switchChars(flagInt, flagStatus, status, foundIn, lastIntWithChars);
		}
	    }
	}      
    }
  return false;
}

//returns status bits in order to place a char
unsigned int Hash_t::charPlacement(unsigned int it) const
{
  return ((it << 28) >> 28);    
}

/*Finds an unsigned int element in the
  hash. True if found.*/
bool Hash_t::find(unsigned int int2Find)
{
  for(size_t i = 0; i < this->width; i++)
    {
      for(size_t j = 0; j < buckets[i].size(); j++)
	{
	  if(buckets[i][j] == int2Find)
	    {
	      return true;
	    }
	}
    }
  return false;
}

/*Finds an char element in the
  hash. True if found.*/
bool Hash_t::find(char char2Find)
{
  for(size_t i = 0; i < this->width; i++)
    {
      for(size_t j = 0; j < buckets[i].size(); j++)
	{
	  unsigned int check = charPlacement(buckets[i][j]);
	  unsigned int charCheck = buckets[i][j];
	  unsigned int mask = 127;
	  if(((check << 31) >> 31) == 1 )
	    {
	      if((char)((charCheck >> 4)& mask) == char2Find)
		{
		  return true;
		}	      
	    }
	  if(((check << 30) >> 31) == 1)
	    {
	      if((char)((charCheck >> (7+4))& mask) == char2Find)
		{
		  return true;
		}
	    }
	  if(((check << 29) >> 31) == 1)
	    {
	      if((char)((charCheck >> (14+4))& mask) == char2Find)
		{
		  return true;
		}
	    }
	  if(((check << 28) >> 31) == 1)
	    {
	      if((char)((charCheck >> (21+4))& mask) == char2Find)
		{
		  return true;
		}
	    }
	}
    }
  return false;
}

/*Removes an unsigned int element from the hash. true if removed.
 Only remove first occurance*/
bool Hash_t::remove(unsigned int int2Rem)
{
  for(size_t i = 0; i < this->width; i++)
    {
      for(size_t j = 0; j < buckets[i].size(); j++)
	{
	  if(buckets[i][j] == int2Rem)
	    {
	      buckets[i].erase(buckets[i].begin()+j);
	      decSize();
	      return true;
	    }
	}
    }
  return false;
}

size_t Hash_t::getIndex(void *data, size_t dataSize) const
{
  return funcPtr(data, dataSize) % width;
}

size_t Hash_t::size() const
{
  return this->hashSize;
}

void Hash_t::decSize()
{
  this->hashSize--;
}
void Hash_t::incSize()
{
  this->hashSize++;
}
vector<vector<unsigned int> > Hash_t::getBuckets()
{
  return this->buckets;
}

/*Creates a string with all of the bucket data,
  see sample output. This assumes the hash holds unsigned ints*/
string Hash_t::toString() const
{
  std::stringstream retval;
  for(size_t i = 0; i < this->width; i++)
    {
      if(i < 10)
	{
	  retval << " " << i << ": ";
	}
      else
	{
	  retval << i << ": ";
	}
      if(buckets[i].size() == 0)
	{
	  retval << "(Empty)";
	}
      else
	{
	  for(size_t j = 0; j < buckets[i].size(); j++)
	    {
	      if(j ==  buckets[i].size())
		{
		  retval << buckets[i][j];
		}
	      else
		{
		  retval << buckets[i][j] << " "; 
		}
	    }
	}
      retval << endl;
    }
  return retval.str();
}

/*Creates a string with all of the bucket data,
  see sample output. This assumes the hash holds unsigned ints*/
string Hash_t::toString(unsigned int data) const
{
  return toString();
}

/*Creates a string with all of the bucket data,
  see sample output. This assumes the hash holds unsigned ints*/
string Hash_t::toString(char data) const
{
  std::stringstream retval;
  unsigned int charCheck;
  unsigned int check;
  unsigned int mask = 127;
  for(size_t i = 0; i < width; i++)
    {
      if(i < 10)
	{
	  retval << " " << i << ": ";
	}
      else
	{
	  retval << i << ": ";
	}/*
      if(buckets[i].size() == 0)
	{
	  retval << "(Empty)";
	  }*/
      for(size_t j = 0; j < buckets[i].size(); j++)
	{
	  if(buckets[i].size() == 0 && buckets[i][j] == 0 )
	    {
	      retval << "(Empty)";
	    }
	  else
	    {
	      charCheck = buckets[i][j];
	      check = charPlacement(charCheck);
	      if(((check << 31) >> 31) == 1 )
		{
		  charCheck >>= 4;
		  if(check > 1)
		    {
		      retval << (char)(charCheck & mask) << " ";      
		    }
		  else
		    {
		      retval << (char)(charCheck & mask);
		    }
		  charCheck = buckets[i][j];
		}      
	      if(((check << 30) >> 31) == 1)
		{
		  charCheck >>= (7+4);
		  if(check > 3)
		    {
		      retval << (char)(charCheck & mask) << " ";
		    }
		  else
		    {
		      retval << (char)(charCheck & mask);
		    }
		  charCheck = buckets[i][j];
		}
	      if(((check << 29) >> 31) == 1)
		{
		  charCheck >>= (14+4);
		  if(check > 7)
		    {
		      retval << (char)(charCheck & mask) << " ";
		    }
		  else
		    {
		      retval << (char)(charCheck & mask);
		    }
		  charCheck = buckets[i][j];
		}
	      if(((check << 28) >> 31) == 1)
		{
		  charCheck >>= (21+4);
		  if(buckets[i].size() > j)
		    {
		      retval << (char)(charCheck & mask) << " ";
		    }
		  else
		    {
		      retval << (char)(charCheck & mask);
		    }
		  charCheck = buckets[i][j];
		}
	    }
	}
      retval << endl;
    }
  return retval.str();
}

ostream& operator<<(ostream& out, const Hash_t *rhs)
{
  out << rhs->toString();
  return out;
}

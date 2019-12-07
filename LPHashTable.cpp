#include "LPHashTable.hpp"
#include <cmath>

using namespace std;

LPHashTable::LPHashTable(int tableSize, bool hashFunction)
{
  TABLE_SIZE = tableSize;
  functOne = hashFunction;
  elements = 0;
  loadFactor = 0.0;
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    LPHashtable[i] = -1;
  }
}

LPHashTable::~LPHashTable()
{
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    while(LPHashtable[i] != -1)
    {
      LPHashtable[i] = -1;
    }
  }
  delete LPHashtable;
  LPHashtable = NULL;
}

int LPHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}

int LPHashTable:: hashFunctTwo(int key)
{
  return floor(key/TABLE_SIZE);
}

void LPHashTable::printTable()
{
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    cout << i << " --> ";
    if (LPHashtable[i] != -1)
    {
      cout << LPHashtable[i] << " ";
    }
  }
}

void LPHashTable::insertKey(int key)
{
  int i;
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  else
  {
    i = hashFunctTwo(key);
  }
  int curr;
  if(LPHashtable[i] != -1)
  {
    LPHashtable[i] = key;
  }
  else
  {
    curr = i;
    while(LPHashtable[i] != -1)
    {
      if(i == TABLE_SIZE)
      {
        i = 0;
      }
      else
      {
        i++;
      }
      if(curr == i)
      {
        TABLE_SIZE++;
        LPHashtable[TABLE_SIZE-1] = key;
        return;
      }
    }
    LPHashtable[i] = key;
    elements++;
  }
}

int LPHashTable::searchKey(int key)
{
  int i;
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  else
  {
    i = hashFunctTwo(key);
  }
  int curr = i;
  while(LPHashtable[i] != key)
  {
    if(i == TABLE_SIZE-1)
    {
      i = 0;
    }
    else
    {
      i++;
    }
    if(i == curr)
    {
      return -1;
    }
  }
  return i;
}

void LPHashTable::deleteKey(int key)
{
  int i;
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  else
  {
    i = hashFunctTwo(key);
  }
  int curr;
  if(LPHashtable[i] == key)
  {
    LPHashtable[i] = -1;
  }
  else
  {
    curr = i;
    i = searchKey(key);
    if(i == -1)
    {
      return;
    }
    else
    {
      LPHashtable[i] = -1;
    }
  }
  elements--;
}

float LPHashTable::getLoadFactor()
{
  return (float)elements/(float)TABLE_SIZE;
}

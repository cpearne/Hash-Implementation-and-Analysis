#include "CHHashTable.hpp"
#include <iostream>
using namespace std;

CHHashTable::CHHashTable(int tableSize)
{
  TABLE_SIZE = tableSize;
  CHTable1 = new int [TABLE_SIZE];
  CHTable2 = new int [TABLE_SIZE];
  elements = 0;
  loadFactor = 0;
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    CHTable1[i] = -1;
    CHTable2[i] = -1;
  }
}

CHHashTable::~CHHashTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    while (CHTable1[i] != -1)
    {
      CHTable1[i] = -1;
    }
    while (CHTable2[i] != -1)
    {
      CHTable2[i] = -1;
    }
  }
  delete CHTable1;
  CHTable1 = NULL;
  delete CHTable2;
  CHTable2 = NULL;
}

int CHHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}

int CHHashTable:: hashFunctTwo(int key)
{
  return floor(key/TABLE_SIZE);
}

void CHHashTable::reHash()
{
  rehash++;
  int newSize = TABLE_SIZE + 1;
  int *temp1 = new int [newSize];
  int *temp2 = new int [newSize];

  for(int i = 0; i < newSize; i++)
  {
    temp1[i] = CHTable1[i];
    temp2[i] = CHTable2[i];
  }

  temp1[newSize] = -1;
  temp2[newSize] = -1;
  delete CHTable1;
  delete CHTable2;
  CHTable1 = temp1;
  CHTable2 = temp2;
  TABLE_SIZE = newSize;
}


void CHHashTable::insertKey(int key)
{
  int i = hashFunctOne(key);
  int j = hashFunctTwo(key);
  int curr;
  int newKey = key;
  int oldKey = key;
  if (CHTable1[i] == -1)
  {
    CHTable1[i] = newKey;
    elements ++;
    return;
  }
  temp = CHTable1[i];
  CHTable1[i] = newKey;
  if (CHTable2[j] == -1)
  {
    CHTable2[j] = temp;
    elements++;
    return;
  }
  else
  {
    newKey = CHTable2[j];
    CHTable2[j] = temp;
  }
  if (oldKey == newKey)
  {
    rehash();
  }
}

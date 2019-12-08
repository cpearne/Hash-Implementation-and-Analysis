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

void CHHashTable::printTable()
{
  cout << "Table One: " << endl;
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    cout << i << " --> ";
    if (CHTable1[i] != -1)
    {
      cout << CHTable1[i] << " ";
    }
    cout << endl;
  }
  cout << "Table Two:" << endl;
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    cout << i << " --> ";
    if (CHTable2[i] != -1)
    {
      cout << CHTable2[i] << " ";
    }
    cout << endl;
  }
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

int CHHashTable::getRehash()
{
  cout << "Number of times Rehashed: " << rehash << endl;
  return rehash;
}

void CHHashTable::insertKey(int key)
{
  if (searchKey(key) == 0)
  {
    int i = hashFunctOne(key);
    int j = hashFunctTwo(key);
    int curr;
    int temp;
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
      reHash();
    }
  }
}

int CHHashTable::searchKey(int key)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    if (CHTable1[i] == key)
    {
      table = 1;
      return i;
    }
    else if (CHTable2[i] == key)
    {
      table = 2;
      return i;
    }
    else
    {
      return 0;
    }
  }
  return 0;
}

void CHHashTable::deleteKey(int key)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    if (CHTable1[i] == key)
    {
      CHTable1[i] = -1;
    }
    if (CHTable2[i] == key)
    {
      CHTable2[i] = -1;
    }
  }
}

float CHHashTable::getLoadFactor()
{
  return (float)elements/(float)TABLE_SIZE;
}

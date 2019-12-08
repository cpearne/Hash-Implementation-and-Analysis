#include "CHHashTable.hpp"
#include <iostream>
using namespace std;

/*
 * Purpose: Constructor for Initialization of hash table
 * @param tableSize to set the TABLE_SIZE
 */
CHHashTable::CHHashTable(int tableSize)
{
  TABLE_SIZE = tableSize;
  CHTable1 = new int [TABLE_SIZE];
  CHTable2 = new int [TABLE_SIZE];
  elements = 0;
  loadFactor = 0;
  //for loop to set all values in both tables to -1 (empty)
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    CHTable1[i] = -1;
    CHTable2[i] = -1;
  }
}

/*
 * Purpose: Destructor for Cuckoo Hash Table
 */
CHHashTable::~CHHashTable()
{
  //for loop to empty all inexes
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
  //delete both tables
  delete CHTable1;
  CHTable1 = NULL;
  delete CHTable2;
  CHTable2 = NULL;
}

/*
 * Purpose: Function to obtain the index if the first hash Function is used
 * @param key of the node that is in the first hash table
 * @return key % TABLE_SIZE which is h(x)
 */
int CHHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}

/*
 * Purpose: Function to obtain the index if the second hash Function is used
 * @param key of the node that is in the second hash table
 * @return floor(key % TABLE_SIZE) which is h'(x)
 */
int CHHashTable:: hashFunctTwo(int key)
{
  return floor(key/TABLE_SIZE);
}

/*
 * Purpose: Function to print the Hash Table
 * Used strictly for testing purposes
 */
void CHHashTable::printTable()
{
  cout << "Table One: " << endl;
  //for loop to traverse h(x) table
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
  //for loop to traverse h'(x) table
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

/*
 * Purpose: Function to create two new tables with a larger TABLE_SIZE
 */
void CHHashTable::reHash()
{
  //counter to get number of times reHashed
  rehash++;
  //incremente TABLE_SIZE by 1 and create two new tables with new tableSize
  int newSize = TABLE_SIZE + 1;
  int *temp1 = new int [newSize];
  int *temp2 = new int [newSize];
  //set the indexes of the previous tables to the new ones
  for(int i = 0; i < newSize; i++)
  {
    temp1[i] = CHTable1[i];
    temp2[i] = CHTable2[i];
  }
  //delete the old tables and remake them with a now larger TABLE_SIZE
  temp1[newSize] = -1;
  temp2[newSize] = -1;
  delete CHTable1;
  delete CHTable2;
  CHTable1 = temp1;
  CHTable2 = temp2;
  TABLE_SIZE = newSize;
}

/*
 * Purpose: Function to obtain the number of times reHashed
 */
int CHHashTable::getRehash()
{
  cout << "Number of times Rehashed: " << rehash << endl;
  return rehash;
}

/*
 * Purpose: Add a new node to the Cuckoo Hash Table in the correct spot
 * @param key value of the new value to be inserted
 */
void CHHashTable::insertKey(int key)
{
  //proceed if key is not a duplicate
  if (searchKey(key) == 0)
  {
    //assign each index of both hashTables to a variable
    int i = hashFunctOne(key);
    int j = hashFunctTwo(key);
    int curr;
    int temp;
    int newKey = key;
    int oldKey = key;
    //if an index in the first hash table is open, fill it
    if (CHTable1[i] == -1)
    {
      CHTable1[i] = newKey;
      elements ++;
      return;
    }
    temp = CHTable1[i];
    CHTable1[i] = newKey;
    //if an index in the second hash table is open,
    //take the value at the first tables index and assign it
    //to the index in the second hash table
    if (CHTable2[j] == -1)
    {
      CHTable2[j] = temp;
      elements++;
      return;
    }
    //if there are no available spots, set the index at table 2
    //as the new key
    else
    {
      newKey = CHTable2[j];
      CHTable2[j] = temp;
    }
    //if the key is unchanged, a loop occurrs so perform rehash
    if (oldKey == newKey)
    {
      reHash();
    }
  }
}

/*
 * Purpose: Search both hash tables for the specified key and return the index
 * @param key value
 * @return index of found key, or NULL if not found
 */
int CHHashTable::searchKey(int key)
{
  //for loop to traverse each table
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    //if the key is found in table 1,
    //return the index at which it is found
    if (CHTable1[i] == key)
    {
      table = 1;
      return i;
    }
    //if key is found in table 2
    else if (CHTable2[i] == key)
    {
      table = 2;
      return i;
    }
    //otherwise return 0 as key was not found
    else
    {
      return 0;
    }
  }
  return 0;
}

/*
 * Purpose: delete the value with the specified key in the hash table.
 * @param Key value of the node within the hash table
 */
void CHHashTable::deleteKey(int key)
{
  //for loop to traverse each hash table
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    //if found in table 1, set that value to -1
    if (CHTable1[i] == key)
    {
      CHTable1[i] = -1;
    }
    //if found in table 2, set that value to -1
    if (CHTable2[i] == key)
    {
      CHTable2[i] = -1;
    }
  }
  //decrease number of elements for load factor as value is deleted;
  elements --;
}

/*
 * Purpose: Function to obtain the Load Factor
 * @return Load Factor as a float
 */
float CHHashTable::getLoadFactor()
{
  return (float)elements/(float)TABLE_SIZE;
}

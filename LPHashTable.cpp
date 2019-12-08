#include "LPHashTable.hpp"
#include <cmath>

using namespace std;

/*
 * Purpose: Constructor for Linear Probing Hash Table
 * @param tableSize and which hash function to initialize hash table
 */
LPHashTable::LPHashTable(int tableSize, bool hashFunction)
{
  TABLE_SIZE = tableSize;
  functOne = hashFunction;
  elements = 0;
  loadFactor = 0.0;
  LPHashtable = new int [TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    LPHashtable[i] = -1;
  }
}
/*
*  Purpose: Destructor for Linear Probing Hash Table
*/
LPHashTable::~LPHashTable()
{
  // For loop to traverse hash table and set each key to -1
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

/*
 * Purpose: Function to obtain the index if the first hash Function is used
 * @param key of the node that is in the first hash table
 * @return key % TABLE_SIZE which is h(x)
 */
int LPHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}
/*
 * Purpose: Function to obtain the index if the second hash Function is used
 * @param key of the node that is in the second hash table
 * @return floor(key % TABLE_SIZE) which is h'(x)
 */
int LPHashTable:: hashFunctTwo(int key)
{
  return floor(key/TABLE_SIZE);
}

/*
 * Purpose: Function to print the Hash Table
 * Used strictly for testing purposes
 */
void LPHashTable::printTable()
{
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    cout << i << " --> ";
    if (LPHashtable[i] != -1)
    {
      cout << LPHashtable[i] << " ";
    }
      cout << endl;
  }
}
/*
*  Purpose: Add a new key value to the hash table
*  @param int key value
*/
void LPHashTable::insertKey(int key)
{
  // Condition to make sure no duplicates are found
  if (searchKey(key) == -1)
  {
    int i;
    // h(x)
    if(functOne)
    {
      i = hashFunctOne(key);
    }
    // h'(x)
    else
    {
      i = hashFunctTwo(key);
    }
    int curr;
    // If hash table index is empty
    if(LPHashtable[i] == -1)
    {
      LPHashtable[i] = key;
    }
    else
    {
      curr = i;
      while(LPHashtable[i] != -1)
      {
        // Lets the loop cycle through if necessary
        if(i == TABLE_SIZE)
        {
          i = 0;
        }
        // Traversal of array
        else
        {
          i++;
        }
        // if we reach our starting point, a cycle is present and we resolve by increasing hash table size
        if(i == curr)
        {
          TABLE_SIZE++;
          LPHashtable[TABLE_SIZE-1] = key;
          return;
        }
      }
      // Fill the hash table with new key if empty space is found/created
      LPHashtable[i] = key;
    }
    // Increase count of elements inserted
    elements++;
  }
}
/*
 * Purpose: Search the hash table for the specified key and return the index found
 * @param int key value
 * @return index of key or -1 if
 */
int LPHashTable::searchKey(int key)
{
  int i;
  // h(x)
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  // h'(x)
  else
  {
    i = hashFunctTwo(key);
  }
  int curr = i;
  while(LPHashtable[i] != key)
  {
    // Allows the loop to cycle through
    if(i == TABLE_SIZE-1)
    {
      i = 0;
    }
    // Traverse through hash table
    else
    {
      i++;
    }
    // Detects if cycle is present and returns that nothing was found
    if(curr == i)
    {
      return -1;
    }
  }
  return i;
}
/*
 * Purpose: Function to delete the given key if present within the hash table
 * @param int key value
 */
void LPHashTable::deleteKey(int key)
{
  int i;
  // h(x)
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  // h'(x)
  else
  {
    i = hashFunctTwo(key);
  }
  int curr;
  // If key is found
  if(LPHashtable[i] == key)
  {
    LPHashtable[i] = -1;
  }
  else
  {
    curr = i;
    // Search table for key since it was displaced by collision resolution methods
    i = searchKey(key);
    // Doesn't exist or already deleted
    if(i == -1)
    {
      return;
    }
    // Otherwise set to -1 for delete
    else
    {
      LPHashtable[i] = -1;
    }
  }
  // Remove one from our count of elements inserted
  elements--;
}

/*
 * Purpose: Function to obtain the Load Factor
 * @return Load Factor as a float
 */
float LPHashTable::getLoadFactor()
{
  return (float)elements/(float)TABLE_SIZE;
}

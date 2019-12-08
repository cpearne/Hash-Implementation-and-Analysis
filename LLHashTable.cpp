#include "LLHashTable.hpp"
#include <iostream>
#include <cmath>
using namespace std;

/*
 * Purpose: Constructor for LL
 * @param tableSize and which hash function to use
 */
LLHashTable::LLHashTable(int tableSize, bool hashFunction)
{
  TABLE_SIZE = tableSize;
  functOne = hashFunction;
  keyCount = 0;
  loadFactor = 0.0;
  LLHashtable = new node* [TABLE_SIZE];
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    LLHashtable[i] = nullptr;
  }
}

/*
 * Purpose: Destructor for LL
 */
LLHashTable::~LLHashTable()
{
  //for loop to traverse LL and delete each node
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    while (LLHashtable[i] != NULL)
    {
      deleteNode(LLHashtable[i]->key);
    }
  }
  delete LLHashtable;
  LLHashtable = NULL;
}

/*
 * Purpose: Function that creates a node upon insertion
 * @param key of node to be created
 * @return newNode to be used upon insertion
 */
node* LLHashTable::createNode(int key)
{
  node* newNode = new node;
  newNode->key = key;
  newNode->next = NULL;
  return newNode;
}

/*
 * Purpose: Function to obtain the index if the first hash Fucntion is used
 * @param key of the node that is in the first hash table
 * @return key % TABLE_SIZE which is h(x)
 */
int LLHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}

/*
 * Purpose: Function to obtain the index if the second hash Fucntion is used
 * @param key of the node that is in the first hash table
 * @return floor(key % TABLE_SIZE) which is h'(x)
 */
int LLHashTable::hashFunctTwo(int key)
{
  return floor(key / TABLE_SIZE);
}

/*
 * Purpose: Function to print the Hash Table
 * Used strictly for testing purposes
 */
void LLHashTable::printHashTable()
{
  //for loop to traverse the hash table
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    node* curr = LLHashtable[i];
    cout << i << " --> ";
    while(curr)
    {
      cout << curr->key << " ";
      curr = curr->next;
    }
  }
}

/*
 * Purpose: Search the LL for the specified key and return a pointer to that node
 * @param key value of node in LL
 * @return pointer to node of key, or NULL if not found
 */
node* LLHashTable::searchTable(int key)
{
  int i;
  //determine which hash function to use
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  else
  {
    i = hashFunctTwo(key);
  }
  node* curr = LLHashtable[i];
  //Traverse the LL until the node with the given key is found
  //and then return it
  while(curr)
  {
    if (curr->key == key)
    {
      return curr;
    }
    else
    {
      curr = curr->next;
    }
  }
  return NULL;
}

/*
 * Purpose: Add a new node to the LL in the correct spot
 * @param key value of the new node to be inserted
 */
void LLHashTable::insertNode(int key)
{
  //only insert if key is not a duplicate
  if(searchTable(key) == NULL)
  {
    int i;
    //determine which hash function to use
    if (functOne)
    {
      i = hashFunctOne(key);
    }
    else
    {
      i = hashFunctTwo(key);
    }
    //create a new node
    node* newNode = createNode(key);
    //if LL index is empty, place new node at that index
    if (LLHashtable[i] == NULL)
    {
      LLHashtable[i] = newNode;
    }
    //otherwise, traverse the LL until an empty index is found
    else
    {
      node* curr = LLHashtable[i];
      while (curr->next != NULL)
      {
        curr = curr->next;
      }
      curr->next = newNode;
    }
    //increase keyCount for load factor
    keyCount++;
    return;
  }
}

/*
 * Purpose: delete the node in the LL with the specified key.
 * @param Key value of the node within the LL
 */
void LLHashTable::deleteNode(int key)
{
  //check to see that the given key exists in the LL
  if (searchTable(key))
  {
    int i;
    //determine which hash function to use
    if (functOne)
    {
      i = hashFunctOne(key);
    }
    else
    {
      i = hashFunctTwo(key);
    }
    //set current node to first index
    //set previous node to NULL
    node* curr = LLHashtable[i];
    node* prev = NULL;
    //if current node's key is given key
    if (curr->key == key)
    {
      if (curr->next)
      {
        //set the index to the next value in the LL
        //delete current node
        LLHashtable[i] = curr->next;
        delete curr;
        curr = nullptr;
      }
      //if LL node is at the end;
      else
      {
        delete LLHashtable[i];
        LLHashtable[i] = nullptr;
      }
    }
    //traverse LL until key is found, then delete it
    else
    {
      while (curr->key != key)
      {
        prev = curr;
        curr = curr->next;
      }
      if (curr->next)
      {
        node* temp = curr;
        prev->next = curr->next;
        delete temp;
        temp = NULL;
      }
      else
      {
        delete curr;
        curr = NULL;
        prev->next = NULL;
      }
    }
  }
  //decrease keyCount for load factor as a node is deleted
  keyCount --;
}

/*
 * Purpose: Function to obtain the Load Factor
 * @return Load Factor as a float
 */
float LLHashTable::LoadFactor()
{
  float loadFactor;
  loadFactor = (float)keyCount / (float)TABLE_SIZE;
  return loadFactor;
}

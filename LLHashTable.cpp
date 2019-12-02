#include "LLHashTable.hpp"
#include <iostream>
#include <cmath>
using namespace std;

LLHashTable::LLHashTable(int tableSize, bool hashFunction)
{
  TABLE_SIZE = tableSize;
  functOne = hashFunction;
  LLHashTable = new node* [TABLE_SIZE];
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    LLHashTable[i] = NULL;
  }
}

LLHashTable::~LLHashTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    while (LLHashTable[i] != NULL)
    {
      deleteNode(LLHashTable[i]->key);
    }
  }
  delete LLHashTable;
  LLHashTable = NULL;
}

node* LLHashTable::createNode(int key)
{
  node* newNode = new node;
  newNode->key = key;
  return newNode;
}

int LLHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}

int LLHashTable::hashFunctTwo(int key)
{
  return floor(key / TABLE_SIZE);
}

void LLHashTable::printHashTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    node* curr = LLHashTable[i];
    cout << i << " --> ";
    while(curr)
    {
      cout << curr->key << " ";
      curr = curr->next;
    }
    cout << endl;
  }
}

/*
 * Purpose: Search the LL for the specified key and return a pointer to that node
 * @param key key value of node in LL
 * @return pointer to node of key, or NULL if not found
 */
node* LLHashTable::searchTable(int key)
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
  node* curr = LLHashTable[i];
  for (int i = 0; i < TABLE_SIZE; i++)
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
 * @param previous nod
 * @param key value of the new node to be inserted
 * @return none
 */
void LLHashTable::insertNode(node* previous, int key)
{
  if(searchTable(key) == NULL)
  {
    int i;
    if (functOne)
    {
      i = hashFunctOne(key);
    }
    else
    {
      i = hashFunctTwo(key);
    }
    node* newNode = createNode(key);
    if (LLHashTable[i] == NULL)
    {
      LLHashTable[i] = newNode;
    }
    else
    {
      node* curr = LLHashTable[i];
      while (curr->next != NULL)
      {
        curr = curr->next;
      }
      curr->next = newNode;
    }
  }
}

/*
 * Purpose: delete the node in the LL with the specified key.
 * @param Key value of the node within the LL
 * @return none
 */
void LLHashTable::deleteNode(int key)
{
  if (searchTable(key))
  {
    int i;
    if (functOne)
    {
      i = hashFunctOne(key);
    }
    else
    {
      i = hashFunctTwo(key);
    }
    node* curr = LLHashTable[i];
    node* prev = NULL;
    if (curr->key == key)
    {
      if (curr->next != NULL)
      {
        LLHashTable[i] = curr->next;
        delete curr;
        curr = NULL;
      }
      else
      {
        delete LLHashTable[i];
        LLHashTable[i] = NULL;
      }
    }
    else
    {
      while (curr->key != key)
      {
        prev = curr;
        curr = curr->next;
      }
      if (curr->next != NULL)
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
        prev-next = NULL;
      }
    }
  }
}

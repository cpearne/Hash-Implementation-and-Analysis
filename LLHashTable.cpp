#include "LLHashTable.hpp"
#include <iostream>
#include <cmath>
using namespace std;

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

LLHashTable::~LLHashTable()
{
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
  node* curr = LLHashtable[i];
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
 * @param previous nod
 * @param key value of the new node to be inserted
 * @return none
 */
void LLHashTable::insertNode(int key)
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
    if (LLHashtable[i] == NULL)
    {
      LLHashtable[i] = newNode;
    }
    else
    {
      node* curr = LLHashtable[i];
      while (curr->next != NULL)
      {
        curr = curr->next;
      }
      curr->next = newNode;
    }
  }
  keyCount++;
  return;
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
    node* curr = LLHashtable[i];
    node* prev = NULL;
    if (curr->key == key)
    {
      if (curr->next)
      {
        LLHashtable[i] = curr->next;
        delete curr;
        curr = nullptr;
      }
      else
      {
        delete LLHashtable[i];
        LLHashtable[i] = nullptr;
      }
    }
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
  keyCount --;
}

float LLHashTable::LoadFactor()
{
  float loadFactor;
  loadFactor = (float)keyCount / (float)TABLE_SIZE;
  return loadFactor;
}

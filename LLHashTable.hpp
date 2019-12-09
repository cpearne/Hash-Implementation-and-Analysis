#include <iostream>
#include <cmath>
using namespace std;

#ifndef LLHASHTABLE_H
#define LLHASHTABLE_H

struct node
{
  int key;
  node* next;
};

class LLHashTable{
  private:
    int TABLE_SIZE;
    node* *LLHashtable;
    node* createNode(int key);
    bool functOne;
    int keyCount;
    float loadFactor;

  public:
    LLHashTable(int tableSize, bool hashFunction);
    ~LLHashTable();
    int hashFunctOne(int key);
    int hashFunctTwo(int key);
    void printHashTable();
    node* searchNode(int key);
    void insertNode(int key);
    void deleteNode(int key);
    float getLoadFactor();
};

#endif

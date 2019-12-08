#ifndef CH_HashTable
#define CH_HashTable

#include <iostream>

using namespace std;

class CHHashTable
{
  private:
    int TABLE_SIZE;
    int *CHTable1;
    int *CHTable2;
    int table;
    int elements;
    float loadFactor;
    int rehash;

  public:
    CHHashTable(int tableSize);
    ~CHHashTable();
    int hashFunctOne(int key);
    int hashFunctTwo(int key);
    void printTable();
    void insertKey(int key);
    int searchKey(int key);
    void deleteKey(int key);
    float getLoadFactor();
    void reHash();
    int getRehash();
};

#endif

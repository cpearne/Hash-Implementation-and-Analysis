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
    bool functOne;
    int elements;
    float loadFactor;

  public:
    CHHashTable(int tableSize, bool hashFunction);
    ~CHHashTable();
    int hashFunctOne();
    int hashFunctTwo();
    void printTable();
    void insertKey(int key);
    int searchKey(int key);
    void deleteKey(int key);
    float getLoadFactor();
}

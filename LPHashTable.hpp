
#ifndef LPHASHTABLE_H
#define LPHASHTABLE_H

#include <iostream>

using namespace std;


class LPHashTable{
  private:
      int TABLE_SIZE;
      int *LPHashTable;
      bool functnOne;
      int elements;
      float loadFactor;
  public:
      LPHashTable(int tableSize, bool hashFunction);
      ~LPHashTable();
      int hashFunctOne(int key);
      int hashFunctTwo(int key);
      void printTable();
      void insertKey(int key);
      int searchKey(int key);
      void deleteKey(int key);
      float getLoadFactor();
};

#endif

#include <iostream>
using namespace std;

class BSTHashTable{
  private:
    int TABLE_SIZE;
    BST BSTHash;

  public:
    BSTHashTable();
    ~BSTHashTable();
    int hashFunctOne(int key);
    int hashFunctTwo(int key);
    void printHashTable();
    node *searchTable();
};

#include <iostream>
using namespace std;

struct TreeNode{
  int key;
  TreeNode *left, *right, *parent;
};

class BSTHashTable{
  private:
    int TABLE_SIZE;
    TreeNode* root;
    bool functone;

  public:
    BSTHashTable(int tableSize, bool hashFunction);
    ~BSTHashTable();
    int hashFunctOne(int key);
    int hashFunctTwo(int key);
    void printHashTable();
    TreeNode* search(int key);
    void insert(int key);
    void delete(int key);
};

#include <iostream>
using namespace std;

struct BSTNode{
  int key;
  BSTNode *left, *right, *parent;
};

class BST {
  private:
    BSTNode* root;

  public:
    BST();
    void insert(key);
    void printBST();
    void balanceTree();
};

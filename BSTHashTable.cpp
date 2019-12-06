#include "BSTHashTable.hpp"
#include <iostream>

using namespace std;

BSTHashTable::BSTHashTable(int tableSize, bool hashFunction);
{
  TABLE_SIZE = tableSize;
  functone = hashFunction;
  BSTHashTable = new TreeNode* [tableSize];
  for(int i = 0; i < tableSize; i++)
  {
    BSTHashTable[i] = NULL;
  }
}

BSTHashTable::~BSTHashTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    while (BSTHashTable[i] != NULL)
    {
      deleteNode(BSTHashTable[i]->key);
    }
  }
  delete BSTHashTable;
  BSTHashTable = NULL;
}

int BSTHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}

int BSTHashTable::hashFunctTwo(int key)
{
  return floor(key / TABLE_SIZE);
}

void inOrder(TreeNode* curr)
{
  if(curr == NULL)
  {
    return;
  }
  else
  {
    inOrder(curr->left);
    cout << curr->key << " ";
    inOrder(curr->right);
  }
}

void BSTHashTable::printHashTable()
{
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    node* curr = BSTHashTable[i];
    cout << i << " --> ";
    if(BSTHashTable[i] != NULL)
    {
      inOrder(curr);
      cout << endl;
    }
  }
}

TreeNode* BSTHashTable::searchTable(int key)
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
  if(BSTHashTable[i] != NULL)
  {
    TreeNode* curr = BSTHashTable[i];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (curr->key == key)
      {
        return curr;
      }
      else
      {
        if(key > curr->key)
        {
          curr = curr->right;
        }
        else
        {
          curr = curr->left;
        }
      }
    }
  }
  return NULL;
}

TreeNode* childInsert(TreeNode* parent, int childKey)
{
  if(parent == NULL)
  {
    TreeNode* New = new TreeNode;
    New->key = key;
    New->left = NULL;
    New->right = NULL;
    return New;
  }
  if(key > parent->key)
  {
    TreeNode* rightChild = childInsert(parent->right, key);
    parent->right = rightChild;
    rightChild->parent = parent;
  }
  else
  {
    TreeNode* leftChild = childInsert(parent->left, key);
    parent->left = leftChild;
    leftChild->parent = parent;
  }
  return parent;
}

void BSTHashTable::insertNode(int key)
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
  TreeNode* New = new TreeNode;
  New->key = key;
  New->left = NULL;
  New->right = NULL;

  if(BSTHashTable[i] == NULL)
  {
    BSTHashTable[i] = New;
  }
  else
  {
    BSTHashTable[i] = childInsert(BSTHashTable[i], key);
  }
  elementsCount++;
}

TreeNode* minKey(TreeNode* node)
{
  TreeNode* curr = node;
  while(curr != NULL && curr->left != NULL)
  {
    curr = curr->left;
  }
  return curr;
}

TreeNode* deleteNodeHelper(TreeNode* curr, int key)
{
  if(curr == NULL)
  {
    return curr;
  }
  if(curr->key < key)
  {
    curr->right = deleteNodeHelper(curr->right, key);
  }
  else if(curr->key > key)
  {
    curr->left = deleteNodeHelper(curr->left, key);
  }
  else
  {
    if(curr->key == key)
    {
      // No Children
      if(curr->left == NULL && curr->right == NULL)
      {
        delete curr;
        curr = NULL;
        return NULL;
      }
      // Right Child
      else if(curr->left == NULL && curr->right != NULL)
      {
        TreeNode* node = curr->right;
        delete curr;
        curr = NULL;
        return node;
      }
      // Left Child
      else if(curr->right == NULL && curr->left != NULL)
      {
        TreeNode* node2 = curr->left;
        delete curr;
        curr = NULL;
        return node2;
      }
      //Two Children
      else
      {
        TreeNode* node3 = minKey(curr->right);
        curr->key = node3->key;
        curr->right = deleteNodeHelper(root->right, node3->key)
      }
    }
  }
  return curr;
}

void BSTHashTable::deleteNode(int key)
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
  TreeNode* found = searchTable(key);
  if(found == NULL)
  {
    cout << key << ": Not Found" << endl;
  }
  else
  {
      BSTHashTable[i] = deleteNodeHelper(BSTHashTable[i], key);
  }
  elementsCount--;
}

int elementsCounter(TreeNode* curr)
{
  if(curr == NULL)
  {
    return;
  }
  else
  {
    elementsCounter(curr->left);
    elementsCounter(curr->right);
    return 1;
  }
}

float BSTHashTable::traverseLoadFactor()
{
  int total = 0;
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    TreeNode* curr = BSTHashTable[i];
    if(curr != NULL)
    {
      total += elementsCounter(curr);
    }
  }
  int loadFactor = total/TABLE_SIZE;
  return loadFactor;
}

float BSTHashTable::varLoadFactor()
{
  return (float)elementsCount/float(TABLE_SIZE);
}

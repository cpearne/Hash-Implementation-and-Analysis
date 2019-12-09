#include "BSTHashTable.hpp"
#include <iostream>

using namespace std;

/*
*  Purpose: constructor for Initialization of hash table
*  @param tableSize to set the TABLE_SIZE
*         hashFunction to set the functOne variable (which hashkey to use)
*         allocate new hashtable and set it as NULL
*/
BSTHashTable::BSTHashTable(int tableSize, bool hashFunction)
{
  TABLE_SIZE = tableSize;
  functOne = hashFunction;
  BSTHashtable = new TreeNode* [TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    BSTHashtable[i] = NULL;
  }
}

/*
*  Purpose: Destructor of Binary Search Tree Hash Table
*  @function traverse hash table indices using delete function for all connected nodes in each index
*/
BSTHashTable::~BSTHashTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    while (BSTHashtable[i] != NULL)
    {
      deleteNode(BSTHashtable[i]->key);
    }
  }
  delete BSTHashtable;
  BSTHashtable = NULL;
}

/*
*  Purpose: Function to obtain appropriate hash table index given a key
*  @param key of the node to be inserted/searched when output index
*  @return key % TABLE_SIZE which is h(x) index
*/
int BSTHashTable::hashFunctOne(int key)
{
  return key % TABLE_SIZE;
}
/*
*  Purpose: Function to obtain appropriate hash table index given a key
*  @param key of the node to be inserted/searched when output index
*  @return key % TABLE_SIZE which is h'(x) index
*/
int BSTHashTable::hashFunctTwo(int key)
{
  return floor(key / TABLE_SIZE);
}

/*
*  Purpose: Helper function for printing hash table by traversing the BST of a given Hash Table node
*  @param TreeNode root node so that it can recursively traverse left and right children until NULL
*/
void inOrder(TreeNode* curr)
{
  if(curr == NULL)
  {
    return;
  }
  else
  {
    // recursively call all left children
    inOrder(curr->left);
    cout << curr->key << " ";
    // recursively call all right children
    inOrder(curr->right);
  }
}

/*
*  Purpose: Function to print the entire Hash Table by traversing every index, and
*           calling helper to traverse from root node to all child nodes
*  Used for debugging and given as a menu option
*/
void BSTHashTable::printTable()
{
  // for loop to traverse hash table indices
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    // temporary TreeNode for hash table index root node
    TreeNode* curr = BSTHashtable[i];
    // Prints given hash table index and points to all connected nodes
    cout << i << " --> ";
    if(BSTHashtable[i] != NULL)
    {
      // Calls Binary Search Tree Inorder Traversal to print all connected nodes
      inOrder(curr);
      cout << endl;
    }
  }
}
/*
*  Purpose: Function to traverse Hash Table for a node with a given key
*  @param key value to compare against nodes
*  Since Binary Tree is balanced we can search/traverse it like a Binary Search Tree
*  @return node within search function, otherwise return null at the end of the function
*/
TreeNode* BSTHashTable::searchNode(int key)
{
  int i;
  // h(x)
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  // h'(x)
  else
  {
    i = hashFunctTwo(key);
  }
  // As long as the index isn't empty
  if(BSTHashtable[i] != NULL)
  {
    // Temp TreeNode to establish root node
    TreeNode* curr = BSTHashtable[i];
    while (curr != NULL)
    {
      // if key is found within a node
      if (curr->key == key)
      {
        return curr;
      }
      // Otherwise traverse the left and right children until the node either is/isn't found
      else
      {
        // Right side traversal
        if(key > curr->key)
        {
          curr = curr->right;
        }
        // Left side traversal
        else
        {
          curr = curr->left;
        }
      }
    }
  }
  return NULL;
}

/*
*  Purpose: Helper function to insert new node to chain if index is already occupied
*  @param TreeNode* parent to compare its key against new node to insert to insert in appropriate
*         spot on the Binary Tree to ensure it is balanced
*  @return Newly created node
*/
TreeNode* childInsert(TreeNode* parent, int childKey)
{
  if(parent == NULL)
  {
    TreeNode* New = new TreeNode;
    New->key = childKey;
    New->left = NULL;
    New->right = NULL;
    return New;
  }
  if(childKey > parent->key)
  {
    TreeNode* rightChild = childInsert(parent->right, childKey);
    parent->right = rightChild;
    rightChild->parent = parent;
  }
  else
  {
    TreeNode* leftChild = childInsert(parent->left, childKey);
    parent->left = leftChild;
    leftChild->parent = parent;
  }
  return parent;
}

/*
*  Purpose: to insert a new key into our hash table by creating a node to store it
*  @param int key value
*/
void BSTHashTable::insertNode(int key)
{
  // search to make sure there are no duplicate key values in table
  if (searchNode(key) == NULL)
  {
    int i;
    // h(x)
    if(functOne)
    {
      i = hashFunctOne(key);
    }
    // h'(x)
    else
    {
      i = hashFunctTwo(key);
    }
    // Create a new TreeNode* that will be our new node to insert into hash table
    TreeNode* New = new TreeNode;
    New->key = key;
    New->left = NULL;
    New->right = NULL;

    // If hash table index does not contain a node
    if(BSTHashtable[i] == NULL)
    {
      BSTHashtable[i] = New;
    }
    // Otherwise call helper function that inserts node to keep BST balance
    else
    {
      BSTHashtable[i] = childInsert(BSTHashtable[i], key);
    }
    // Increase elements inserted for load factor
    elementsCount++;
  }
}

/*
*  Purpose: Helper function to find the node with the minimum key value to replace any deleted node
*           that might have children to maintain BST balance
*  @param TreeNode* to be deleted
*  @return node with minimum value connected to deleted node
*/
TreeNode* minKey(TreeNode* node)
{
  TreeNode* curr = node;
  while(curr != NULL && curr->left != NULL)
  {
    curr = curr->left;
  }
  return curr;
}
/*
*  Purpose: Helper function to find node containing the given key by recursively traversing the BST
*  @param a TreeNode that is the current node being compared to in the traversal
*  @param the int key value that is being traversed for deletion
*  @return TreeNode to either return the node if it was deleted or if it wasn't found
*/
TreeNode* deleteNodeHelper(TreeNode* curr, int key)
{
  // If the node was deleted before a recursive call
  if(curr == NULL)
  {
    return curr;
  }
  // Right child traversal
  if(curr->key < key)
  {
    curr->right = deleteNodeHelper(curr->right, key);
  }
  // Left child traversal
  else if(curr->key > key)
  {
    curr->left = deleteNodeHelper(curr->left, key);
  }
  else
  {
    // If we found node with the key
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
        // Find the inorder successor to the deleted node
        TreeNode* node3 = minKey(curr->right);
        curr->key = node3->key;
        curr->right = deleteNodeHelper(curr->right, node3->key);
      }
    }
  }
  return curr;
}

/*
*  Purpose: Function to delete a node that has a given key value
*  @param int key value to be deleted from hash table
*/
void BSTHashTable::deleteNode(int key)
{
  int i;
  // h(x)
  if(functOne)
  {
    i = hashFunctOne(key);
  }
  // h'(x)
  else
  {
    i = hashFunctTwo(key);
  }
  // Check to see if search function found the key
  TreeNode* found = searchNode(key);
  // If node isn't null then helper functions are called to properly delete node
  if (found != NULL)
  {
      BSTHashtable[i] = deleteNodeHelper(BSTHashtable[i], key);
  }
  // Substract number of elements in hash table
  elementsCount --;
}

/*
*  Purpose: Helper function for Binary Tree Traversal to count all elements in hash table
*  @param passed root node for function to traverse its children
*/
int elementsCounter(TreeNode* curr)
{
  if(curr == NULL)
  {
    return 0;
  }
  else
  {
    elementsCounter(curr->left);
    elementsCounter(curr->right);
    return 1;
  }
}

/*
*  Purpose: Function to traverse and count the number of elements in the hash table and get load factor
*  @return float load factor
*/
float BSTHashTable::traverseLoadFactor()
{
  int total = 0;
  // for loop traversal of hash table indices
  for(int i = 0; i < TABLE_SIZE; i++)
  {
    // Current TreeNode for hash table index root node
    TreeNode* curr = BSTHashtable[i];
    if(curr != NULL)
    {
      total += elementsCounter(curr);
    }
  }
  float loadFactor = total/TABLE_SIZE;
  cout << "Load Factor: " << loadFactor << endl;
  return loadFactor;
}
/*
*  Purpose: Function to obtain the load factor
*  @return float load factor
*/
float BSTHashTable::getLoadFactor()
{
  return (float)elementsCount/(float)TABLE_SIZE;
}

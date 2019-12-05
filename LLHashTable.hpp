#include <iostream>
using namespace std;

struct node
{
  int key;
  node* next;
};

class LLHashTable{
  private:
    int TABLE_SIZE;
    node* head;
    bool functOne;
    float keyCount;

  public:
    LLHashTable(int tableSize, bool hashFunction);
    ~LLHashTable();
    node* createNode(int key);
    int hashFunctOne(int key);
    int hashFunctTwo(int key);
    void printHashTable();
    node* searchTable(int key);
    void insertNode(int key);
    void deleteNode(int key);
    float loadFactor();
};

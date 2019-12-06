#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "LLHashTable.cpp"
#include "BSTHashTable.cpp"
using namespace std;

void displayMenu()
{
  cout << "---- Choose Collision Method ----" << endl;
  cout << "1. Linked List" << endl;
  cout << "2. Binary Search Tree" << endl;
  cout << "3. Linear Probing" << endl;
  cout << "4. Cuckoo Hashing" << endl;
  cout << "---------------------" << endl;
}

void displayHashFunction()
{
  cout << "---- Choose Hash Function ----" << endl;
  cout << "1. Hash Function One: key % tableSize" << endl;
  cout << "2. Hash Function Two: floor(key/tableSize)" << endl;
  cout << "---------------------" << endl;
}

void displayData(bool hashFunction, int method, float insertData[], float searchData[], float deleteData[])
{
  cout << "---- Method and Actions ----" << endl;
  cout << "Collision Method Chosen:" << endl;
  if (method == 1)
  {
    cout << "Chaining With Linked List" << endl;
  }
  if (method == 2)
  {
    cout << "Chaining With Binary Search Tree" << endl;
  }
  if (method == 3)
  {
    cout << "Linear Probing" << endl;
  }
  if (method == 4)
  {
    cout << "Cuckoo Hashing" << endl;
  }
  else if (method < 1 || method > 4)
  {
    cout << "error" << endl;
  }
  cout << "Hash Function:" << endl;
  if (hashFunction)
  {
    cout << "key % TABLE_SIZE" << endl;
  }
  else
  {
    cout << "floor(key / TABLE_SIZE)" << endl;
  }
  cout << endl;
  cout << "---- Data Obtained ----" << endl;
  cout << "Insert Data: ";
  for (int i = 0; i < 6; i++)
  {
    cout << insertData[i];
    if (i != 5)
    {
      cout << ", ";
    }
  }
  cout << endl;
  cout << "Search Data: ";
  for (int i = 0; i < 6; i++)
  {
    cout << searchData[i];
    if (i != 5)
    {
      cout << ", ";
    }
  }
  cout << endl;
  cout << "Delete Data: ";
  for (int i = 0; i < 6; i++)
  {
    cout << deleteData[i];
    if (i != 5)
    {
      cout << ", ";
    }
  }
}
int main(int argc, char* argv[])
{
  int startTime, endTime;
  double execTime;
  double insertTime;
  double searchTime;
  double deleteTime;
  bool hashFunction;
  int size = 10009;
  float loadFactors[6] = {0.1, 0.2, 0.5, 0.7, 0.9, 1};
  float insertData[6];
  float searchData[6];
  float deleteData[6];
  string line;
  int count = 6;
  int values[40000];
  int i = 0;
  int number;
  //Load in file
  ifstream myFile;
  myFile.open("dataSetA.csv");
  while (getline(myFile, line, ','))
  {
    number = stoi(line);
    values[i] = number;
    i++;
  }
  //Get collision method
  displayMenu();
  int method;
  cin >> method;
  while (method > 4 || method < 1)
  {
    cout << "Invalid choice, please pick a number between 1 and 4" << endl;
    displayMenu();
    cin >> method;
  }
  //Hash Table Initialization
  if (method > 0 && method < 4)
  {
    displayHashFunction();
    int hashMethod;
    cin >> hashMethod;
    while (hashMethod > 2 || hashMethod < 1)
    {
      cout << "Invalid choice, please pick number 1 or 2" << endl;
      displayHashFunction();
      cin >> hashMethod;
    }
    if (hashMethod == 1)
    {
      hashFunction = true;
    }
    else if (hashMethod == 2)
    {
      hashFunction = false;
    }
  }
  //Linked List Chaining
  if (method == 1)
  {
    cout << "---- Linked List Chaining ----" << endl;
    LLHashTable hashTable(size, hashFunction);
    hashTable.printHashTable();
    int j = 0;
    int loadFactorNum = 0;
    int time;
    for (int k = 0; k < count; k++)
      {
        while(hashTable.LoadFactor() < loadFactors[loadFactorNum])
        {
          hashTable.insertNode(values[j]);
          j++;
        }
        j = 0;
        //Insert 100 values
        startTime = clock();
        for (int l = 0; l < 100; l++)
        {
          hashTable.insertNode(values[j]);
          j++;
        }
        endTime = clock();
        execTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        insertTime = execTime;
        insertData[time] = insertTime;
        j = 0;
        //search 100 values
        startTime = clock();
        for (int m = 0; m < 100; m++)
        {
          hashTable.searchTable(values[j]);
          j++;
        }
        endTime = clock();
        execTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        searchTime = execTime;
        searchData[time] = searchTime;
        j = 0;
        //delete 100 values
        startTime = clock();
        for (int n = 0; n < 100; n++)
        {
          hashTable.deleteNode(values[j]);
          j++;
        }
        endTime = clock();
        execTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        deleteTime = execTime;
        deleteData[time] = deleteTime;
        loadFactorNum++;
        time++;
        float avg = (insertTime + searchTime + deleteTime) / 3.0;
        cout << "Average time: " << avg << endl;
      }
      displayData(hashFunction, method, insertData, searchData, deleteData);
      return 0;
  }
  //BST Implementation
  if (method == 2)
  {
    cout << "---- Binary Search Tree Chaining ----" << endl;
    BSTHashTable b(size, hashFunction);
    int j = 0;
    int loadFactorNum = 0;
    int time;
    for (int k = 0; k < count; k++)
      {
        while(b.getLoadFactor() < loadFactors[loadFactorNum])
        {
          b.insertNode(values[j]);
          j++;
        }
        j = 0;
        //Insert 100 values
        startTime = clock();
        for (int l = 0; l < 100; l++)
        {
          b.insertNode(values[j]);
          j++;
        }
        endTime = clock();
        execTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        insertTime = execTime;
        insertData[time] = insertTime;
        j = 0;
        //search 100 values
        startTime = clock();
        for (int m = 0; m < 100; m++)
        {
          b.searchTable(values[j]);
          j++;
        }
        endTime = clock();
        execTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        searchTime = execTime;
        searchData[time] = searchTime;
        j = 0;
        //delete 100 values
        startTime = clock();
        for (int n = 0; n < 100; n++)
        {
          b.deleteNode(values[j]);
          j++;
        }
        endTime = clock();
        execTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        deleteTime = execTime;
        deleteData[time] = deleteTime;
        loadFactorNum++;
        time++;
        float avg = (insertTime + searchTime + deleteTime) / 3.0;
        cout << "Average time: " << avg << endl;
      }
      displayData(hashFunction, method, insertData, searchData, deleteData);
      return 0;
  }
}

#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int split (string str, char c, string arr[], int length)
{
    if (str.length() == 0)
    {
        return 0;
    }
        string word = "";
        int j = 0;
        str = str + c;
    for (int i = 0; i < str.length(); i++)
    {

    if (str[i] == c)
    {
    if (word.length() == 0) continue;

        arr[j] = word;
        j++;
        word = "";

    }
    else
    {
     word = word + str[i];
    }
    }
    return j;
}

void menu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Print the inventory" << endl;
  cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;
}

int main(int argc, char* argv[])
{
  MovieTree movies;
  int Rank;
  int Yr;
  string Title;
  float Rating;

  ifstream inFile;
  inFile.open(argv[1]);
  if(inFile.is_open())
  {
    string lines = "";
    string stor[4];
    while(getline(inFile, lines))
    {
      split(lines, ',', stor, 4);
      Rank = stoi(stor[0]);
      Title = stor[1];
      Yr = stoi(stor[2]);
      Rating = stof(stor[3]);
      movies.addMovie(Rank, Title, Yr, Rating);
    }
  }

  // movies.printMovieInventory();
  int option = 0;
  string in_title;
  bool test = true;
  while(test)
  {
    menu();
    cin >> option;
    switch(option)
    {
      case 1:
      {
        movies.printMovieInventory();
        break;
      }
      case 2:
      {
        cout << "Enter a movie title:" << endl;
        cin.ignore();
        getline(cin,in_title);
        movies.deleteMovie(in_title);
        break;
      }
      case 3:
      {
        cout << "Goodbye!" << endl;
        test = false;
        break;
      }
    }
  }
  return 0;
}

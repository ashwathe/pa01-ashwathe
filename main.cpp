#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

bool parseLine(string &line, string &cSuit, string &cValue);

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;
  string cSuit;
  string cValue;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  BST<Card>* player1;
  BST<Card>* player2;
  while (getline (cardFile1, line) && (parseLine(line, cSuit, cValue))){
     string suit = cSuit;
     string value = cValue;

    Card c(suit, value);
    player1->insert(c);
     //cout << suit << endl;
     //cout << value << endl;

  }
  cardFile1.close();


  while (getline (cardFile2, line) && (parseLine(line, cSuit, cValue))){
    string suit = cSuit;
    string value = cValue;

    //cout << suit << endl;
    //cout << value << endl;

    //player2.insert();
  }
  cardFile2.close();
  
  
  return 0;
}

bool parseLine(string &line, string &cSuit, string &cValue) {
  if(line.length() <= 0) return false;

  cSuit = line[0];
  cValue = line.substr(2, line.length() - 2);
/*
  if(cSuit == "c"){
      cSuit = "0";
  }
  else if(cSuit == "d"){
      cSuit = 1;
  }
  else if(cSuit == "s"){
      cSuit = 2;
  }
  else if(cSuit == "h"){
      cSuit = 3;
  }

  if (cValue == "a"){
      cValue = 0;
  }
  else if (cValue == "j"){
      cValue = 10;
  }
  else if (cValue == "q"){
      cValue = 11;
  }
  else if (cValue == "k"){
      cValue = 12;
  }
  else {
      cValue = stoi(cValue) - 1;
  }
*/
  return true;
}

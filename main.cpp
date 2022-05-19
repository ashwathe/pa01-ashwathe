#include <iostream>
#include <fstream>
#include <string>

#include "cards.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  BST<Card> a, b;
  
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){

    string suit = line.substr(0,1);
    string value = line.substr(2);

    Card *c = new Card(suit, value);
    a.insert(*c);
    delete c;

  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){

    string suit = line.substr(0,1);
    string value = line.substr(2);

    Card *c = new Card(suit, value);
    b.insert(*c);
    delete c;

  }
  cardFile2.close();

  Card a_current = a.getMin();
  Card b_current = b.getMax();

  while ( !(a_current == a.getMax()) && !(b_current == b.getMin()) ) {
    while( !b.contains(a_current) && !(a_current == a.getMax()) ) {
      a_current = a.getSuccessor(a_current);
    }
    if ( b.contains(a_current) ) {
      cout << "Alice picked matching card " << a_current;
      Card a_temp = a_current;
      if (!(a_current == a.getMax())) { 
        a_current = a.getSuccessor(a_current);
      }
      if (b_current == a_temp && !(b_current == b.getMin())) {
        b_current = b.getPredecessor(b_current);
      }
      a.remove(a_temp);
      b.remove(a_temp);
    }
    while( !a.contains(b_current) && !(b_current == b.getMin()) ) {
      b_current = b.getPredecessor(b_current);
    }
    if ( a.contains(b_current) ) {
      cout << "Bob picked matching card " << b_current;
      Card b_temp = b_current;
      if (!(b_current == b.getMin())) { 
        b_current = b.getPredecessor(b_current); 
      }
      if (a_current == b_temp && !(a_current == a.getMax())) {
        a_current = a.getSuccessor(a_current);
      }
      a.remove(b_temp);
      b.remove(b_temp);
    }
  }

  cout << endl << "Alice's cards: " << endl;
  a.printInOrder();
  cout << endl << "Bob's cards: " << endl;  
  b.printInOrder();
  
  return 0;
  
}

/*#include <iostream>
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

    Card *c = new Card(suit, value);
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

  //if(s == 'c'){
      cSuit = 0;
  }
  else if(s == 'd'){
      cSuit = 1;
  }
  else if(s == 's'){
      cSuit = 2;
  }
  else if(s == 'h'){
      cSuit = 3;
  }

  if (v == "a"){
      cValue = 0;
  }
  else if (v == "j"){
      cValue = 10;
  }
  else if (v == "q"){
      cValue = 11;
  }
  else if (v == "k"){
      cValue = 12;
  }
  else {
      cValue = stoi(v) - 1;
  }

  return true;
}*/
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

  // Read each file
  BST<Card> a;
  BST<Card> b;

  while (getline (cardFile1, line) && parseLine(line, cSuit, cValue)){
    string suit = cSuit;
    string value = cValue;

    Card c(suit, value);
    a.insert(c);

  }
  cardFile1.close();


  while (getline (cardFile2, line) && parseLine(line, cSuit, cValue)){   
    string suit = cSuit;
    string value = cValue;

    Card c(suit, value);
    b.insert(c);

  }
  cardFile1.close();
  
  // code for the game
  Card a_curr = a.getMin();
  Card b_curr = b.getMax();

  while ( !(a_curr == a.getMax()) && !(b_curr == b.getMin()) ) {
    
    // a's turn to pick cards:
    while( !b.contains(a_curr) && !(a_curr == a.getMax()) ) {
      a_curr = a.getSuccessor(a_curr);
    }

    // check if card matches with b: 
    if ( b.contains(a_curr) ) {
      cout << "Alice picked matching card " << a_curr;
      Card a_temp = a_curr;
      if (!(a_curr == a.getMax())) { 
        a_curr = a.getSuccessor(a_curr);
      }
      if (b_curr == a_temp && !(b_curr == b.getMin())) {
        b_curr = b.getPredecessor(b_curr);
      }
      a.remove(a_temp);
      b.remove(a_temp);
    }

    // b's turn to pick cards
    while( !a.contains(b_curr) && !(b_curr == b.getMin()) ) {
      b_curr = b.getPredecessor(b_curr);
    }

    // chekc if card matches with a:
    if ( a.contains(b_curr) ) {
      cout << "Bob picked matching card " << b_curr;
      Card b_temp = b_curr;
      if (!(b_curr == b.getMin())) { 
        b_curr = b.getPredecessor(b_curr); 
      }
      if (a_curr == b_temp && !(a_curr == a.getMax())) {
        a_curr = a.getSuccessor(a_curr);
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

bool parseLine(string &line, string &cSuit, string &cValue) {
  if(line.length() <= 0) return false;

  cSuit = line.substr(0,1);
  cValue = line.substr(2);

  return true;
}

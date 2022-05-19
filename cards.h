// cards.h
// Author: Ashwath Ekambaram
// All class declarations go here

#ifndef CARDS_H
#define CARDS_H

#include <iostream>

using namespace std;

template <class Tree>
class BST {
    public:
        BST();
        ~BST();
        bool insert(Tree value);
        void printPreOrder() const;
        void printInOrder() const;
        void printPostOrder() const;
        int count() const;        
        bool contains(Tree value) const;
        Tree getPredecessor(Tree value) const;
        Tree getSuccessor(Tree value) const;
        Tree getMax() const;
        Tree getMin() const;
        bool remove(Tree value);

    private:

        struct Node {
            Tree info;
            Node *left, *right, * parent;
        Node (Tree v = nullptr) : info(v), left(nullptr), right(nullptr), parent(nullptr) {}
        };
        
        Node *root;
        
        Node* getNodeFor(Tree value, Node* n) const;
        void clear(Node* n);
        bool insert(Tree value, Node* n);
        void printPreOrder(Node* n) const;
        void printInOrder(Node* n) const;
        void printPostOrder(Node* n) const;
        int count(Node* n) const;


        Node* getSuccessorNode(Tree value) const;
        Node* getPredecessorNode(Tree value) const;
        Node* getMaxNode() const;
        Node* getMinNode() const;


};

class Card {
    public:
        Card(string s, string v);
        Card(const Card& source);
        ~Card();
        Card* operator=(const Card& source);

        bool operator>(const Card& source) const;
        bool operator<(const Card& source) const;
        bool operator==(const Card& source) const;
        friend ostream& operator<<(ostream& stream, const Card& source);

        string getValue() const;
        int getValueInt() const;
        string getSuit() const;
        int getSuitInt() const;

    private:
        int suit;
        int value;

};

#include "cards.cpp"

#endif
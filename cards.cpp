// cards.cpp
// Author: Ashwath Ekambaram
// Implementation of the classes defined in cards.h

#include <iostream>
#include <string>
#include "cards.h"

using namespace std;


//constructor constructs empty tree
template <class Tree>
BST<Tree>::BST() : root(nullptr) {
}

//destructor
template <class Tree>
BST<Tree>::~BST(){
    clear(root);
}

//destructive helper
template <class Tree>
void BST<Tree>::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

template <class Tree>
bool BST<Tree>::insert(Tree value) {
    if(!root){
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

template <class Tree>
bool BST<Tree>::insert(Tree value, Node *n) {
    if(value == n->info){
        return false;
    }
    if (value < n->info) {
        if(n->left){
            return insert(value, n->left);
        }
        else {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if(n->right){
            return insert(value, n->right);
        }
        else{
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
    }
}


template <class Tree>
void BST<Tree>::printPreOrder() const {
    printPreOrder(root);
}

template <class Tree>
void BST<Tree>::printPreOrder(Node *n) const{
    if (n) {
        cout << n->info;
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

template <class Tree>
void BST<Tree>::printInOrder() const {
    printInOrder(root);
}

template <class Tree>
void BST<Tree>::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->info;
        printInOrder(n->right);
    }
}

template <class Tree>
void BST<Tree>::printPostOrder() const {
        printPostOrder(root);
}

template <class Tree>
void BST<Tree>::printPostOrder(Node *n) const {
    if(n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info;
    }
}

template <class Tree>
int BST<Tree>::count() const{
    return count(root);
}

template <class Tree>
int BST<Tree>::count(Node *n) const {
    if(!n){
        return 0;
    }
    return (1 + count(n->left) + count(n->right));
}

template<class Tree>
typename BST<Tree>::Node* BST<Tree>::getNodeFor(Tree value, Node* n) const {
    if(!n) return nullptr;
        if(n->info == value){
            return n;
        }
        else{
            if(value < n->info) {
                return getNodeFor(value, n->left);
            }
            else{
                return getNodeFor(value, n->right);
            }
        }
    }


template<class Tree>
bool BST<Tree>::contains(Tree value) const {
    if(getNodeFor(value, root) != nullptr) {
        return true;
        }
    else{
        return false;
    }
}

template<class Tree>
typename BST<Tree>::Node* BST<Tree>::getPredecessorNode(Tree value) const{
    Node* n = getNodeFor(value, root);
    if(!n){
        return 0;
    }
    if(n->left){
        n = n->left;
        while(n->right){
            n = n->right;
        }
        return n;
    }
    else{
        while(n->parent) {
            n = n->parent;
            if(n->info < value){
                return n;
            }
        }
        return 0;
    }
}

template<class Tree>
Tree BST<Tree>::getPredecessor(Tree value) const {
    Node *n = getPredecessorNode(value);
    if(!n){
        cout<< "you lost";
    }
    return n->info;
}

template<class Tree>
typename BST<Tree>::Node* BST<Tree>::getSuccessorNode(Tree value) const{
    Node* n = getNodeFor(value, root);
    if(n->right) {
        n = n->right;
        while(n->left){
            n =  n->left;
        }
        return n;
    }
    else {
        while(n->parent) {
            n = n->parent;
            if (n->info > value) {
                return n;
            }
        }
        return 0;
    }
}


template<class Tree>
Tree BST<Tree>::getSuccessor(Tree value) const {
    Node *n = getSuccessorNode(value);
    if(!n){
        cout<<"you lost";
    }
    return n->info;
}

template<class Tree>
Tree BST<Tree>::getMax() const {
    Node *n = getMaxNode();
    return n->info;
}

template<class Tree>
typename BST<Tree>::Node* BST<Tree>::getMaxNode() const {
    Node *n = root;
    while(n->right){
        n = n->right;
    }
    return n;
}

template<class Tree>
Tree BST<Tree>::getMin() const {
    Node *n = getMinNode();
    return n->info;
}

template<class Tree>
typename BST<Tree>::Node* BST<Tree>::getMinNode() const {
    Node *n = root;
    while(n->left){
        n = n->left;
    }
    return n;
}
template<class Tree>
bool BST<Tree>::remove(Tree value){
    Node* n = getNodeFor(value, root);
    
    if(n) {
        if (!n->left && !n->right) { // Remove leaf
            if (n == root) { // Node is root
                root = NULL;
                delete n;
            }
            else if (n->parent->left == n) {
                n->parent->left = NULL;
                delete n;
            }
            else {
                n->parent->right = NULL;
                delete n;
            }
            return true;
        }
        else if (!n->right) {                // Remove node with only left child
            if (!n->parent) {// Node is root
                root = n->left;
                n->left->parent = NULL;
            }

            else if (n->parent->left == n) {
                n->parent->left = n->left;
                n->left->parent = n->parent;
            }

            else {
                n->parent->right = n->left;
                n->left->parent = n->parent;
            }
            delete n;
            return true;
        }
        else if (!n->left) {                // Remove node with only right child
            if (!n->parent) { // Node is root
                root = n->right;
                n->right->parent = NULL;
            }
            else if (n->parent->left == n)  {
                n->parent->left = n->right;
                n->right->parent = n->parent;
            }
            else {
                n->parent->right = n->right;
                n->right->parent = n->parent;
            }

            delete n;
            return true;
        }
        else {                                      // Remove node with two children
            // Find successor (leftmost child of right subtree)
            Node* suc = n->right;
            while (suc->left)
                suc = suc->left;
            int tmp = suc->info;
            //suc->parent->left = NULL;
            remove(tmp);     // Remove successor
            n->info = tmp;
            return true;// Node found and removed
        }
    }
    return false; // Node not found */
    
}

Card::Card(string s, string v) {
    if(s == "c"){
        suit = 0;
    }
    else if(s == "d"){
        suit = 1;
    }
    else if(s == "s"){
        suit = 2;
    }
    else if(s == "h"){
        suit = 3;
    }
    else{
        // error
    }

    if(v == "a"){
    value = 0;
    }
    else if (v == "2"){
    value = 1;
    }
    else if (v == "3"){
    value = 2;
    }
    else if (v == "4"){
    value = 3;
    }
    else if (v == "5"){
    value = 4;
    }
    else if (v == "6"){
    value = 5;
    }
    else if (v == "7"){
    value = 6;
    }
    else if (v == "8"){
    value = 7;
    }
    else if (v == "9"){
    value = 8;
    }
    else if (v == "10"){
    value = 9;
    }
    else if (v == "j"){
    value = 10;
    }
    else if (v == "q"){
    value = 11;
    }
    else if (v == "k"){
    value = 12;
    }
    else{
    // error
    }
}

Card::Card(const Card& source){
    suit = source.getSuitInt();
    value = source.getValueInt();
}

Card::~Card(){};

Card* Card::operator=(const Card& source) {
    suit = source.getSuitInt();
    value = source.getValueInt();
        return this;
}
bool Card::operator>(const Card& source) const {
    if(this->suit == source.suit) {
        return (this->value > source.value);
    }
    return(this->suit > source.suit);
}

bool Card::operator<(const Card& source) const {
    if(this->suit == source.suit) {
        return (this->value < source.value);
    }
    return(this->suit < source.suit);
}

bool Card::operator==(const Card& source) const{
    return (this->suit == source.suit && this->value == source.value);
}
string Card::getValue() const {
    if( value == 0){
        return "a";
    }
    else if(value == 1) {
        return "2";
    }
    else if(value == 2) {
        return "3";
    }
    else if(value == 3) {
        return "4";
    }
    else if(value == 4) {
        return "5";
    }
    else if(value == 5) {
        return "6";
    }
    else if(value == 6) {
        return "7";
    }
    else if(value == 7) {
        return "8";
    }
    else if(value == 8) {
        return "9";
    }
    else if(value == 9) {
        return "10";
    }
    else if(value == 10) {
        return "j";
    }
    else if(value == 11) {
        return "q";
    }
    else if(value == 12) {
        return "k";
    }
    else{
        return "invalid input";
    }
}

int Card::getValueInt() const{
    return value;
}
string Card::getSuit() const{
    if(suit == 0) {
        return "c";
    }
    else if (suit == 1) {
        return "d";
    }
    else if (suit == 2) {
        return "s";
    }
    else if(suit == 3) {
        return "h";
    }
    else{
        return "invalid suit";
    }
}
int Card::getSuitInt() const{
    return suit;
}

ostream& operator <<(ostream& stream, const Card& source) {
    stream << source.getSuit() << " " << source.getValue() << endl;
    return stream;
}





































/*CardBST::Card(string strcard) {
    root = NULL;

    if(card == "x x"){
        int suit = -1;
        int value = -1;
        return;
    
    }
    char suit = card[0];
    if(s == 'c'){
        suit = 0;
    }
    else if(s == 'd'){
        suit = 1;
    }
    else if(s == 's'){
        suit = 2;
    }
    else if(s == 'h'){
        suit = 3;
    }
    string v = card.substr(2, card.length() - 2);
    if (v == "a"){
        value = 0;
    }
    else if (v == "j"){
        value = 10;
    }
    else if (v == "q"){
        value = 11;
    }
    else if (v == "k"){
        value = 12;
    }
    else {
        value = stoi(v) - 1;
    }
}
    // Destructor
BST::~BST() {
    clear(root);
}
void BST::clear(Node* n){
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}
    // Insert
    bool BST::insert(string strcard){
        Card card {strcard};
        if (!root) {
            root = new Node(strcard);
            return true;
        }
        return insert(strcard, root);
    }

    bool BST::insert(Card card, Node *n){
        
    if (card > n->info) {
        if (!n->right) {
            n->right = new Node(card);
            n->right->parent = n;
            return true;
        }
        return insert(card, n->right);
    }
    if (card < n->info) {
        if (!n->left) {
            n->left = new Node(card);
            n->left->parent = n;
            return true;
        }
        return insert(card, n->left);
    }
    return false; 

    }

void BST::printInOrder() const{
    printInOrder(root);
}

void BST::printInOrder() const{
    if(!n) {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}


Card BST::getMin() const {
    Node* curr = root;
    while(curr->left){
        curr = curr->left;
    }
    return curr->info;
}

Card BST::getMax() const {
    Node* curr = root;
    while(curr->right) {
        curr = curr->right;
    }
    return curr->info;
}

bool BST::contains(string strcard) const {
    Card card {strcard};
    if (getNodeFor(strcard, root) == nullptr){
        return false;
    }
    return true;
}

bool BST::contains(Card card) const {
    return contains(card.toString())
}

BST::Node* BST::getNodeFor(Card card, Node* n) const{
    if (n) {
        if (n->info == card){
            return n;
        }
        Node* leftRes = getNodeFor(card, n->left);
    }
    if (leftRes){
        return leftRes;
    }
    Node* rightRes = getNodefor(card, n->right);
    if(rightRes){
        return rightRes;
    }
    return nullptr;
}

//Predecessor
BST::getPredecessorNode(Card card) const {
    Node* pre = nullptr;
    Node* curr = root;
    if(!curr){
        return nullptr;
    }

    while(curr && curr -> info != card) {
        if(curr->info > card) {
            curr = curr->left;
        }
        else{
            pre = curr;
            curr = curr ->right;
        }
    }

    if(curr && curr->left) {
        pre = curr->left;
        while(pre->right){
            pre = pre ->right;
        }
    return pre;
    }
}

Card BST::predessor(string strcard) const {
    Card card {strcard};
    const Card nullCard {"x x"};
    Node* pre = getPredecessorNode(card);
    if(pre == nullptr){
        return nullCard;
    }
    else{
        pre->info;
    }
}

Card BST::predecessor(Card card) const {
    return predecessor(card.toString());
}

//Successor

BST::Node* BST::getSuccessorNode(Card card) const {
    Node* suc = nullptr;
    Node* curr = root;
    if(!curr){
        return nullptr;
    }

    while (curr && curr->info != card) {
        if(curr->info > card) {
            suc = succ;
            curr = curr-> left;
        }
        else{
            curr = curr->right;
        }
    }
}

*/
/*class Cards{
    Cards();                   // constructor
    ~Cards();                  // destructor
    bool insert(int value);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    // 8 METHODS YOU MUST IMPLEMENT in intbst.cpp:
    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(int value) const;  // true if value is in tree
}*/
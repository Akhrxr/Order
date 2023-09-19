//-----------------------------------------------------------------------------
// Dictionary.cpp
// Cpp file for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<cmath>
#include"Dictionary.h"

Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R->key == "nillrt") {
      return nil;
    }
    else if (k == R->key) {
        return R;
    }
    else if (k < R->key) {
      return search(R->left, k);
    }
    else { // k > x.key 
      return search(R->right, k);
    }
}

void Dictionary::Transplant(Node* U, Node* V) {
    if (U->key != "nillrt" && V) {
        if (U->parent->key == "nillrt")
            this->root = V;
        else if (U == U->parent->left)
            U->parent->left = V;
        else 
            U->parent->right = V;
        if (V->key != "nillrt")
            V->parent = U->parent;
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R->key != "nillrt" && R) {
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      remove(R->key);
    }
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R->key != "nillrt" && R) {
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        std::string vals = std::to_string(R->val);
        s.append(vals);
        s.append("\n");
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N){
    if (R!= nil && R) {
        if (R != N) {
            Dictionary::setValue(R->key, R->val);
            Dictionary::preOrderCopy(R->left, N);
            Dictionary::preOrderCopy(R->right, N);
        }
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R!=nil && R) {
        s.append(R->key);
        s.append("\n");
        Dictionary::preOrderString(s, R->left);
        Dictionary::preOrderString(s, R->right);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R){
    if (R->key != "nillrt" && R) {
        while (R->left->key != "nillrt") {
            R = R->left;
        }
    }
    //else std::cerr << "R is nil in findMin \n";
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    if (R != nil && R) {
        while (R->right->key != "nillrt") {
            R = R->right;
        }
    }
    //else std::cerr << "R is nil in findMax\n";
    return R;
}


Dictionary::Node* Dictionary::findNext(Node* N){
    if (N == nil || N == Dictionary::findMax(this->root)) return nil;
    if (N->right->key != "nillrt")                 // case 1
        return Dictionary::findMin(N->right);
    Node* y = N->parent;                 // case 2
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N == nil || N == Dictionary::findMin(this->root)) return nil;
    if (N->left->key != "nillrt")                 // case 1
        return Dictionary::findMax(N->left);
    Node* y = N->parent;                 // case 2
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}
// Class Constructors & Destructors ----------------------------------------

Dictionary::Dictionary() {
    nil = new Node("nillrt" , 0);
    nil->right = nullptr;
    nil->left = nullptr;
    nil->parent = nullptr;
    this->current = this->root = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("nillrt" , 0);
    nil->right = nullptr;
    nil->left = nullptr;
    nil->parent = nullptr;
    this->current = this->root = nil;
    num_pairs = 0;
    Dictionary::preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    Dictionary::clear();
    root = current = nil = nullptr;
    delete root;
    delete current;
    delete nil;
}

// Access functions --------------------------------------------------------

int Dictionary::size() const {
    return this->num_pairs;
}

bool Dictionary::contains(keyType k) const {
    /*std::string s = "";
    Dictionary::preOrderString(s, this->root);
    int M = k.length();
    int N = s.length();
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++) {
            if (s[i + j] != k[j])
                break;
        }
        if (j == M) {
            return true;
        }
    }
    return false;*/
    return (search(root, k) != nil);
}

valType& Dictionary::getValue(keyType k) const{
    if (!Dictionary::contains(k)) {
        throw std::logic_error("This dictionary does not contain key k. \n");
    }
    Node* R = root;
    while (R->key != k){
        if (R->key > k) {
            R = R->left;
        }
        else {
            R = R->right;
        }
    }
    return R->val;
}

bool Dictionary::hasCurrent() const{
    return (this->current->key != "nillrt" && this->current);
}

keyType Dictionary::currentKey() const{
    if (!Dictionary::hasCurrent()) {
        throw std::logic_error ("Cannot call currentKey() as current is not defined \n");
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if (!Dictionary::hasCurrent()) {
        throw std::logic_error ("Cannot call currentVal() as current is not defined \n");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

void Dictionary::clear(){
    if (num_pairs != 0) {
        postOrderDelete(this->root);
    }
}

void Dictionary::setValue(keyType k, valType v){
    Node* y = nil;
    Node* x = this->root;
    //if (!Dictionary::contains(k)) {
        Node* z = new Node(k, v);
        while (x != nil && x->key != z->key) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else 
                x = x->right;
        }
        if (x->key == z->key) { //rewrites it if its equal to it.
            x->val = v;
            return;
        }
        z->parent = y;
        if (y == nil) {
            this->root = z; 
            root->left = root->right = nil;
        }  // tree T was empty
        else if (z->key < y->key){
            y->left = z;
            z->left = z->right = this->nil;
        }
        else {
            y->right = z;
            z->left = z->right = this->nil;
        }
        ++num_pairs;

    //}
    /*else {
        while (x->key != k) {
            y = x;
            if (k < x->key)
                x = x->left;
            else 
                x = x->right;
        }
        x->val = v;
    }*/
}

void Dictionary::remove(keyType k){
    Node* y = nil;
    Node* z = this->root;
    while (z->key != k && z != nil) {
        y = z;
        if (k < z->key)
            z = z->left;
        else 
            z = z->right;
    }
    if (z == nil) {
        throw std::logic_error("Key is not in this list already \n");
    }
    if (current == z) {
        current = nil;
    }
    if (z->left == nil)               // case 1  or case 2.1 (right only)
      Transplant(z, z->right);
    else if (z->right == nil)       // case 2.2 (left only)
      Transplant(z, z->left);
    else {                          // case 3
      y = findMin(z->right);
      if (y->parent != z){
        Transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      Transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
    }
    --num_pairs;
    delete z;
}

void Dictionary::begin(){
    this->current = findMin(this->root);
}

void Dictionary::end(){
    this->current = findMax(this->root);
}

void Dictionary::next(){
    if (!Dictionary::hasCurrent()) {
        throw std::logic_error ("Cannot call next() as current is not defined \n");
    }
    this->current = findNext(this->current);
}

void Dictionary::prev(){
    if (!Dictionary::hasCurrent()) {
        throw std::logic_error ("Cannot call prev() as current is not defined \n");
    }
    this->current = findPrev(this->current);
}

// Other Functions ---------------------------------------------------------

std::string Dictionary::to_string() const{
    std::string s = "";
    Dictionary::inOrderString(s, this->root);
    return s;
}

std::string Dictionary::pre_string() const{
    std::string s = "";
    Dictionary::preOrderString(s, this->root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const{
    std::string s = to_string();
    std::string p = D.to_string();
    return (s == p);
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
    return (A.equals(B));
}

Dictionary& Dictionary::operator=( const Dictionary& D ){
    if( this != &D ){ // not self assignment
      // make a copy of Q
      Dictionary temp = D;

      // then swap the copy's fields with fields of this
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}

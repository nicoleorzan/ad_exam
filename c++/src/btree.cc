#include <btree.h>
#include <memory>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <math.h>
#include <vector> 


template<typename TK, typename TV>
void BTree<TK,TV>::insert( std::pair<TK,TV> p ){ 
  this->root->insert_node(p); 
}

// insert node
template<typename TK, typename TV>
void BTree<TK,TV>::BNode::insert_node(std::pair<TK,TV> p){
  // BNode *tmproot = this->root_node.get();

  // key is already present
  if( this->pair.first == p.first )
    this->pair.second = p.second;
  //std::cout << "already present" << std::endl;
  else if( this->pair.first > p.first ){
    if( this->left == nullptr ){
      this->left = new BNode{p, this};
      return;
    }
    else
      this->left->insert_node(p);
  }    
  else{
    if( this->right == nullptr ){
      this->right = new BNode{p, this};
      return;
    }
    else
      this->right->insert_node(p);

  }
}


template<typename TK, typename TV>
void BTree<TK,TV>::print() const{
  print(root);  
}

template<typename TK, typename TV>
void BTree<TK,TV>::print(const BNode *n) const{
  //inorder printing of the tree

  if(n != nullptr){
    print(n->left);
    std::cout<<"key: "<< n->pair.first << ", value: "<< n->pair.second <<"\n";
    print(n->right);
  }
}

//deleting the tree
template<typename TK, typename TV>
void BTree<TK,TV>::clear(){
  if (root==nullptr)
    std::cout<<"Tree is empty"<<"\n";
  
  clear(root);
  root=nullptr;
}

template<typename TK, typename TV>
void BTree<TK,TV>::clear(BNode *n){
  if(n != nullptr){
    clear(n->left);
    clear(n->right);  
    delete n;
    n = nullptr;
  }
}

template<typename TK, typename TV>
BTree<TK,TV>::~BTree(){
  clear(root);
}

template<typename TK, typename TV>
void BTree<TK,TV>::diagram(){
  diagram(root, 6);  
}

template<typename TK, typename TV>
void BTree<TK,TV>::diagram(BNode* p, int indent){
  if(p != nullptr) {
    if (indent) {
      std::cout << std::setw(indent) << ' ';
      std::cout<< p->pair.first<<std::endl;
    }
    /* if (p->left && p->right){
      diagram(p->left, indent - 2);
      diagram(p->right, indent + 2);
      }*/
    if (p->left) {
      diagram(p->left, indent - 2);
    }
    if (p->right) {
      diagram(p->right, indent + 2);
    }
  }
}

/*
template<typename TK, typename TV>
bool BTree<TK,TV>::isbalanced(){
  if ( isbalanced(root) == -1 ){
    std::cout<<"no"<<std::endl;
    return false;
  } else {
    std::cout<<"yes"<<std::endl;
    return true;
  }
}

template<typename TK, typename TV>
int BTree<TK,TV>::isbalanced(BNode *n){
  if (n == NULL) return 0;
  
  if(isbalanced(n->left) == -1) return -1; 
  if(isbalanced(n->right) == -1) return -1; 

  int diff = isbalanced(n->left) - isbalanced(n->right);

  if(abs(diff) > 1) return -1;
  else return  std::max(isbalanced(n->left),isbalanced(n->right)) + 1;
}
*/
//template<typename TK, typename TV>
//bool BTree<TK,TV>::find(){



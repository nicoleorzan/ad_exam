#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

#ifndef __BTREE__
#define __BTREE__

// class BTree;

template<typename TK, typename TV>
  class BTree{
  struct BNode{
    std::pair<TK,TV> pair;
    BNode* left;
    BNode* right;
    BNode* father;
		
		
    // constructor for pair, only for root father is nullptr
  BNode(std::pair<TK,TV> p): pair{p}, left{nullptr}, right{nullptr}, father{nullptr} {}
    // constructor with father
  BNode(std::pair<TK,TV> p, BNode* f): pair{p}, left{nullptr}, right{nullptr}, father{f} {}
    // constructor for 2 elements separated
    // BNode(TK key, TV val): pa{key,val}, left{nullptr}, right{nullptr} {}
		
    void insert_node( std::pair<TK,TV> p );
		
		
  }; // BNode


  // root node
  BNode* root;
  void print(const BNode *n) const;
  void clear(BNode *n);
  void diagram(BNode* n, int indent);
  //int balance(BNode *n);
  //int isbalanced(BNode* n);
  //void build_tree(std::vector<BNode*> &nodes);
  
 public:
		
  // constructor for pair
 BTree(std::pair<TK,TV> p): root{new BNode{p} } {}
  //destructor
  ~BTree();
  // constructor for 2 elements separated
  // BTree(TK key, TV val): root{new BNode{key,val}} {}
		
  void insert( std::pair<TK,TV> p );
  void print() const;
  void clear();
  void diagram();
  //void balance();
  //bool isbalanced();
  //void erase(int key);
  //void find(int val);
  
  class Iterator;
		
  Iterator begin(){
    BNode *pt = root;
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return Iterator{pt};
  }	
  Iterator end(){	return Iterator{nullptr}; }

  class ConstIterator;
  ConstIterator begin() const {
    BNode *pt = root;
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return Iterator{pt};
  }	
  ConstIterator end() const {	return Iterator{nullptr}; }

  ConstIterator cbegin() const {
    BNode *pt = root;
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return Iterator{pt};
  }	
  ConstIterator cend() const {	return Iterator{nullptr}; }
}; // BTree


// Iterator
template <typename TK, typename TV>
  //class BTree<TK,TV>::Iterator {
  class BTree<TK,TV>::Iterator: public std::iterator<std::bidirectional_iterator_tag, TK, TV>{
    using BNode = BTree<TK,TV>::BNode;
    BNode* current;

 public:
 Iterator(BNode* n) : current{n} {}
  TK& operator*() const { return current->pair.first; }

  // ++it
  Iterator& operator++() {
    BNode *f, *ff;
    if( current->right != nullptr ){
      //std::cout << "[++] curr->right != nullptr" << std::endl;
      f = current->right;
      while( f->left != nullptr)
	f = f->left;
      current = f;
      return *this;
    }
			
    // else (current->right == nullptr)
			
    f = current;
    ff = current->father;
    if( ff == nullptr ){   // f = root no right branch
      current = ff;
      return *this;
    } 
    if( ff->left != nullptr && ff->left->pair.first == f->pair.first ){ // ff = right father
      current = ff;
      return *this;
    }
    if( ff->right->pair.first == f->pair.first ){ // ff = left father
      while(  ff != nullptr &&  ff->right->pair.first == f->pair.first   ){
	f = ff;
	ff = f->father;
      }
      std::cout << "exit from while" << std::endl;
      current = ff;
      return *this;
    }
			
  }

  /*
  // it++
  Iterator operator++(int) {
  Iterator it{current};
  ++(*this);
  return it;
  }
  */
		
  bool operator==(const Iterator& other) {
    return this->current == other.current;
  }
		
  bool operator!=(const Iterator& other) { return !(*this == other); }
		
  bool is_nullptr() { return current == nullptr; }
};

template <typename TK, typename TV>
struct comparison {
  bool operator()(const TK& a, const TK& b) { return a < b; }
};

template <typename TK, typename TV>
  class BTree<TK,TV>::ConstIterator : public BTree<TK,TV>::Iterator {
  using parent = BTree<TK,TV>::Iterator;

 public:
  using parent::Iterator;
  const TK& operator*() const { return parent::operator*(); }
};

#endif // __BTREE__

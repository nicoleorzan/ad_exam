#include <iostream>
#include <memory>
#include <vector>
// #include <iterator>

#ifndef __BTREE__
#define __BTREE__

// class BTree;

template<typename TK, typename TV>
class BTree{
  struct BNode{
    std::pair<TK,TV> pair;
    std::unique_ptr<BNode> left;
    std::unique_ptr<BNode> right;
    BNode* next;
		
		
    // constructor for pair, only for root father is nullptr
  BNode(std::pair<TK,TV> p): pair{p}, left{nullptr}, right{nullptr}, next{nullptr} {}
    // constructor with father
  BNode(std::pair<TK,TV> p, BNode* f): pair{p}, left{nullptr}, right{nullptr}, next{f} {}
    // constructor for 2 elements separated
    // BNode(TK key, TV val): pa{key,val}, left{nullptr}, right{nullptr} {}
    
  // BNode copy const
  BNode(const BNode& b): pair{b.pair}, left{nullptr}, right{nullptr}, next{b.next} {
  	#ifdef DEBUG
	std::cout << "BNode copy ctor" << std::endl;
	#endif
	if( b.left != nullptr )
		left.reset( new BNode{ *b.left } );
	if( b.right != nullptr )
		right.reset( new BNode{ *b.right } );
  }

		
  void insert_node( std::pair<TK,TV> p );
  void clear_node();
		
		
  }; // BNode


  // root node
    // root node
  std::unique_ptr<BNode> root;
  
  // void print(std::unique_ptr<BNode> &n);
  // void clear(std::unique_ptr<BNode> &n);
  // void print(const BNode *n) const;
  void clear(BNode *n);
  // void diagram(BNode* n, int indent);
  //int balance(BNode *n);
  //int isbalanced(BNode* n);
  //void build_tree(std::vector<BNode*> &nodes);
  
 public:
		
  // default constructor
  BTree(): root{nullptr} {
  #ifdef DEBUG
  	std::cout << "BTree()" << std::endl;
  #endif
  }
  
  // constructor for pair
 BTree(std::pair<TK,TV> p): root{new BNode{p} } {
   #ifdef DEBUG
  	std::cout << "BTree(std::pair<TK,TV>)" << std::endl;
  #endif
 
 }
  
  //destructor
  ~BTree();
  // constructor for 2 elements separated
  // BTree(TK key, TV val): root{new BNode{key,val}} {}
  
  
  // copy const
  BTree(const BTree& t) /*: root { new BNode{ t.root->pair } } */ {
  	#ifdef DEBUG
  	std::cout << "BTree copy constructor: BTree(const BTree& t)" << std::endl;
  	#endif
  	root.reset(new BNode{ *t.root } );
  }
  
  
  //copy assignment
  BTree& operator=(const BTree& t){
  	#ifdef DEBUG
  	std::cout << "BTree copy assignment: BTree& operator=(const BTree& t)" << std::endl;
  	#endif
  	root.reset(new BNode{ *t.root } );
  	return *this;
  }
  
  // move const
  BTree(BTree&& t): root{std::move(t.root)} { 
  	#ifdef DEBUG
  	std::cout << "BTree move const: BTree(BTree&& t)" << std::endl;
  	#endif 
  }
		
  // move assignment
  BTree& operator=(BTree&& t){ 
  	#ifdef DEBUG
  	std::cout << "BTree move assignment: BTree& operator=(BTree&& t)" << std::endl; 
  	#endif
  	root = std::move(t.root);
  	return *this;
  }
	
		
		
		
		
  void insert( std::pair<TK,TV> p );
  void print();
  void clear();
  // void diagram();
  //void balance();
  //bool isbalanced();
  //void erase(int key);
  //void find(int val);
  
  class Iterator;
		
  Iterator begin(){
  	if( root == nullptr )
  		return Iterator{nullptr};
    BNode *pt = root.get();
    // leftmost()
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return Iterator{pt};
  }	
  
  Iterator end(){ return Iterator{nullptr}; }

 // Iterator find(TK k);

  /*
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
  */
  
}; // BTree


// Iterator
template <typename TK, typename TV>
class BTree<TK,TV>::Iterator {

    using BNode = BTree<TK,TV>::BNode;
    BNode* current;

 public:
   
   Iterator(BNode* n) : current{n} {}
   std::pair<TK,TV>& operator*() { return current->pair; }

  // ++it
  Iterator& operator++() {
  	if( current->right != nullptr ){
  		BNode *p;
  		p = current->right.get();
  		while( p->left != nullptr )
  			p = p->left.get();
  		current = p;
  		// return *this;
  	}
  	else{
  		if( current->next != nullptr){
  		    current = current->next; 
  		}
  		else{
  			current = nullptr;
  		}
  	}
  
  	return *this;
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
}; // Iterator

/*
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
*/
#endif // __BTREE__

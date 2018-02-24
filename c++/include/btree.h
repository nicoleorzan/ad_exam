#include <iostream>
#include <memory>
#include <vector>
// #include <iterator>

#ifndef __BTREE__
#define __BTREE__


//!\class BTree
/**
 *This class contains our implementation of a Binary Search Tree, which is a sorted container of items 
 *that allows fast lookup, addition and remotion of the same. 
 *The class is templated on the type of keys and values of the nodes.
 */ 
template<class TK, class TV, class Tcomp>
  class BTree{

  // class Invalid_BNode;


  //!\class BNode
  /** 
   *The Members of the tree are created as classes. Each Node has a pair kay-value, two unique pointers 
   *to the left and right childs, and a raw pointer to the father node. The constructor of the node 
   *takes as argument a key-value pair and sets the childs to nullpointers. 
   */
  class BNode{

  public:

    Tcomp comparison;
    
    std::pair<TK,TV> pair;
    std::unique_ptr<BNode> left;
    std::unique_ptr<BNode> right;
    //Invalid_BNode* invalid_parent;
    BNode* next;
			
    // constructor for pair, only for root father is nullptr
  BNode(std::pair<TK,TV> p): pair{p}, left{nullptr}, right{nullptr}, next{nullptr} {}
    // constructor for root (with invalid node as father)
    // BNode(std::pair<TK,TV> p, Invalid_BNode* inv): pair{p}, left{nullptr}, right{nullptr}, invalid_parent{inv} {}
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
  int isbalanced_node();
  void diagram(int indent);
  void erase_node();
  void find_node(TK key);
		
  }; // BNode

  /* class Invalid_BNode{
    
  public:
    std::pair<TK,TV> p;
    BNode* child_root;
    // std::unique_ptr<BNode> child_root{};
    
  Invalid_BNode(std::unique_ptr<BNode> node): p{-7777,-7777},  child_root{node.get()} {}
    //Invalid_BNode(std::pair<TK,TV> rootpair): p{-7777,-7777},  child_root{new BNode{rootpair}} {}
    
    };*/

  // std::unique_ptr<Invalid_BNode> invalid;
  std::unique_ptr<BNode> root;
  //std::unique_ptr<Invalid_BNode> invalid;
  
  void clear(BNode *n);
  void built_tree(std::vector<std::pair<TK,TV>> &vec, int start, int end);

  
 public:

  Tcomp comparison;
  
  // default constructor
 BTree() {
  #ifdef DEBUG
  	std::cout << "BTree()" << std::endl;
  #endif
  }
  
  // constructor for pair, with comparison operator
 BTree(std::pair<TK,TV> p, Tcomp c=Tcomp{}): root{new BNode{p}}, comparison{c} {
   #ifdef DEBUG
  	std::cout << "BTree(std::pair<TK,TV>)" << std::endl;
  #endif
	//invalid=new Invalid_BNode{root};
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
  void diagram();
  void balance();
  bool isbalanced();
  void erase(TK key);

  struct comparison {
    bool operator()(const TK& a, const TK& b) { return a < b; }
  };
  
  class Iterator;
		
  Iterator begin(){
    if( root == nullptr )
    return Iterator{nullptr};
    BNode *pt = root.get();
    std::cout<<"before leftmost"<<std::endl;
    return (leftmost(pt));
    /*BNode *pt = root.get();
      while( pt->left != nullptr )
      pt = pt->left.get();	
      return Iterator{pt};*/
  }	
  
  Iterator end() { return Iterator{nullptr}; }

  Iterator leftmost(BNode *b){
    std::cout<<"inside leftmost"<<std::endl;
    while ( b->left != nullptr) b = b->left.get();
    return Iterator{b};
  }

  Iterator find(TK k){
    //TO FIX RETURN --> MUST BE end()
    if( root == nullptr ) 
    	return Iterator{nullptr};
    	
    // std::cout<<"iterator find"<<std::endl;
    BNode *pt = root.get();
    
    while ( comparison(pt->pair.first, k) || comparison(pt->pair.first, k) ){
      if( comparison( pt->pair.first, k ) ){
	if (pt->right != nullptr) {
	  //std::cout<<"key val "<<pt->pair.first<<std::endl;
	  pt = pt->right.get();
	}
	else return Iterator{nullptr};
      }
      else {
	if (pt->left!= nullptr) {
	  //std::cout<<"key val "<<pt->pair.first<<std::endl;
	  pt = pt->left.get();
	}
	else return Iterator{nullptr};
      }
    }
    return Iterator{pt};
    
  } // find
  
  class ConstIterator;
  
  /*
  ConstIterator begin() const {
    if( root == nullptr )
    return ConstIterator{nullptr};
    BNode *pt = root.get();
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return ConstIterator{pt};
  }	
  ConstIterator end() const {return ConstIterator{nullptr}; } */

  ConstIterator cbegin() const {
    if( root == nullptr )
    return ConstIterator{nullptr};
    BNode *pt = root.get();
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return ConstIterator{pt};
  }	
  ConstIterator cend() const {	return ConstIterator{nullptr}; }
  
  
}; // BTree


// Iterator
template <class TK, class TV, class Tcomp>
  class BTree<TK,TV,Tcomp>::Iterator/*: public std::iterator<std::forward_iterator_tag, TK,TV,Tcomp> */ {

  using BNode = BTree<TK,TV,Tcomp>::BNode;
    BNode* current;

 public:
   
   Iterator(BNode* n) : current{n} {}
   std::pair<TK,TV>& operator*() const { return current->pair; }

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

  
  // it++
  Iterator operator++(int) {
  	Iterator it{current};
  	++(*this);
  	return it;
  }
  
		
  bool operator==(const Iterator& other) {
    return this->current == other.current;
  }
		
  bool operator!=(const Iterator& other) { return !(*this == other); }
		
  bool is_nullptr() { return current == nullptr; }
}; // Iterator

//const iterator
template<class TK, class TV, class Tcomp>
  class BTree<TK,TV,Tcomp>::ConstIterator: public BTree<TK,TV,Tcomp>::Iterator  {
  using parent = BTree<TK,TV,Tcomp>::Iterator;

 public:
  using parent::Iterator;
  const std::pair<TK,TV>& operator*() const { return parent::operator*(); }
};

#endif // __BTREE__

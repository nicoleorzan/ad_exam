#include <iostream>
#include <memory>
#include <vector>

#ifndef __BTREE__
#define __BTREE__


//!\class BTree
/**
 *This class contains our implementation of a Binary Search Tree, which is a sorted container of items 
 *that allows fast lookup, addition and remotion of the same. 
 *The class is templated on the type of keys and values of the nodes.
 */ 
template<class TK, class TV, class Tcomp=std::less<TK>>
  class BTree{

  //!\class BNode
  /** 
   *The Members of the tree are created as classes. Each Node has a pair kay-value, two unique pointers 
   *to the left and right childs, and a raw pointer to the father node. The constructor of the node 
   *takes as argument a key-value pair and sets the childs to nullpointers. 
   */
  class BNode{

  public:

    /**custom comparison operator*/
    Tcomp comparison;
    /** key-value pair*/
    std::pair<TK,TV> pair;
    /** left child as unique_ptr */
    std::unique_ptr<BNode> left;
    /** right child as unique_ptr */
    std::unique_ptr<BNode> right;
    /** parent node */
    BNode* next;
			
   /** BNode constructor for pair key-value, only for root father is nullptr */
  BNode(std::pair<TK,TV> p): pair{p}, left{nullptr}, right{nullptr}, next{nullptr} {}
   /** BNode constructor with father node */
  BNode(std::pair<TK,TV> p, BNode* f): pair{p}, left{nullptr}, right{nullptr}, next{f} {}

  /** BNode copy constuctor */
  BNode(const BNode& b): pair{b.pair}, left{nullptr}, right{nullptr}, next{b.next} {
  	#ifdef DEBUG
	std::cout << "BNode copy ctor" << std::endl;
	#endif
  }
   

    /**
     * Bnode function for inserting a new Node
     */		
    void insert_node( std::pair<TK,TV> p );
    /**
     * Bnode utility function to check if the tree is balanced
     */
    int isbalanced_node();
    
    /**
     * BNode function that recursively insert the node of the tree in another tree passed as reference
     */    
    void copy_node(BTree<TK,TV,Tcomp>& t){
    #ifdef DEBUG
    	std::cout << "BNode::copy_node()" << std::endl;
    #endif 
    
    	if( this->left != nullptr ){
    		t.insert(left->pair);
    		this->left->copy_node(t);
    	}
    	if( this->right != nullptr ){
    		t.insert(right->pair);
    		this->right->copy_node(t);
    	}
    };
    
    /**
     * BNode function that recursively measure the depth of a tree
     */    
    void measure_depth(int&, int&);
		
  }; // BNode





  /**root node of the tree as unique_ptr */
  std::unique_ptr<BNode> root;

   /** BTree private function to built the tree using a given vector of pairs  */
  void built_tree(std::vector<std::pair<TK,TV>> &vec, int start, int end);

  
 public:

  /**custom comparison operator */
  Tcomp comparison;
  
  /** BTree default constructor */
  BTree() {
#ifdef DEBUG
    std::cout << "BTree()" << std::endl;
#endif
  }
  
  /** BTree constructor with pair key-value, with comparison operator */
 // BTree(std::pair<TK,TV> p, Tcomp c=std::less<TK>): root{new BNode{p}}, comparison{c} {  
 BTree(std::pair<TK,TV> p, Tcomp c=Tcomp{}): root{new BNode{p}}, comparison{c} {
#ifdef DEBUG
    std::cout << "BTree(std::pair<TK,TV>)" << std::endl;
#endif
  }
  
  /** BTree destructor */
  ~BTree();  
  
  /** copy constructor */
  BTree(const BTree& t) {
  	#ifdef DEBUG
  	std::cout << "BTree copy constructor: BTree(const BTree& t)" << std::endl;
  	#endif
  	root.reset(new BNode{ *t.root } );
  	t.root->copy_node(*this);
  }
  
  
  /** copy assignment */
  BTree& operator=(const BTree& t){
  	#ifdef DEBUG
  	std::cout << "BTree copy assignment: BTree& operator=(const BTree& t)" << std::endl;
  	#endif
  	root.reset(new BNode{ *t.root } );
  	t.root->copy_node(*this);
  	return *this;
  }
  
  /** move constructor */
  BTree(BTree&& t): root{std::move(t.root)} { 
  	#ifdef DEBUG
  	std::cout << "BTree move const: BTree(BTree&& t)" << std::endl;
  	#endif 
  }
		
  /** move assignment */
  BTree& operator=(BTree&& t){ 
  	#ifdef DEBUG
  	std::cout << "BTree move assignment: BTree& operator=(BTree&& t)" << std::endl; 
  	#endif
  	root = std::move(t.root);
  	return *this;
  }
		
  /**  BTree function for inserting a new Node */
  void insert( std::pair<TK,TV> p );
  /** BTree function to print the tree using the Constiterator  */
  void print();
  /** BTree function to clear the tree  */
  void clear();
  /** BTree function to balance the tree  */
  void balance();
  /** BTree function to check if the tree is balanced  */
  bool isbalanced();
  /** BTree function to measure the max depth of the tree  */
  int measure_depth();

  struct comparison {
    bool operator()(const TK& a, const TK& b) { return a < b; }
  };
  
  /** 
   *  An Iterator for the BTree acts like a pointer and allows the user to access the nodes
   *  of the tree following the keys order
   */
  class Iterator;

  /** Iterator begin function, which returns the smallest key value   */
  Iterator begin(){
    if( root == nullptr )
      return Iterator{nullptr};
    BNode *pt = root.get();
    return (leftmost(pt));
  }	
  /** Iterator end function  */
  Iterator end() { return Iterator{nullptr}; }
  
  /** 
   * Iterator leftmost function, which returns an iterator to the 
   * leftmost node with respect to the given one
   */
  Iterator leftmost(BNode *b){
    while ( b->left != nullptr) b = b->left.get();
    return Iterator{b};
  }
  
  /**
   * Iterator find function, which returns an iterator to the 
   * node with the given key. If the node is not found returns end function.
   */
  Iterator find(TK);
  
  /** Like the Iterator class but cannot modify what it points to 
   *  this class is derived by Iterator	
   */
  class ConstIterator;
  
  /** Like find but returns a ConstIterator*/
  ConstIterator cfind(TK);
  
  /** ConstIterator cbegin function, which returns the smallest key value */
  ConstIterator cbegin() const {
    if( root == nullptr )
      return ConstIterator{nullptr};
    BNode *pt = root.get();
    while( pt->left != nullptr )
      pt = pt->left.get();	
    return ConstIterator{pt};
  }
  /** ConstIterator cend function   */
  ConstIterator cend() const {	return ConstIterator{nullptr}; }
  
  
}; // BTree


// Iterator
template <class TK, class TV, class Tcomp>
  class BTree<TK,TV,Tcomp>::Iterator/*: public std::iterator<std::forward_iterator_tag, TK,TV,Tcomp> */ {

  using BNode = BTree<TK,TV,Tcomp>::BNode;
  BNode* current;

 public:
   
 Iterator(BNode* n) : current{n} {}
 
    /** Function to dereference an Iterator */
    std::pair<TK,TV>& operator*() const { return current->pair; }

    /** Function to move the iterator to the next node */
    Iterator& operator++() {
      if( current->right != nullptr ){
	BNode *p;
	p = current->right.get();
	while( p->left != nullptr )
	  p = p->left.get();
	current = p;
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

  
    /** Another function to move the iterator to the next node */
    Iterator operator++(int) {
      Iterator it{current};
      ++(*this);
      return it;
    }
  
    /** boolean operator to check equality of nodes*/
    bool operator==(const Iterator& other) {
      return this->current == other.current;
    }
    /** boolean operator to check if two nodes are different*/
    bool operator!=(const Iterator& other) { return !(*this == other); }
		
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

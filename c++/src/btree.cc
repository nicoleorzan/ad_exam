#include <btree.h>
#include <memory>
#include <iostream>
#include <iomanip> //indentation
#include <math.h>
#include <vector> 


// BNode::measure_depth()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::measure_depth(int& max, int& cur) {
	cur++;
	if( cur > max )
		max = cur;
	if( left != nullptr )
		left->measure_depth(max, cur);
	if( right != nullptr )
		right->measure_depth(max, cur);
		
	cur--;
}

// BTree::measure_depth()
template<class TK, class TV, class Tcomp>
int BTree<TK,TV,Tcomp>::measure_depth() {
	int current = 0, depth = 0;
	
	if( root == nullptr )
		return 0;

	root->measure_depth(depth, current);

	return depth;
}


// BTree::insert()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::insert( const std::pair<TK,TV> p ){ 
  if( root == nullptr){
    root.reset(new BNode{p, this->comparison});
  }
  else
    this->root->insert_node(p); 
}



// BNode::insert node()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::insert_node(const std::pair<TK,TV> p){
  // key is already present
  if (!comparison(this->pair.first, p.first) && !comparison(p.first,this->pair.first) ){
    this->pair.second = p.second;
    std::cout << "already present" << std::endl;
  }
  else if (comparison(p.first,this->pair.first) ){
    if( this->left == nullptr ){
      this->left.reset(new BNode{p, this, this->comparison});
      return;
    }
    else
      this->left->insert_node(p);
  }    
  else{
    if( this->right == nullptr ){
      this->right.reset(new BNode{p, this->next, this->comparison});
      return;
    }
    else
      this->right->insert_node(p);

  }
}


// BTree::print
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::print() const {
  using ConstIterator = BTree<TK,TV,Tcomp>::ConstIterator;
  ConstIterator it = this->cbegin(), end = this->cend();
  #ifdef DEBUG
  	if(it == end)
        	std::cout<<"BTree::print() : Tree is empty"<<"\n";
  #endif
  for( ; it != end; ++it )
  	std::cout << (*it).first << " " << (*it).second << std::endl; 
}


// BTree::clear()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::clear(){
  if (root==nullptr){
  	#ifdef DEBUG
        	std::cout<<"BTree::clear() : Tree is empty"<<"\n";
    	#endif
  	return;
  }
  root.reset();
}


// BTree::find(TK)
template <class TK, class TV, class Tcomp>
class BTree<TK,TV,Tcomp>::Iterator BTree<TK,TV,Tcomp>::find(const TK k){
    if( root == nullptr ) 
      return Iterator{nullptr};
    	
    BNode *pt = root.get();
    
    while ( comparison(pt->pair.first, k) || comparison(k, pt->pair.first) ){
      if( comparison( pt->pair.first, k ) ){
	if (pt->right != nullptr) {
	  pt = pt->right.get();
	}
	else{
	  return Iterator{nullptr};
	}
      }
      else {
	if (pt->left!= nullptr) {
	  pt = pt->left.get();
	}
	else{
	  return Iterator{nullptr};
	}
      }
    }
return Iterator{pt};  
}


// BTree::cfind(TK)   const
template <class TK, class TV, class Tcomp>
class BTree<TK,TV,Tcomp>::ConstIterator BTree<TK,TV,Tcomp>::cfind(const TK k) {
    if( root == nullptr ) 
      return ConstIterator{nullptr};
    	
    BNode *pt = root.get();
    
    while ( comparison(pt->pair.first, k) || comparison(k, pt->pair.first) ){
      if( comparison( pt->pair.first, k ) ){
	if (pt->right != nullptr) {
	  pt = pt->right.get();
	}
	else return ConstIterator{nullptr};
      }
      else {
	if (pt->left!= nullptr) {
	  pt = pt->left.get();
	}
	else return ConstIterator{nullptr};
      }
    }

return ConstIterator{pt};  
}


// ~BTree()
template<class TK, class TV, class Tcomp>
BTree<TK,TV,Tcomp>::~BTree(){
	#ifdef DEBUG
		std::cout << "~BTree()" << std::endl;
	#endif
  	this->clear();
}



//BALANCE FUNCTIONS
// BTree::balance()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::balance(){
#ifdef DEBUG
  std::cout << "BTree()::balance()" << std::endl;
#endif
  std::vector<std::pair<TK,TV>> vec;

  using Iterator = BTree<TK,TV,Tcomp>::Iterator;
  Iterator it = this->begin(), end = this->end();
  for( ; it != end; ++it ){
    vec.push_back(*it);
  }
  
  clear();
  
  int size = vec.size();

  built_tree(vec,0,size-1);
}



// BTree::built_tree()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::built_tree( std::vector<std::pair<TK,TV>> &vec, int start, int end){
  if (start>end) return;
  int half = (start+end)/2;
  
  std::pair<TK,TV> p = vec[half];
  
  insert(p);
  
  built_tree(vec, start, half-1);
  built_tree(vec, half+1, end);
}


// BTree::isbalanced()
template<class TK, class TV, class Tcomp>
bool BTree<TK,TV,Tcomp>::isbalanced() const{
  if (root!=nullptr){
	#ifdef DEBUG
	    std::cout << "isbalanced: root!= nullptr" << std::endl;
	#endif
    return (this->root->isbalanced_node());
  }
  else {
    std::cout<<"blanced tree"<<std::endl;
    return 0;
  }
}


// BNode::isbalanced_node()
template<class TK, class TV, class Tcomp>
int BTree<TK,TV,Tcomp>::BNode::isbalanced_node() const {

  if (this != nullptr){
    if (this->left != nullptr && this->right != nullptr){
      int diff = this->left->isbalanced_node() - this->right->isbalanced_node() ;
#ifdef DEBUG
      std::cout<<"diff "<<diff<<std::endl;
#endif
      return diff;
    }

    if ( (this->left==nullptr && this->right!=nullptr) || (this->left!=nullptr && this->right==nullptr)) {
#ifdef DEBUG
      std::cout<<"unblanced tree"<<std::endl;
#endif
      return 1;
    }
    else if (this->left==nullptr && this->right==nullptr) {
#ifdef DEBUG
      std::cout<<"blanced tree"<<std::endl;
#endif
      return 0;
    }
  }
#ifdef DEBUG
  std::cout<<"blanced tree"<<std::endl;
#endif
  return 0;
 
}

struct Notfound{};

struct Unknown_except{};


template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::erase(TK key){
  if (root!=nullptr){

    BNode *n = root.get();
    
    while ( (n->left.get() && comparison(key,n->pair.first)) || (n->right.get() && comparison(n->pair.first,key)) ){
      //comparions()n->pair.first>key
      //key is lower, I have to go left
      if (comparison(key,n->pair.first)){
	if ( n->left.get() ){
	  if(  !comparison( (n->left.get())->pair.first , key ) && !comparison( key,  (n->left.get())->pair.first ) ){
	    #ifdef DEBUG
	    std::cout<<"found, left child, returning "<<n->pair.first<<std::endl;
	    #endif
	    break;
	  }
	  else n=n->left.get();
	}
	else {
	  throw Notfound{};
	}
      }
	
      //key is bigger, I have to go right
    else if (comparison(n->pair.first,key)){
	if( n->right.get() ){
	  if (  !comparison( (n->right.get())->pair.first , key ) && !comparison( key,  (n->right.get())->pair.first )   ){
	    #ifdef DEBUG
	    std::cout<<"found, right child, returning "<<n->pair.first<<std::endl;
	    #endif
	    break;
	  }
	  else n=n->right.get();
	}
	else {
	  throw Notfound{};
	}
      }
    }
    
    //key into left child
    if ( n->left.get() &&  (!comparison( (n->left.get())->pair.first , key ) && !comparison( key,  (n->left.get())->pair.first )) ){
      std::unique_ptr<BNode> left_child{(n->left.get())->left.release()};
      std::unique_ptr<BNode> right_child{(n->left.get())->right.release()};
      n->left.reset();
      insert_subtree(left_child);
      insert_subtree(right_child);
    }
    
    //key into right child
    else if ( n->right.get() && (  !comparison( (n->right.get())->pair.first , key ) && !comparison( key,  (n->right.get())->pair.first )  ) ){
      std::unique_ptr<BNode> left_child{(n->right.get())->left.release()};
      std::unique_ptr<BNode> right_child{(n->right.get())->right.release()};
      n->right.reset();
      insert_subtree(left_child);
      insert_subtree(right_child);
    }
    //key is in root node
    else if ( !comparison(n->pair.first,key) && !comparison(key,n->pair.first) ) {
      #ifdef DEBUG
      std::cout<<"is root node"<<std::endl;
      #endif
      std::unique_ptr<BNode> left_child{(n)->left.release()};
      std::unique_ptr<BNode> right_child{(n)->right.release()};
      root.reset();
      insert_subtree(left_child);
      insert_subtree(right_child);
    }
    else {
      throw Unknown_except{};
    }
  }
} //erase

template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::insert_subtree(std::unique_ptr<BNode>& n){
  if (this!= nullptr && n!= nullptr){
    //std::pair<TK,TV> p{};
    if (n->left) insert_subtree(n->left);
    insert(n->pair);
    if (n->right) insert_subtree(n->right);
    }
}


//
// explicit templates
//


template class BTree<int,int, bool(*)(const int&, const int&)>;
template class BTree<int,int, std::less<int>>;
template class BTree<int,double, std::less<int>>;
template class BTree<std::string, std::string, std::less<std::string>>;
template class BTree<std::string, int, std::less<std::string>>;
template class BTree<char, double, std::less<char>>;

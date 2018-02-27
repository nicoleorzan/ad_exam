#include <btree.h>
#include <memory>
#include <iostream>
#include <iomanip> //indentation
#include <math.h>
#include <vector> 


// BNode::measure_depth()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::measure_depth(int& max, int& cur){
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
int BTree<TK,TV,Tcomp>::measure_depth(){
	int current = 0, depth = 0;
	
	if( root == nullptr )
		return 0;

	root->measure_depth(depth, current);

	return depth;
}


// BTree::insert()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::insert( std::pair<TK,TV> p ){ 
  if( root == nullptr){
    root.reset(new BNode{p});
  }
  else
    this->root->insert_node(p); 
}



// BNode::insert node()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::insert_node(std::pair<TK,TV> p){
  // key is already present
  if (!comparison(this->pair.first, p.first) && !comparison(p.first,this->pair.first) ){
    this->pair.second = p.second;
    std::cout << "already present" << std::endl;
  }
  else if (comparison(p.first,this->pair.first) ){
    if( this->left == nullptr ){
      this->left.reset(new BNode{p, this});
      return;
    }
    else
      this->left->insert_node(p);
  }    
  else{
    if( this->right == nullptr ){
      this->right.reset(new BNode{p, this->next});
      return;
    }
    else
      this->right->insert_node(p);

  }
}


// BTree::print
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::print() {
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
  //root->clear_node();
  //root.reset(nullptr);
  root.reset();
}


// BNode::clear_node()
/*template <class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::clear_node(){

	if( this->left != nullptr ){
		this->left->clear_node();
		}
	if( this->right != nullptr ){
		this->right->clear_node();
		}
	
	this->left.reset(nullptr);
	this->right.reset(nullptr);
	}*/


// BTree::find(TK)
template <class TK, class TV, class Tcomp>
class BTree<TK,TV,Tcomp>::Iterator BTree<TK,TV,Tcomp>::find(TK k){
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
#ifdef DEBUG
	  std::cout << "key not found" << std::endl;
#endif
	}
      }
      else {
	if (pt->left!= nullptr) {
	  pt = pt->left.get();
	}
	else{
	  return Iterator{nullptr};
#ifdef DEBUG
	  std::cout << "key not found" << std::endl;
#endif
	}
      }
    }
#ifdef DEBUG
    std::cout << "key found" << std::endl;
#endif
return Iterator{pt};  
}


// BTree::cfind(TK)   const
template <class TK, class TV, class Tcomp>
class BTree<TK,TV,Tcomp>::ConstIterator BTree<TK,TV,Tcomp>::cfind(TK k){
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
bool BTree<TK,TV,Tcomp>::isbalanced(){
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
int BTree<TK,TV,Tcomp>::BNode::isbalanced_node(){

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


// BTree::erase()
template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::erase(TK key){
  if (root!=nullptr)
     this->root->find_node(key);
}


template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::find_node(TK key){
  if (this!=nullptr){
    // if (this->left->pair.first==key) this->erase_node(0);
    //else if (this->right->pair.first==key) this->erase_node(1);
    if ( !comparison(this->pair.first, key) && !comparison(key,this->pair.first)  )  this->erase_node();
    //else if (this->pair.first>key) this->left->find_node(key);
    //else this->right->find_node(key);
    else if (comparison(key,this->pair.first) ) this->left->find_node(key);
    else this->right->find_node(key);
  }
  return;
}

template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::erase_node(){

  /* if (b==0){
    if (this->left->left==nullptr && this->left->right==nullptr) this->left.reset(nullptr);
    if (this->left->left!=nullptr) this->left.reset(this->left->left);
    if (this->left->right!=nullptr) this->right.reset(this->left->right);
  }
  else if (b==1){
    if (this->right->left==nullptr && this->right->right==nullptr) this->right.reset(nullptr);
    if (this->right->left!=nullptr) this->left.reset(this->right->left);
    if (this->right->right!=nullptr) this->right.reset(this->right->right);
    }*/
    //this->left.reset(nullptr);
  
    //node has no childs
   if (this->left==nullptr && this->right == nullptr){
    std::cout<<"no childs"<<std::endl;
    //if(this->next!=nullptr)
    //std::cout<<"printing next "<<this->next->pair.first<<" "<<this->next->pair.second<<std::endl;
    }
   
   //node has only left child
   if (this->left!= nullptr && this->right==nullptr){
     this->pair.first=this->left->pair.first;
     this->pair.second=this->left->pair.second;
      if (this->left->left==nullptr && this->left->right==nullptr) this->left.reset(nullptr);
      else this->left->erase_node();
    }
    //node has only right child
    if (this->left== nullptr && this->right!=nullptr){
      this->pair.first=this->right->pair.first;
      this->pair.second=this->right->pair.second;
      this->right->erase_node();
      if (this->right->left==nullptr && this->right->right==nullptr) this->right.reset(nullptr);
      else this->right->erase_node();
    }
    //node has both childs
    if (this->left!= nullptr && this->right!=nullptr){
      this->pair.first=this->right->pair.first;
      this->pair.second=this->right->pair.second;
      //std::cout<<"here "<<this->pair.first<<" "<<this->pair.second<<std::endl;
      if (this->right->left==nullptr && this->right->right==nullptr) this->right.reset(nullptr);
      else this->right->erase_node();
      // this->right->erase_node();
      }

  return;

}


template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::diagram(){
  if (root!=nullptr)
    this->root->diagram(6);  
}

template<class TK, class TV, class Tcomp>
void BTree<TK,TV,Tcomp>::BNode::diagram(int indent){
  if(this != nullptr) {
    if (indent) {
      std::cout << std::setw(indent) << ' ';
      std::cout<< this->pair.first<<std::endl;
    }
    if (this->left) {
      this->left->diagram(indent - 2);
    }
    if (this->right) {
      this->right->diagram(indent + 2);
    }
  }
}





//
// explicit templates
//

template class BTree<int,int, std::less<int>>;
template class BTree<int,double, std::less<int>>;
template class BTree<std::string, std::string, std::less<std::string>>;
template class BTree<std::string, int, std::less<std::string>>;
template class BTree<char, double, std::less<char>>;

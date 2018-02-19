#include <btree.h>
#include <memory>
#include <iostream>
// #include <iterator>
#include <iomanip>
#include <math.h>
#include <vector> 


template<typename TK, typename TV>
void BTree<TK,TV>::insert( std::pair<TK,TV> p ){ 
  if( root == nullptr)
  	root.reset(new BNode{p});
  else
  	this->root->insert_node(p); 
}

// insert node
template<typename TK, typename TV>
void BTree<TK,TV>::BNode::insert_node(std::pair<TK,TV> p){
  // BNode *tmproot = this->root_node.get();

  // key is already present
  if( this->pair.first == p.first ){
    this->pair.second = p.second;
    std::cout << "already present" << std::endl;
    }
  else if( this->pair.first > p.first ){
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
template<typename TK, typename TV>
void BTree<TK,TV>::print() {
  using Iterator = BTree<TK,TV>::Iterator;
  Iterator it = this->begin(), end = this->end();
  // std::cout << "print" << std::endl;
  for( ; it != end; ++it )
  	std::cout << (*it).first << " " << (*it).second << std::endl; 
}




/*
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
  root.reset(nullptr);
}


*/


// BTree::clear()
template<typename TK, typename TV>
void BTree<TK,TV>::clear(){
  if (root==nullptr){
  	#ifdef DEBUG
        std::cout<<"BTree::clear() : Tree is empty"<<"\n";
    	#endif
  	return;
  }
  root->clear_node();
  root.reset(nullptr);
}


// BNode::clear_node()
template <typename TK, typename TV>
void BTree<TK,TV>::BNode::clear_node(){

	if( this->left != nullptr ){
		this->left->clear_node();
		}
	if( this->right != nullptr ){
		this->right->clear_node();
		}
	
	this->left.reset(nullptr);
	this->right.reset(nullptr);
}


/*
template<typename TK, typename TV>
void BTree<TK,TV>::clear(BNode *n){
  if(n != nullptr){
    clear(n->left);
    clear(n->right);  
    delete n;
    n = nullptr;
  }
}*/

// ~BTree()
template<typename TK, typename TV>
BTree<TK,TV>::~BTree(){
	#ifdef DEBUG
	std::cout << "~BTree()" << std::endl;
	#endif
  	this->clear();
}




// explicit template
template class BTree<int,int>;


/*
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
    // if (p->left && p->right){
    //  diagram(p->left, indent - 2);
    //  diagram(p->right, indent + 2);
    //  }
    if (p->left) {
      diagram(p->left, indent - 2);
    }
    if (p->right) {
      diagram(p->right, indent + 2);
    }
  }
}


template<typename TK, typename TV>
class BTree<TK,TV>::Iterator BTree<TK,TV>::find(TK k){
Iterator it = this->begin();

while( *it.first < k )
	++it;

if(*it.first == k )
	return it;
else
	return Iterator{nullptr};


// std::cout << "inside" << std::endl;
BNode *p = root;
if( p == nullptr )
	return Iterator{nullptr};
while(1){
	
	if(p->pair.first == k)
		return Iterator{p};
	if(p->pair.first > k){
		if( p->left != nullptr){
			p = p->left;
			std::cout << "left" << std::endl;
		}
		else
			return Iterator{nullptr};
	}
	else{
		if( p->right != nullptr){
			p = p->right;
			std::cout << "right" << std::endl;
		}
		else
			return Iterator{nullptr};
	
	}
}
}
*/

// BNode copy const
/*
template<typename TK, typename TV>
BTree<TK,TV>::BNode(const BNode& b): pair{b.pair}, left{nullptr}, right{nullptr}, father{nullptr} {
	std::cout << "BNode copy ctor\n" << std::endl;
}

// copy const
template<typename TK, typename TV>
BTree<TK,TV>::BTree(const BTree& t){
	std::cout << "BTree copy ctor" << std::endl;
	root = new BNode{*(t.root)};

}


// copy assignment
template<typename TK, typename TV>
BTree<TK,TV>& BTree<TK,TV>::operator=(const BTree& t){
	std::cout << "BTree copy assignment" << std::endl;

}
*/









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



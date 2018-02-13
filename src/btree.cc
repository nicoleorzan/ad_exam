#include <btree.h>
#include <memory>
#include <iostream>

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
//  

#include <iostream>
#include <memory>
#include <vector>

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
		
		// void print_node();
		
		
	}; // BNode


	// root node
	BNode* root;

	public:
		
		// constructor for pair
		BTree(std::pair<TK,TV> p): root{new BNode{p} } {}
		// constructor for 2 elements separated
		// BTree(TK key, TV val): root{new BNode{key,val}} {}
		
		void insert( std::pair<TK,TV> p );
		
		class Iterator;
		
		Iterator begin(){
			BNode *pt = root;
			while( pt->left != nullptr )
				pt = pt->left.get();	
			return Iterator{pt};
		}
		
		Iterator end(){	return Iterator{nullptr}; }
}; // BTree


// Iterator
template <typename TK, typename TV>
class BTree<TK,TV>::Iterator {
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


#endif // __BTREE__

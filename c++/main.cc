#include <btree.h>
#include <iostream>
#include <memory>
// #include "src/btree.cc"
#include <cstdlib>   // rand()
#include <vector>


void random_fill(BTree<int,int>& t, int size){
int r, i;
std::pair<int,int> p;
	
	for(i=0; i<size; i++){
		r = rand() % (size*100);
		p = {r, r};
		t.insert(p); 
	}

}




void constructor_test(){

	std::cout << "####################################################" << std::endl;
	std::cout << "\nCONSTRUCTOR TEST:" << std::endl;
	std::cout << "test the constructors, destructor, insert, print and clear\n" << std::endl;
	std::cout << "####################################################" << std::endl;
	
	
	
	std::pair<int,int> p{1,1};
	unsigned int j;

/*	
{
        
	BTree<int,int> t1;
	std::cout << "BTree<int,int> t1;" << std::endl;
	std::cout << "t1.print();" << std::endl;
	t1.print();
	
  	
  	std::cout << "t1.insert(p);" << std::endl;
  	t1.insert(p);
  	std::cout << "t1.print()" << std::endl;
  	t1.print();
  	
  	std::cout << "t1.clear()" << std::endl;
  	t1.clear();
  	std::cout << "t1.print()" << std::endl;
  	t1.print();
}
*/	
  	
{
  	p = {1,1};
  	std::cout << "BTree<int,int> t2{p};" << std::endl;
  	BTree<int,int> t2{p};
  	std::cout << "t2.print()" << std::endl;
  	t2.print();
  	p = {2,2};
  	std::cout << "t2.insert(p);" << std::endl;
  	t2.insert(p);
  	std::cout << "t2.print()" << std::endl;
  	t2.print();
  	std::cout << "t2.clear()" << std::endl;
  	t2.clear();
  	std::cout << "t2.print()" << std::endl;
  	t2.print();
  	
  	std::vector<int> v{4,2,6,1,3,5,7};
  	for(j=0; j< v.size(); j++){
		p = {v[j], v[j]};
		t2.insert(p);
	}
	std::cout << "inserted v={4,2,6,1,3,5,7}" << std::endl;
	std::cout << "t2.print()" << std::endl;
  	t2.print();
  	std::cout << "t2.clear()" << std::endl;
  	t2.clear();
  	std::cout << "t2.print()" << std::endl;
  	t2.print();	
}
	
} // constructor_test





/*

void find_test(){
std::vector<std::pair<int,int>> v;
std::pair<int,int> p;
int i, r; //  n;
unsigned int j;


for( i=0; i<10; i++){
	r = rand() % 1000;
	// std::cout << r << std::endl;
	p = {r,r};
	for( j=0; j<v.size(); j++){
		if( p == v[j] )
			break;
	}
	if( j == v.size() )
		v.push_back(p);
}

std::cout << "v has size " << v.size() << std::endl;
for( j=0; j<v.size(); j++)
	std::cout << v[j].first << std::endl;

BTree<int,int> t;
for( j=0; j<v.size(); j++)
	t.insert(v[j]);
	
std::cout << "t" << std::endl;
t.print();

int count = 0;
BTree<int,int>::Iterator it = t.begin(), end = t.end();
for( ; it != end; ++it )
	count++;

std::cout << "v.size(): " << v.size() << " size of tree: " << count << std::endl;

for( j=0; j<v.size() - 1; j++){
	std::cout << "looking for " << v[j].first << std::endl;
	it = t.find( v[j].first );
	if( it != end )
		std::cout << "(*it).first: " << (*it).first;
	if( ++it != end ){
		// std::cout << "test ok" << std::endl;
		std::cout << " (*++it).first: " << (*it).first;
		}
	else
		std::cout << " last element ";
	std::cout << std::endl;
}



}// find_test

*/




void copymove_test(){

	std::cout << "####################################################" << std::endl;
	std::cout << "\nCOPY MOVE TEST:\n" << std::endl;
	// std::cout << "test " << std::endl;
	std::cout << "####################################################" << std::endl;
	std::pair<int,int> p;
	BTree<int,int> t1;
	p = {2,2};
	t1.insert(p);
	p = {1,1};
	t1.insert(p);
	p = {3,3};
	t1.insert(p);
	std::cout << "t1" << std::endl;
	t1.print();
	
	std::cout << "\n\nCOPY CONSTRUCTOR\n" << std::endl;
	std::cout << "BTree<int,int> t2 = t1;" << std::endl;
	BTree<int,int> t2 = t1;
	std::cout << "t2.print()" << std::endl;
	t2.print();
	
	std::cout << "\n\nCOPY ASSIGNMENT\n" << std::endl;
	std::cout << "BTree<int,int> t3;" << std::endl;
	BTree<int,int> t3;
	t3 = t1;
	std::cout << "t3.print()" << std::endl;
	t3.print();
	
	
	std::cout << "\n\nMOVE ASSIGNMENT\n" << std::endl;
	std::pair<int,int> p1{13,13};
	std::cout << "t2 = BTree<int,int>{p1};" << std::endl;
	t2 = BTree<int,int>{p1}; 
	std::cout << "t2.print()" << std::endl;
	t2.print();
	
	std::cout << "\n\nMOVE CONSTRUCTOR\n" << std::endl;
	std::cout << "BTree<int,int> t4{std::move(t1)};" << std::endl;
	BTree<int,int> t4{std::move(t1)};
	std::cout << "t4.print();" << std::endl;
	t4.print();
	
}






int main(){
  
  constructor_test();
  
  //copymove_test();
  
  //find_test();
   
  return 0;
}

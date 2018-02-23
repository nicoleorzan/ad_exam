#include <btree.h>
#include <iostream>
#include <memory>
// #include "src/btree.cc"
#include <cstdlib>   // rand()
#include <vector>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

double cclock(){

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}


void random_fill(BTree<int,int,std::less<int>>& t, int size){
int r, i;
unsigned int j;
std::pair<int,int> p;
std::vector<std::pair<int,int>> v;
	
  t.clear();

  for(i=0; i<size; i++){
    r = rand() % (size*100);
    p = {r, r};
    for( j=0; j<v.size(); j++){
	if( p == v[j] )
		break;
    }
	if( j == v.size() )
		v.push_back(p);
   }


std::cout << "v has size " << v.size() << std::endl;
for( j=0; j<v.size(); j++)
	t.insert( v[j] );
	
std::cout << "t" << std::endl;
t.print();

} // random_fill


void balance_test(){
  
 std::cout << "####################################################" << std::endl;
  std::cout << "\nBALANCE TREE TESTING:" << std::endl;
  std::cout << "####################################################" << std::endl;

   std::pair<int,int> p{1,1};
  std::cout << "BTree<int,int> t{p};" << std::endl;
  BTree<int,int,std::less<int>> t{p};
  std::cout << "t.print()" << std::endl;
  t.print();

  std::vector<int> v{87,7,6,5,11,25,4,3,2,1,15,2,18,33,17};
    for(unsigned int j=0; j< v.size(); j++){
      p = {v[j], v[j]};
      t.insert(p);
    }
    std::cout << "inserted  v{87,7,6,5,11,25,4,3,2,1,15,2,18,33,17}" << std::endl;
    std::cout << "t.print()" << std::endl;
    t.print();
    std::cout << "t.find(87)" << std::endl;
    t.find(87);
    std::cout << "t.isbalanced()" << std::endl;
    t.isbalanced();
    t.diagram();
    std::cout << "t.balance()" << std::endl;
    t.balance();
    std::cout << "t.isbalanced()" << std::endl;
    t.isbalanced();
    std::cout << "t.find(87)" << std::endl;
    t.find(87);
    std::cout << "t.diagram()" << std::endl;
    t.diagram();
    std::cout << "t.clear()" << std::endl;
    t.clear();

    std::vector<int> v1{2,17,11,25,4,33,3,2,1,15,87,7,6,5,18};
    for(unsigned int j=0; j< v1.size(); j++){
      p = {v1[j], v1[j]};
      t.insert(p);
    }
    std::cout << "inserted v1{33,17,11,25,4,3,2,1,15,87,7,6,5,2,18}" << std::endl;

    std::cout << "t.print()" << std::endl;
    t.print();
    std::cout << "t.find(7)" << std::endl;
    t.find(7);
    std::cout << "t.isbalanced()" << std::endl;
    t.isbalanced();
    t.diagram();
    std::cout << "t.balance()" << std::endl;
    t.balance();
    std::cout << "t.isbalanced()" << std::endl;
    t.isbalanced();
    std::cout << "t.find(7)" << std::endl;
    t.find(7);
    std::cout << "t.diagram()" << std::endl;
    t.diagram();
    std::cout << "t.clear()" << std::endl;
  
  BTree<int,int,std::less<int>>::Iterator it = t.begin(), end = t.end();
    std::cout << "t.find(100)" << std::endl;
    it = t.find(100);
    if( it == end )
    	std::cout << "it == end" << std::endl;
    
    std::cout << "t.diagram()" << std::endl;
    t.diagram();
	t.clear();
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
    BTree<int,int,std::less<int>> t2{p};
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
  	
    std::vector<int> v{7,6,5,4,3,2,1};// v{4,2,6,1,3,5,7};
    for(j=0; j< v.size(); j++){
      p = {v[j], v[j]};
      t2.insert(p);
    }
    std::cout << "inserted v={7,6,5,4,3,2,1}" << std::endl;
    std::cout << "t2.print()" << std::endl;
    t2.print();
    std::cout << "t2.isbalanced()" << std::endl;
    t2.isbalanced();
    /* std::cout << "t2.clear()" << std::endl;
       t2.clear();
       std::cout << "t2.print()" << std::endl;
       t2.print();	*/
    t2.diagram();
    std::cout << "t2.balance()" << std::endl;
    t2.balance();
    std::cout << "t2.isbalanced()" << std::endl;
    t2.isbalanced();
    std::cout << "t2.diagram()" << std::endl;
    t2.diagram();
    //std::cout << "t2.erase(7)" << std::endl;
    //t2.erase(7);
    std::cout << "t2.diagram()" << std::endl;
    t2.diagram();
    std::cout << "t2.clear()" << std::endl;
    t2.clear();
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
	BTree<int,int,std::less<int>> t1;
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
	BTree<int,int,std::less<int>> t2 = t1;
	std::cout << "t2.print()" << std::endl;
	t2.print();
	
	std::cout << "\n\nCOPY ASSIGNMENT\n" << std::endl;
	std::cout << "BTree<int,int> t3;" << std::endl;
	BTree<int,int,std::less<int>> t3;
	t3 = t1;
	std::cout << "t3.print()" << std::endl;
	t3.print();
	
	
	std::cout << "\n\nMOVE ASSIGNMENT\n" << std::endl;
	std::pair<int,int> p1{13,13};
	std::cout << "t2 = BTree<int,int>{p1};" << std::endl;
	t2 = BTree<int,int,std::less<int>>{p1}; 
	std::cout << "t2.print()" << std::endl;
	t2.print();
	
	std::cout << "\n\nMOVE CONSTRUCTOR\n" << std::endl;
	std::cout << "BTree<int,int> t4{std::move(t1)};" << std::endl;
	BTree<int,int,std::less<int>> t4{std::move(t1)};
	std::cout << "t4.print();" << std::endl;
	t4.print();
	
}






int main(){
  
  double t_start, t_end;
  
  t_start=cclock();
  
  //constructor_test();

  balance_test();
  
  //copymove_test();
  
  //find_test();

  t_end = cclock();
  std::cout<<"time: "<<t_end - t_start<<std::endl;
  
  std::pair<int,int> p{2,2};
  BTree<int,int,std::less<int>> t1{p};
  t1.print();
  
  random_fill(t1, 15);
   
  return 0;
}

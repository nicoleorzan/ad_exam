/*
*   Contains some small tests on the main features of class BTree
*   
*/


#include <btree.h>
#include <iostream>
#include <cstdlib>   // rand()
#include <vector>
#include <string>


/*
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
*/



void constructor_test(){

  std::cout << "####################################################" << std::endl;
  std::cout << "\nCONSTRUCTOR TEST:" << std::endl;
  std::cout << "test the constructors, destructor, insert, print and clear\n" << std::endl;
  std::cout << "####################################################" << std::endl;
	
	
	

  unsigned int j;

  	
  {
    std::cout << "\n\nTEST WITH INT\n" << std::endl;
    std::pair<int,int> p{1,1};
    std::cout << "BTree<int,int,std::less<int>> t1; calls:" << std::endl;    
    BTree<int,int,std::less<int>> t1;
    
    std::cout << "\nt1.print();" << std::endl;
    t1.print();
	
  	
    std::cout << "t1.insert(p = {1,1});" << std::endl;
    t1.insert(p);
    std::cout << "\nt1.print()" << std::endl;
    t1.print();
  	
    std::cout << "\nt1.clear()" << std::endl;
    t1.clear();
    std::cout << "\nt1.print()" << std::endl;
    t1.print();
    std::cout << "\nnow calling the destructor:" << std::endl;
  }
	
  
  {
    std::cout << "\n" << std::endl;
    std::pair<int,int> p{1,1};
    std::cout << "BTree<int,int,std::less<int>> t2{p}; calls:" << std::endl;
    BTree<int,int,std::less<int>> t2{p};
    std::cout << "\nt2.print()" << std::endl;
    t2.print();
    p = {2,2};
    std::cout << "\nt2.insert(p);" << std::endl;
    t2.insert(p);
    std::cout << "\nt2.print()" << std::endl;
    t2.print();
    std::cout << "\nt2.clear()" << std::endl;
    t2.clear();
    std::cout << "\nt2.print()" << std::endl;
    t2.print();
  	
    std::vector<int> v{4,2,6,1,3,5,7};
    for(j=0; j< v.size(); j++){
      p = {v[j], v[j]};
      t2.insert(p);
    }
    std::cout << "\ninserted v={4,2,6,1,3,5,7} in t2" << std::endl;
    std::cout << "\nt2.print()" << std::endl;
    t2.print();

    std::cout << "\nt2.clear()" << std::endl;
    t2.clear();
    std::cout << "\nt2.print()" << std::endl;
    t2.print();
    std::cout << "\nnow calling the destructor:" << std::endl;
  }
  
  
  {
    std::cout << "\n\nTEST WITH CHARS\n" << std::endl;
    unsigned int i;
    std::vector<char> c{'c','a','e','b','f','k','p','j','y','n','d','i','m','n','l','s','g','o','q','h','r','t','z','u','x','w','v'};
    std::cout << "BTree<char, double, std::less<char>> t;\n" << std::endl;
    BTree<char, double, std::less<char>> t;
    std::pair<char,double> p;
    std::cout << "inserting the alphabet in this order\n" << std::endl;
    for(i=0; i<c.size(); i++){
    	std::cout << c[i] << " ";
    	p = {c[i], 3.14};
    	t.insert(p);
    }
    std::cout << "\n\nt.print()" << std::endl;
    t.print();
    
  } // test char
  
  {
    std::cout << "\n\nTEST WITH STRINGS\n" << std::endl;
    std::cout << "inserting:" << std::endl;
    std::cout << "{this,is,the,string,test,for,the,class,btree,for,the,advanced, programming, exam}" << std::endl;
    std::vector<std::string> v{"this","is","the","string","test","for","the","class","btree","for","the",\
    				"advanced", "programming", "exam"};
    BTree<std::string, std::string, std::less<std::string>> t;
    std::pair<std::string,std::string> p;
    unsigned int i;
    for(i=0; i<v.size(); i++){
    	p = {v[i], " "};
    	t.insert(p);
    }
    std::cout << "\nt.print()" << std::endl;
    t.print();
  
  } // test string
  
  std::cout << "\n\n\nend of constructor test" << std::endl;
  std::cout << "####################################################" << std::endl;
	
} // constructor_test


void copymove_test(){

	std::cout << "####################################################" << std::endl;
	std::cout << "\nCOPY MOVE TEST:\n" << std::endl;
	std::cout << "test copy and move constructor and assignment" << std::endl;
	std::cout << "####################################################" << std::endl;
	std::pair<int,int> p;
	unsigned int j;

{

	BTree<int,int,std::less<int>> t1;
    	std::vector<int> v{4,2,6,1,3,5,7};
    	for(j=0; j< v.size(); j++){
      		p = {v[j], v[j]};
      		t1.insert(p);
    	}
    	std::cout << "\ninserted v={4,2,6,1,3,5,7} in t1" << std::endl;
	std::cout << "t1.print()" << std::endl;
	t1.print();
	
	std::cout << "\n\nCOPY CONSTRUCTOR\n" << std::endl;
	std::cout << "BTree<int,int,std::less<int>> t2 = t1; calls" << std::endl;
	BTree<int,int,std::less<int>> t2 = t1;
	std::cout << "t2.print()" << std::endl;
	t2.print();
	std::cout << "t1.clear();" << std::endl; 
	t1.clear();
	std::cout << "\nt1.print();" << std::endl; 
	t1.print();
	std::cout << "\nt2.print();" << std::endl; 
	t2.print();
	
	std::cout << "\n\nCOPY ASSIGNMENT\n" << std::endl;
	std::cout << "BTree<int,int,std::less<int>> t3;" << std::endl;
	BTree<int,int,std::less<int>> t3;
    	for(j=0; j< v.size(); j++){
      		p = {v[j], v[j]};
      		t1.insert(p);
    	}
	std::cout << "t3 = t1 calls;" << std::endl;
	t3 = t1;
	std::cout << "\nt3.print()" << std::endl;
	t3.print();
	std::cout << "\nt1.clear();" << std::endl; 
	t1.clear();
	std::cout << "t1.print();" << std::endl; 
	t1.print();
	std::cout << "\nt3.print();" << std::endl; 
	t3.print();
}
{	
	std::cout << "\n\nMOVE ASSIGNMENT\n" << std::endl;
	std::cout << "std::pair<int,int> p1{13,13};" << std::endl;
	std::pair<int,int> p1{13,13};
	BTree<int,int,std::less<int>> t2;
	std::cout << "BTree<int,int,std::less<int>> t2 = BTree<int,int>{p1}; calls" << std::endl;
	t2 = BTree<int,int,std::less<int>>{p1}; 
	std::cout << "\nt2.print()" << std::endl;
	t2.print();
}	
	std::cout << "\n\nMOVE CONSTRUCTOR\n" << std::endl;
	BTree<int,int,std::less<int>> t1;
    	std::vector<int> v{4,2,6,1,3,5,7};
    	for(j=0; j< v.size(); j++){
      		p = {v[j], v[j]};
      		t1.insert(p);
    	}
    	std::cout << "\ninserted v={4,2,6,1,3,5,7} in t1" << std::endl;
	std::cout << "t1.print()" << std::endl;
	t1.print();
	std::cout << "\nBTree<int,int,std::less<int>> t4{std::move(t1)}; calls" << std::endl;
	BTree<int,int,std::less<int>> t4{std::move(t1)};
	std::cout << "t4.print();" << std::endl;
	t4.print();
	std::cout << "\nt1.clear();" << std::endl; 
	t1.clear();
	std::cout << "t1.print();" << std::endl; 
	t1.print();
	std::cout << "t4.print();" << std::endl;
	t4.print();
	
} // copymove_test



/*
void balance_test(){
  
 std::cout << "####################################################" << std::endl;
  std::cout << "\nBALANCE TREE TESTING:" << std::endl;
  std::cout << "####################################################" << std::endl;

   std::pair<int,int> p{1,1};
  std::cout << "BTree<int,int> t{p};" << std::endl;
  BTree<int,int,std::less<int>> t;//{p};
  std::cout << "t.print()" << std::endl;
  t.print();

  std::vector<int> v{20,10,30,5,15,25,35,3,8,12,17,22,27,32,39,1,4};
    for(unsigned int j=0; j< v.size(); j++){
      p = {v[j], v[j]};
      t.insert(p);
    }
    std::cout << "inserted  v{20,10,30,5,15,25,35,3,8,12,17,22,27,32,39,1,4}" << std::endl;
    // std::cout << "t.print()" << std::endl;
    //t.print();
    std::cout << "t.diagram()" << std::endl;
    t.diagram();
    std::cout << "t.erase(25)" << std::endl;
    t.erase(25);
    std::cout << "t.diagram()" << std::endl;
    t.diagram();
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
    std::cout << "t.erase(7)" << std::endl;
    t.erase(7);
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
*/







void find_test(){

	std::cout << "####################################################" << std::endl;
	std::cout << "\nFIND TEST:\n" << std::endl;
	std::cout << "test the find function and other features of Iterator" << std::endl;
	std::cout << "####################################################" << std::endl;

std::pair<int,int> p;
unsigned int j;

BTree<int,int,std::less<int>> t1;
std::vector<int> v{4,2,6,1,3,5,7};
for(j=0; j< v.size(); j++){
	p = {v[j], v[j]};
	t1.insert(p);
}
std::cout << "\ninserted v={4,2,6,1,3,5,7} in t1" << std::endl;
t1.print();

BTree<int,int,std::less<int>>::Iterator it = t1.begin(), end = t1.end();

for( j=0; j<v.size(); j++){
	std::cout << "looking for " << v[j] << std::endl;
	it = t1.find( v[j] );
	if( it != end )
		std::cout << "(*it).first: " << (*it).first << std::endl;
}


std::cout << "now looking for an element not present in the tree: 110" << std::endl;
it = t1.find( 110 );

if( it == end )
	std::cout << "110 not found " << std::endl;

else
	std::cout << "110 found " << std::endl;
	

std::cout << "now using the iterator to modify the second element of the pair" << std::endl;
std::cout << "it = t1.find( 3 );" << std::endl;
it = t1.find( 3 );
std::cout << "(*it).second = 45646;" << std::endl;
(*it).second = 45646;
std::cout << "t1.print();" << std::endl;
t1.print();





std::cout << "\nTEST CONSTITERATOR\n" << std::endl; 
BTree<int,int,std::less<int>>::ConstIterator itc = t1.cbegin(), endc = t1.cend();

for( j=0; j<v.size(); j++){
	std::cout << "looking for " << v[j] << std::endl;
	itc = t1.cfind( v[j] );
	if( itc != end )
		std::cout << "(*itc).first: " << (*itc).first << std::endl;
}


std::cout << "now looking for an element not present in the tree: 110" << std::endl;
itc = t1.cfind( 110 );

if( itc == endc )
	std::cout << "110 not found " << std::endl;

else
	std::cout << "110 found " << std::endl;
	

std::cout << "the const iterator cannot modify the second element of the pair" << std::endl;
std::cout << "itc = t1.find( 3 );" << std::endl;
itc = t1.cfind( 3 );
std::cout << "(*itc).second = 45646; would produce an error" << std::endl;
// (*itc).second = 45646;


}// find_test












int main(){

  constructor_test();

  copymove_test();
  
  find_test();
  
  // balance_test();
   
  return 0;
}

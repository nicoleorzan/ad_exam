/*
*   Contains some small tests on the main features of class BTree
*   
*/


#include <btree.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>


// measure time
double cclock(){

  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
  return sec;
}


// generate a random string
std::string random_str(int length){
std::string pool = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
std::string res;
res.resize(length);

for( int i=0; i<length; i++)
	res[i] = pool[ rand() % pool.length() ];

return res;
}



// constructor test
void constructor_test(){

  std::cout << "\n\n####################################################" << std::endl;
  std::cout << "\nCONSTRUCTOR TEST:" << std::endl;
  std::cout << "test the constructors, destructor, insert, print and clear\n" << std::endl;
  std::cout << "####################################################" << std::endl;
	
	
	

  unsigned int j;

  	
  {
    std::cout << "\n\nTEST WITH INT\n" << std::endl;
    std::pair<int,int> p{1,1};
    std::cout << "BTree<int,int> t1; calls:" << std::endl;    
    BTree<int,int> t1;
    
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
    std::cout << "\nt2.insert(p={2,2});" << std::endl;
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
    std::vector<char> c{'c','a','e','b','f','k','p','j','y','n','d','i','m','l','s','g','o','q','h','r','t','z','u','x','w','v'};
    std::cout << "BTree<char, double, std::less<char>> t;\n" << std::endl;
    BTree<char, double, std::less<char>> t;
    std::pair<char,double> p;
    std::cout << "inserting the alphabet in this order\n" << std::endl;
    for(i=0; i<c.size(); i++){
    	std::cout << c[i] << " ";
    	p = {c[i], (double) i};
    	t.insert(p);
    }
    std::cout << "\n\nt.print()" << std::endl;
    t.print();
    
  } // test char
  
  {
    BTree<std::string, std::string, std::less<std::string>> t;
    std::cout << "\n\nTEST WITH STRINGS\n" << std::endl;
    std::cout << "inserting:" << std::endl;
    std::cout << "{this,is,the,string,test,for,the,class,btree,for,the,advanced, programming, exam}" << std::endl;
    std::vector<std::string> v{"this","is","the","string","test","for","the","class","btree","for","the",\
    				"advanced", "programming", "exam"};
    
    std::pair<std::string,std::string> p;
    unsigned int i;
    for(i=0; i<v.size(); i++){
    	p = {v[i], " "};
    	t.insert(p);
    }
    std::cout << "\nt.print()" << std::endl;
    t.print();
    std::cout << "\n" << std::endl;
  
  } // test string
	
} // constructor_test





// copy move test
void copymove_test(){

	std::cout << "\n\n####################################################" << std::endl;
	std::cout << "\nCOPY MOVE TEST:" << std::endl;
	std::cout << "test copy and move constructor and assignment\n" << std::endl;
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





// balance test
void balance_test(){
  
  std::cout << "\n\n####################################################" << std::endl;
  std::cout << "\nBALANCE TREE TESTING:\n" << std::endl;
  std::cout << "####################################################" << std::endl;



{
	std::pair<int,int> p;
	unsigned int j;
	int depth = 0;


	BTree<int,int,std::less<int>> t1;
    	std::vector<int> v{4,2,6,1,3,5,7};
    	for(j=0; j< v.size(); j++){
      		p = {v[j], v[j]};
      		t1.insert(p);
    	}
    	std::cout << "\ninserted v={4,2,6,1,3,5,7} in t1" << std::endl;
	std::cout << "t1.print()" << std::endl;
	t1.print();
	
	depth = t1.measure_depth();
	
	std::cout << "depth: " << depth << std::endl;

	t1.clear();
	t1.print();
	
	std::cout << "inserting numbers from 1 to 34 backwards..." << std::endl;

    	for(j=34; j > 0; j--){
      		p = {j, j};
      		t1.insert(p);
    	}
    	
	depth = t1.measure_depth();
	
	std::cout << "depth before balance: " << depth << std::endl;
	
	t1.balance();
    	depth = t1.measure_depth();
	
	std::cout << "depth after balance: " << depth << std::endl;
	
	std::cout << "2^(depth-1) = " << pow(2.0, depth-1) << std::endl;
	std::cout << "2^depth = " << pow(2.0, depth) << std::endl;
}

{	
	

	std::cout << "\n\nTEST ON RANDOM STRINGS " << std::endl;
	
	double start, end, max;
	BTree<std::string,int,std::less<std::string>> t;
    	std::vector<std::string> v;
    	std::pair<std::string, int> p;
    	unsigned int j, size;
    	int depth;

    	
    	
    	std::cout << "\n\ntest of find time in a tree with 10000 strings" << std::endl;
    	size = 10000;
	v.clear();
	t.clear();
    	std::string r;

    	while(v.size()<size){
    		r = random_str(15);
      		v.push_back(r);
  	}

	for( j=0; j<v.size(); j++){
		p = {v[j] , (int) j};
		t.insert( p );
	}

	depth = t.measure_depth();
	
	std::cout << "depth before balance: " << depth << std::endl;

	max = 0.0;

	for(j=0; j<v.size(); j++){
		start = cclock();
		t.find( v[j] );
		end = cclock();
		if( (end - start) > max )
			max = end - start;
	}

	std::cout << "max time before balance: " << max << std::endl;
	

	t.balance();
	depth = t.measure_depth();
	std::cout << "depth after balance: " << depth << std::endl;
	
	
	max = 0.0;

	for(j=0; j<v.size(); j++){
		start = cclock();
		t.find( v[j] );
		end = cclock();
		if( (end - start) > max )
			max = end - start;
	}

	std::cout << "max time after balance: " << max << std::endl;
	
} // test on random trees

} // balance_test







// find test
void find_test(){

	std::cout << "\n\n####################################################" << std::endl;
	std::cout << "\nFIND TEST:" << std::endl;
	std::cout << "test the find function and other features of Iterator\n" << std::endl;
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


void erase_test(){

  std::cout << "####################################################" << std::endl;
  std::cout << "\nERASE TEST:" << std::endl;
  std::cout << "####################################################" << std::endl;

  std::pair<int,int> p;
  unsigned int j;

  BTree<int,int,std::less<int>> t;
  std::vector<int> v{20,10,23,3,5,12,44,7,54,27,10,16};
  for(j=0; j< v.size(); j++){
    p = {v[j], v[j]};
    t.insert(p);
  }
  std::cout << "\ninserted v={20,10,23,3,5,12,44,7,54,27,10,16} in t1" << std::endl;
  std::cout<<"---PRINTING INITIAL TREE-- "<<std::endl;
  t.print();
  std::cout<<"--------- "<<std::endl;

  for(j=0; j< v.size(); j++){
    std::cout<<"--------- "<<std::endl;
    std::cout<<"balancing tree "<<std::endl;
    t.balance();
    std::cout<<"erasing "<<v[j]<<std::endl;
    t.erase(v[j]);
    std::cout<<"printing tree with erased "<<v[j]<<std::endl;
    t.print();
    std::cout<<"inserting again: "<<v[j]<<std::endl;
    p = {v[j], v[j]};
    t.insert(p);
    std::cout<<"printing recomposed tree, must be the original "<<std::endl;
    t.print();
    }
} //erase test






// test function
bool test_funct(const int& a, const int& b){
	return a > b;
}




void pass_function(){

	bool (*ptf)(const int&, const int&) = test_funct;
	std::cout << "BTree<int,int,bool(*)(const int&, const int&)> t{ptf};" << std::endl;
	std::cout << "The function returns a > b, so the tree should be printed backwards" << std::endl;
	BTree<int,int,bool(*)(const int&, const int&)> t{ptf};
	std::vector<int> v{2,1,3,4,5};
	std::pair<int,int> p;
	unsigned int i;
	std::cout << "inserting v = {2,1,3,4,5}" << std::endl;
	for(i=0; i<v.size(); i++){
		p = {v[i], v[i]};
		t.insert(p);
	}
	std::cout << "print" << std::endl;
	t.print();
	
	std::cout << "\ncopy constructor" << std::endl;
	std::cout << "BTree<int,int,bool(*)(const int&, const int&)> t1 = t;" << std::endl;
	BTree<int,int,bool(*)(const int&, const int&)> t1 = t;
	t.clear();
	std::cout << "print" << std::endl;
	t1.print();
	
	std::cout << "\ncopy assignment" << std::endl;
	std::cout << "t2 = t1;" << std::endl;
	BTree<int,int,bool(*)(const int&, const int&)> t2;
	t2 = t1;
	
	t1.clear();
	t2.print();

	std::cout << "\nmove assignment" << std::endl;
	BTree<int,int,bool(*)(const int&, const int&)> t3;
	std::cout << "BTree<int,int,std::less<int>> t3 = BTree<int,int>{p={5,5}}; calls" << std::endl;
	t3 = BTree<int,int,bool(*)(const int&, const int&)>{p, ptf}; 
	std::cout << "\nt2.print()" << std::endl;
	t3.print();
	
	for(i=0; i<v.size(); i++){
		p = {v[i], v[i]};
		t3.insert(p);
	}
	std::cout << "print" << std::endl;
	t3.print();

	std::cout << "\nmove constructor" << std::endl;
	BTree<int,int,bool(*)(const int&, const int&)> t4{std::move(t3)};
	t4.print();
	


} // pass function


int main(){

  constructor_test();

  copymove_test();
  
  find_test();
  
  balance_test();

  erase_test();
  
  pass_function();

}

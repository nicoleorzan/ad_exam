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


void random_fill(BTree<int,int,std::less<int>>& t, unsigned int size){
  int r;
  unsigned int j;
  std::pair<int,int> p;
  std::vector<std::pair<int,int>> v;
	
  t.clear();

  while(v.size()<size){
    r = rand() % (size*100);
    for( j=0; j<v.size(); j++){
      if( r == v[j].first )
	break;
    }
    if( j == v.size() ){
      p = {r, r};
      v.push_back(p);
    }
  }


  //std::cout << "v has size " << v.size() << std::endl;
  for(j=0; j<v.size(); j++)
    t.insert( v[j] );

  std::pair<int,int> pp{114,114};
  t.insert(pp);

}

int main(int argc, char * argv []){

  double t_start, t_end;
  unsigned int size;
  
   if( argc < 2 ){
    std::cerr<< "Error. I need the size of the tree.\nProgram exit."<<std::endl;
    exit(EXIT_FAILURE);
    }

  
  size = atoi(argv[1]);
  std::cout<<"tree size "<<size<<std::endl;
  
  if( size < 1 ){
    std::cerr<<"Error. Inconsistent tree size.\nProgram exit.\n"<<std::endl;
    exit(EXIT_FAILURE);
    }
  
  BTree<int,int,std::less<int>> t;
  
  random_fill(t, size);
  unsigned int r, j;
  std::pair<unsigned int,unsigned int> p;
  std::vector<std::pair< unsigned int, unsigned int>> v_find;
  
  while(v_find.size()<(size/2)){
    r = rand() % (size*1000);
    for( j=0; j<v_find.size(); j++){
      if( r == v_find[j].first )
	break;
    }
    if( j == v_find.size() ){
      p = {r, r};
      v_find.push_back(p);
    }
  }

  //std::cout << "v_find has size " << v_find.size() << std::endl;
   for(unsigned int p=0; p<v_find.size(); p++)
     std::cout<<v_find[p].first<<std::endl;

  for (unsigned int k=0; k<v_find.size(); k++){
    // std::cout<<"-------------finding "<< v_find[k].first<<"--------------"<<std::endl;
    t_start=cclock();
    t.find( v_find[k].first);
    t_end = cclock();
    std::cout<<"time before balancing: "<<t_end - t_start<<std::endl;
  }
  t.balance();
  
  for (unsigned int k=0; k<v_find.size(); k++){
    // std::cout<<"-------------finding "<< v_find[k].first<<"--------------"<<std::endl;
    t_start=cclock();
    t.find( v_find[k].first);
    t_end = cclock();
    std::cout<<"time after balancing: "<<t_end - t_start<<std::endl;
  }
  return 0;
}

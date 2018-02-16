#include <btree.h>
#include <iostream>
#include <memory>
#include <iterator>
#include "src/btree.cc"

int main(){
  std::pair<int, int>  p{5,4}, p1 {2,5}, p2{8,1}, p4{1,34}, p5{6,324}, p6{11,12}, p7{14,4};// p{1,2}, p1{10,8}, p2{66,1}, p3{4,5}, p4{2,12}, p5{0,80};

  BTree<int,int> t{p};

  t.insert(p);
  t.insert(p1);
  t.insert(p2);
  //t.insert(p3);
  t.insert(p4);
  t.insert(p5);
  t.insert(p6);
  t.insert(p7);
  
  t.print();

  t.diagram();

  t.clear();

  t.print(); 

  
  return 0;
}

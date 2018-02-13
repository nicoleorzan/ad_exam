#include <btree.h>
#include <iostream>
#include <memory>
#include "src/btree.cc"

int main(){
std::pair<int, int> pp;

pp.first = 1;
pp.second = 100;

BTree<int,int> t{pp};

std::pair<int, int> pp2;
pp2.first = 2;
pp2.second = 200;
t.insert(pp2);

return 0;
}

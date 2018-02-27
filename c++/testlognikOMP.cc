#include <btree.h>
#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>   // rand()
#include <vector>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
#include <fstream>

std::string random_str(int size){
std::string pool = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
std::string res;
res.resize(size);

int i;

// std::cout << "randomstr"; 

for(i=0; i<size; i++)
	res[i] = pool[ rand() % pool.length()];

return res;
}


double cclock(){

  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
  return sec;
}


int pow2(int n){
int res = 1;

while(n--)
	res*=2;
	
return res;
}


int main(){

  double t_start, t_end, mean_time_before, mean_time_after, t_max;
  int i, e, n, rank, tree_size, thread_size, size, depth_before, depth_after;
  BTree<std::string,int,std::less<std::string>> t;
  
  // unsigned int r, j;
  std::pair<std::string, int> p;
  std::vector<std::string> v;
  
  size = omp_get_num_threads();
  std::cout << "omp_get_num_threads() = " << size << std::endl;
  
std::ofstream myfile;

	myfile.open("test.dat");
  
  
  for(e=15; e<23; e++){
  	std::cout << "########################################" << std::endl;
  	std::cout << "tree size: " << tree_size << std::endl;
  	std::cout << "########################################" << std::endl;
  	
  	tree_size = pow2(e);
  	std::cout << "tree_size = " << tree_size << std::endl;
  	thread_size = tree_size / size;
  	std::cout << "thread_size = " << thread_size << std::endl;
  	
  	v.resize(tree_size);
  	std::cout << "v.size = " << v.size() << std::endl;
  	t.clear();
  	
  	#pragma omp parallel private(i, rank, thread_size)
  	{
  	size = omp_get_num_threads();
  	rank = omp_get_thread_num();
  	thread_size = tree_size / size;
  	// std::cout << "thread_size = " << thread_size << std::endl;
  	srand(rank*100);
  	std::cout << "thread " << rank << ": sranding with seed " << rank*100 << std::endl;
  	for(i=0; i<thread_size; i++){
  		v[rank*thread_size + i] = random_str(100);
  	}
  	} // parallel
  	
  	// for(j=0; j<tree_size; j++)
  	// 	std::cout << v[j] << std::endl;
  	
  	for(i=0; i<tree_size; i++){
  		p = {v[i], i};
  		t.insert(p);
  	}
  	
  	// cerca tanti max quanti i threads
  	#pragma omp parallel private(i, t_start, t_end, t_max) reduction(+:mean_time_before)
  	{
  	size = omp_get_num_threads();
  	t_max = 0.0;
  	
  	for(i=0; i<tree_size; i++){
  		t_start = cclock();
  		t.find(v[i]);
  		t_end = cclock();
  		if( t_end - t_start > t_max)
  			t_max = t_end - t_start;
  	}
  	mean_time_before = t_max/size;  //    /size;
  	} // parallel
  	
  	depth_before = t.measure_depth();
  	std::cout << "depth before: " << depth_before << std::endl;
  	std::cout << "mean_time before: " << mean_time_before << std::endl;
  	
  	
  	// BALANCE
  	
  	t.balance();
  	
  	
  	
  	
  	// cerca tanti max quanti i threads
  	#pragma omp parallel private(i, t_start, t_end, t_max) reduction(+:mean_time_after)
  	{
  	size = omp_get_num_threads();
  	t_max = 0.0;
  	
  	for(i=0; i<tree_size; i++){
  		t_start = cclock();
  		t.find(v[i]);
  		t_end = cclock();
  		if( t_end - t_start > t_max)
  			t_max = t_end - t_start;
  	}
  	mean_time_after += t_max/size;  //    /size;
  	} // parallel

  	depth_after = t.measure_depth();
  	std::cout << "depth after: " << depth_after << std::endl;  	
  	std::cout << "mean_time after: " << mean_time_after << std::endl;
  	
  	myfile << tree_size << "\t" << mean_time_before << "\t" << mean_time_after << "\t" << depth_before << "\t" << \
  		depth_after << std::endl;
  	} // for e

myfile.close();

  return 0;
}

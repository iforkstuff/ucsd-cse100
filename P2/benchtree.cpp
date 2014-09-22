#include "countint.hpp"
#include "BST.hpp"
#include "RST.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>

 /** benchtree.cpp
  *  Author: Evan Carey (cs100vbg)
  */
int main( int argc, char** argv) {

	std::srand(unsigned (std::time(0)));

	if (argc != 5) {
		std::cout << "Wrong number of arguments" << std::endl;
		return -1;
	}

    std::vector<countint> v;
    long int max_size, N, count;
    bool sorted = true;
	double numcomps = 0.0;
	double stdev = 0.0;
	double totalcomps = 0.0;
	double variance = 0.0;

	BST<countint>* bst = NULL;
	RST<countint>* rst = NULL;
	std::set<countint>* set = NULL;
    
    if ( strcmp( argv[1], "bst" ) == 0 ) {
		bst = new BST<countint>();
	} else if ( strcmp( argv[1], "rst" ) == 0 ) {
		rst = new RST<countint>();
	} else if ( strcmp( argv[1], "set" ) == 0 ) {
		set = new std::set<countint>();    
	} else {
        std::cout << "Wrong structure type argument" << std::endl;
	    return -1;
    }

	
    if( ( max_size = strtol( argv[3], NULL, 10 ) ) == 0 )
    {
	    std::cout << "Wrong order type argument" << std::endl;
		return -1;
    }
    if( ( count = strtol( argv[4], NULL, 10 ) ) == 0 )
    {
	    std::cout << "Wrong order type argument" << std::endl;
	    return -1;
    }

    if ( strcmp( argv[2], "shuffled" ) == 0)
		sorted = false;
    else if ( strcmp( argv[2], "sorted") != 0)
    {
        std::cout << "Wrong argument" << std::endl;
        return -1;
    }

	std::cout<<"# Benchmarking average number of comparisons for successful find"<<std::endl;
	std::cout << "# Data structure: " << argv[1] << std::endl;
	std::cout << "# Data: " << argv[2] << std::endl;
	std::cout << "# N is powers of 2, minus 1, from 1 to " << max_size << std::endl;
	std::cout << "# Averaging over " << argv[4] << " runs for each N" << std::endl;
	std::cout <<  std::setw(12) << "# N" << std::setw(12) << "avgcomps" << std::setw(12) << "stdev" << std::endl;

	
    for(N = 1 ; N < max_size; N = (N << 1) + 1) {
		v.clear();
		if (bst) bst->clear();
		else if (rst) rst->clear();
		else if (set) set->clear();

		for(long int i = 0; i < N; ++i) {
			v.push_back(i);
		}

		numcomps = 0.0;
		stdev = 0.0;
		totalcomps = 0.0;
		variance = 0.0;

		if ( !sorted )
			std::random_shuffle(v.begin(),v.end()); 

		for(std::vector<countint>::iterator vit = v.begin(); vit != v.end(); ++vit) {
			if (bst) bst->insert(*vit);
			else if (rst) rst->insert(*vit);
			else if (set) set->insert(*vit);
		}

		for( long int c = 0 ; c < count; c++ ) {

			if (!sorted) std::random_shuffle(v.begin(),v.end());

			countint::clearcount();
			for(std::vector<countint>::iterator vit = v.begin(); vit != v.end(); ++vit) {
				if (bst) bst->find(*vit);
				else if (rst) rst->find(*vit);
				else if (set) set->find(*vit);
			}
			numcomps = countint::getcount()/(double)N;
			stdev += (numcomps * numcomps);
			totalcomps += numcomps;
		}
		totalcomps /= (double)count; // avg number of comparisons for N
		stdev /= (double)count; // avg squared number of comparisons for N
		variance = fabs((stdev - (numcomps*numcomps)));
		stdev = sqrt( variance );
		std::cout << std::setw(12) << N << std::setw(12) << totalcomps << std::setw(12) << stdev << std::endl;
	}
};

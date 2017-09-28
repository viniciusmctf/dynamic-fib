#include <stdlib.h>
#include <unordered_map>
#include <vector>

#ifndef CACHE_SIZE
	#define CACHE_SIZE 3
#endif

std::unordered_map<int, int> cache;
std::vector< std::pair<int,int> > limited_cache;

int dyn_fib(int n);
int lim_dyn_fib(int n);

int lim_fib(int n) {
	if (n <= 1) {
		return 1;
	} else {
		int var = lim_dyn_fib(n-1) + lim_dyn_fib(n-2);
		limited_cache[n%CACHE_SIZE] = {n, var};
		//printf("{%d,%d}\n", n, var);
		return var;
	}
}

int lim_dyn_fib(int n) {
	auto old = limited_cache.at(n%CACHE_SIZE);
	if (old.first == n) {
		return old.second;
	} else {
		return lim_fib(n);
	}
}

int naive_fib(int n) {
	if (n <= 1) {
		return 1;
	} else {
		return naive_fib(n-1) + naive_fib(n-2);
	}
}

int fib(int n) {
	if (n <= 1) {
		return 1;
	} else {
		int var = dyn_fib(n-1) + dyn_fib(n-2);
		cache[n] = var;
		return var;
	}
}

int dyn_fib(int n) {
	if (cache.count(n)) {
		return cache.at(n);
	} else {
		return fib(n);
	}
}

int main(int argc, char const **argv) {
	if (argc != 3) {
		printf("Usage: ./dyn_fib FIB_VAL {0 (naive)|1 (dynamic)|2 (dynamic with limited cache)}\n");
		return 0;
	}

	if (atoi(argv[1]) < 0) {
		printf("Illegal value of N! Expected: Positive INT, was:%d\n", atoi(argv[1]));
		return 0;
	}

	limited_cache = std::vector< std::pair <int,int> >(CACHE_SIZE);
	limited_cache[0] = {0, 1};
	int var;
	if (atoi(argv[2]) == 1) {
		var = dyn_fib(atoi(argv[1]));
	} else if (atoi(argv[2]) == 0) {
		var = naive_fib(atoi(argv[1]));
	} else if (atoi(argv[2]) == 2) {
		var = lim_dyn_fib(atoi(argv[1]));
	} else {
		printf("Illegal value of strategy, available: {0|1}, chosen: %d\n", atoi(argv[2]));
	}
	printf("%d\n", var);	
	return 0;
}
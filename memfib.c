#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "memfib.h"

// implement cache
#define CACHE_SIZE 1000
static int cache[CACHE_SIZE] = {0};
static int is_computed[CACHE_SIZE] = {0};
static int current_result = 0;  

int is_present(int val) {
    if (val < 0 || val >= CACHE_SIZE) return 0;
    return is_computed[val];
}

int get_value(int val) {
    if (val < 0 || val >= CACHE_SIZE) return -1;
    return cache[val];
}

void insert_value(int val) {
    if (val < 0 || val >= CACHE_SIZE) return;
    cache[val] = current_result;  
    is_computed[val] = 1;
}

// fibonacci calculation
int fibonacci(int n) {
    if (n < 0) return -1;
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// caching function provided in lecture slides for the most part
int cached_steps_provider(int val, Provider* provider, int (*_downstream)(int)) {
    if ((*provider->is_present)(val)) {
        return (*provider->get)(val);
    }
    
    int result = (*_downstream)(val);
    current_result = result; 
    (*provider->insert)(val);
    return result;
}

int fibonacci_cached(int n) {
    Provider provider = {
        .is_present = &is_present,
        .get = &get_value,
        .insert = &insert_value
    };
    
    return cached_steps_provider(n, &provider, fibonacci);
}

// test cases function
void run_tests() {
    // basic cases
    assert(fibonacci_cached(0) == 0);
    assert(fibonacci_cached(1) == 1);
    assert(fibonacci_cached(2) == 1);
    assert(fibonacci_cached(3) == 2);
    assert(fibonacci_cached(4) == 3);
    assert(fibonacci_cached(5) == 5);
    
    // negative input
    assert(fibonacci_cached(-1) == -1);
    
    for (int i = 0; i < 10; i++) {
        assert(fibonacci_cached(i) == fibonacci(i));
    }
    
    for (int i = 0; i <= 5; i++) {
        assert(is_computed[i] == 1);
    }
    
    printf("All tests passed!\n");
}

int main() {
    // run tests
    run_tests();
    
    return 0;
}
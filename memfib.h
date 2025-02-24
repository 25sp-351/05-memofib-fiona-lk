#ifndef MEMFIB_H
#define MEMFIB_H

typedef int (*BoolFunc)(int);
typedef int (*ProviderFunction)(int);
typedef void (*VoidFunc)(int);

typedef struct {
    BoolFunc is_present;
    ProviderFunction get;
    VoidFunc insert;
} Provider;

int is_present(int val);
int get_value(int val);
void insert_value(int val);
int fibonacci(int n);
int cached_steps_provider(int val, Provider* provider, int (*_downstream)(int));
int fibonacci_cached(int n);
void run_tests(void);

#endif // MEMFIB_H
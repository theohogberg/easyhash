// performance-tester.h
#include <stdio.h>
#include <stdint.h>
#include <time.h>


// n=number of strings, size=size of string in bytes
char** allocate_random_strings(int n, size_t size) {
    char** random_strs = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) {
        char* str = malloc(size);
        for (char c = 0; c < size; c++)
            str[c] = (char)((rand()%94)+33); //only add valid chars
        random_strs[i] = str;
    }

    return random_strs;
}


void run_performance_tests(uint64_t (*hash_func)(const uint8_t*, size_t), const char* name)
{
    printf("\nTesting timed performance for %s:\n", name);

    int rs_n = 32768;
    size_t rs_size = 4096;
    char** random_strings = allocate_random_strings(rs_n, rs_size);

    clock_t start = clock();

    uint64_t hash_sum = 0;
    for(int i = 0; i < rs_n; i++) {
        hash_sum += hash_func((uint8_t*)random_strings[i], rs_size);
    }

    clock_t end = clock();
    
    double cpu_time_used = ((double) (end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("CPU time elapsed %fms\n", cpu_time_used);
    printf("Hash sum: %llx\n", hash_sum);
}

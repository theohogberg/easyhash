#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "testgen.h"
#include "apple_time_test.h"


// note: why only iterate 8-bytes?
// Single 16-bit prime
uint64_t hash_16(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    const uint64_t bits_max = len*8; //max bits
    size_t i = 0;
    for (;bits_max > i*64; i++) {
        hash ^= ptr[i];
        hash *= 65521;  // Largest 16-bit prime
    }
    uint32_t bits_left = i*64-bits_max;
    if (bits_left>0) //bits left
    {
        hash ^= (ptr[i+1]>>bits_left);
    }

    return hash;
}

// Multiple 16-bit primes
uint64_t hash_16_multi(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 65521;  // First prime
        hash *= 65519;  // Second prime
        hash *= 65497;  // Third prime
    }
    return hash;
}

// Multiple 16-bit primes
uint64_t hash_16_multi_improved(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 65521;         // First prime
        hash ^= (hash >> 32);  // Mix high bits down
        hash *= 65519;         // Second prime
        hash ^= (hash >> 27);  // Different shift for better mixing
        hash *= 65497;         // Third prime
    }
    return hash;
}

// Mixed-bit primes
uint64_t hash_mixed_primes(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 13;    // 4-bit prime
        hash *= 251;   // 8-bit prime
        hash *= 4093;  // 12-bit prime
        hash *= 65521; // 16-bit prime
    }
    return hash;
}

// 24-bit and small primes
uint64_t hash_24_and_small(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 16777213;  // 24-bit prime
        hash *= 4093;      // 12-bit prime
        hash *= 251;       // 8-bit prime
        hash *= 13;        // 4-bit prime
    }
    return hash;
}

// Alternating custom bit primes
uint64_t hash_20_alternating(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 699051;    // 20-bit prime
        hash *= 3413;      // 12-bit prime
        hash *= 173;       // 8-bit prime
        hash *= 7;         // 4-bit prime
    }
    return hash;
}


// Alternating 16-bit and 8-bit primes
uint64_t hash_16_and_8_alternating(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 43691;  // 16-bit prime
        hash *= 52429;  // 16-bit prime
        hash *= 173;    // 8-bit prime
        hash *= 169;    // 8-bit prime
    }
    return hash;
}

// Alternating 16-bit and 8-bit primes /w improved shifts
uint64_t hash_16_and_8_improved(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 43691;        // 16-bit prime (1010101010101011)
        hash ^= (hash >> 31); // Prime shift value
        hash *= 52429;        // 16-bit prime (1100110011001101)
        hash ^= (hash >> 27); // Different prime shift
        hash *= 173;          // 8-bit prime (10101101)
        hash ^= (hash >> 23); // Another prime shift
        hash *= 169;          // 8-bit prime (10101001)
    }
    return hash;
}

// Alternating 16-bit and 8-bit primes /w optimized shifts
uint64_t hash_16_and_8_improved_opt(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 43691;        // 16-bit prime (1010101010101011)
        hash ^= (hash >> 32); // Prime shift value, power of 2 more efficient shift
        hash *= 52429;        // 16-bit prime (1100110011001101)
        hash ^= (hash >> 16); // Prime shift value,  power of 2 more efficient shift
        hash *= 173;          // 8-bit prime (10101101)
    }
    return hash;
}

// Alternating 16-bit and 8-bit primes /w optimized & combined shifts
uint64_t hash_16_and_8_improved_opt_combo(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 43691;        // 16-bit prime (1010101010101011)
        hash ^= (hash >> 32) ^ (hash >> 16); // Prime shift value, combined shifts one op?
        hash *= 52429;        // 16-bit prime (1100110011001101)
        hash ^= (hash >> 16) ^ (hash >> 8); // Prime shift value, combined shifts one op?
        hash *= 173;          // 8-bit prime (10101101)
    }
    return hash;
}


// Alternating 16-bit primes /w combined shifts streamlined
uint64_t hash_16_opt_combo_mega(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 43691;        // 16-bit prime (1010101010101011)
        hash ^= (hash >> 32) ^ (hash >> 16); // Prime shift value, combined shifts one op?
        hash ^= (hash >> 16) ^ (hash >> 8); // Prime shift value, combined shifts one op?
        hash *= 52429;        // 16-bit prime (1100110011001101)
    }
    return hash;
}


// xxh3 32-bit one prime style
uint64_t xxhash_32_one(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 0x9E3779B1;  // XXH3 prime
    }
    return hash;
}

// xxh3 32-bit two prime style
uint64_t xxhash_32_two(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 0x9E3779B1;  // XXH3 prime
        hash *= 0x85EBCA77;  // XXH3 prime 2
    }
    return hash;
}

int main() {
    srand(0xFFFFFFFFu);

    run_collision_tests(hash_16, "Single 16-bit prime");
    run_collision_tests(hash_16_multi, "Multiple 16-bit primes");
    run_collision_tests(hash_16_multi_improved, "Improved multiple 16-bit primes");
    run_collision_tests(hash_mixed_primes, "Mixed-bit primes");
    run_collision_tests(hash_24_and_small, "24-bit and small primes");
    run_collision_tests(hash_20_alternating, "Alternating 20-bit and small primes");
    run_collision_tests(hash_16_and_8_alternating, "Alternating 16-bit and 8-bit primes");
    run_collision_tests(hash_16_and_8_improved, "Improved 16-bit and 8-bit primes");
    run_collision_tests(hash_16_and_8_improved_opt, "Improved 16-bit and 8-bit primes optimized");
    run_collision_tests(hash_16_and_8_improved_opt_combo, "Improved 16-bit and 8-bit primes optimized combo");
    run_collision_tests(hash_16_opt_combo_mega, "16-bit primes opt-combo megahack");
    run_collision_tests(hash_micro_prime, "8-bit micro primes");
    run_collision_tests(xxhash_32_one, "xxh3 32-bit one prime");
    run_collision_tests(xxhash_32_two, "xxh3 32-bit two prime");

    // Enable performance counters (might need root/admin privileges)
    //asm __volatile__("msr PMCNTENSET_EL0, %0" : : "r" (1UL));

    // char** rxrs = allocate_random_strings(10,10);
    // for(int q=0;q<10;q++)
    //    printf("%s\n", rxrs[q]);

    run_performance_tests(hash_16, "hash_16");

    run_performance_tests(xxhash_32_one, "xxhash_32_one");
    run_performance_tests(xxhash_32_two, "xxhash_32_two");

    return 0;
}
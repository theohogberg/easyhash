#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "testgen.h"


// Single 16-bit prime
uint64_t hash_16(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 65521;  // Largest 16-bit prime
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

// 32-bit prime style
uint64_t hash_32(const uint8_t* data, size_t len) {
    uint64_t hash = len;
    const uint64_t* ptr = (const uint64_t*)data;
    
    for (size_t i = 0; i < len/8; i++) {
        hash ^= ptr[i];
        hash *= 0x9E3779B1;  // XXH3 prime
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


int main() {
   srand(time(NULL));

   run_collision_tests(hash_16, "Single 16-bit prime");
   run_collision_tests(hash_16_multi, "Multiple 16-bit primes");
   run_collision_tests(hash_mixed_primes, "Mixed-bit primes");
   run_collision_tests(hash_24_and_small, "24-bit and small primes");
   run_collision_tests(hash_32, "32-bit prime");

   return 0;
}
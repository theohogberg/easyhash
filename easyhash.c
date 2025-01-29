#include <stdio.h>
#include <stdint.h>
#include <string.h>

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


int main() {
    // Test data - similar strings that should produce different hashes
    const char* tests[] = {
        "test1234",
        "test1235",
        "test1334",
        "TEST1234",
        "1234test"
    };
    
    printf("Single 16-bit prime:\n");
    for (int i = 0; i < 5; i++) {
        uint64_t h = hash_16((uint8_t*)tests[i], strlen(tests[i]));
        printf("%s -> %016llu\n", tests[i], h);
    }
    
    printf("\nMultiple 16-bit primes:\n");
    for (int i = 0; i < 5; i++) {
        uint64_t h = hash_16_multi((uint8_t*)tests[i], strlen(tests[i]));
        printf("%s -> %016llu\n", tests[i], h);
    }
    
    printf("\nMixed-bit primes:\n");
    for (int i = 0; i < 5; i++) {
        uint64_t h = hash_mixed_primes((uint8_t*)tests[i], strlen(tests[i]));
        printf("%s -> %016llu\n", tests[i], h);
    }
        
    printf("\n32-bit prime:\n");
    for (int i = 0; i < 5; i++) {
        uint64_t h = hash_32((uint8_t*)tests[i], strlen(tests[i]));
        printf("%s -> %016llu\n", tests[i], h);
    }
    
    return 0;
}
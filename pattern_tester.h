// pattern-tester.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Test generators for different types of inputs
char* gen_similar_prefix(int len) {
   char* str = malloc(len + 1);
   strcpy(str, "test");
   for(int i = 4; i < len; i++) {
       str[i] = '0' + (rand() % 10);
   }
   str[len] = '\0';
   return str;
}

char* gen_similar_suffix(int len) {
   char* str = malloc(len + 1);
   for(int i = 0; i < len-4; i++) {
       str[i] = '0' + (rand() % 10);
   }
   strcpy(str + len-4, "test");
   str[len] = '\0';
   return str;
}

char* gen_repeating_pattern(int len) {
   char* str = malloc(len + 1);
   const char* pattern = "azby0918";
   int pattern_len = strlen(pattern);
   for(int i = 0; i < len; i++) {
       str[i] = pattern[i % pattern_len];
   }
   str[len] = '\0';
   return str;
}

char* gen_single_char_diff(const char* base, int pos) {
   int len = strlen(base);
   char* str = strdup(base);
   str[pos] = base[pos] + 1;
   return str;
}

// Main test function
void run_collision_tests(uint64_t (*hash_func)(const uint8_t*, size_t), const char* name) {
   printf("\nTesting %s:\n", name);

   // Test similar prefixes
   printf("\nSimilar prefix tests:\n");
   for(int i = 0; i < 5; i++) {
       char* str = gen_similar_prefix(10);
       uint64_t hash = hash_func((uint8_t*)str, strlen(str));
       printf("%s -> %016llx\n", str, hash);
       free(str);
   }

   // Test similar suffixes
   printf("\nSimilar suffix tests:\n");
   for(int i = 0; i < 5; i++) {
       char* str = gen_similar_suffix(10);
       uint64_t hash = hash_func((uint8_t*)str, strlen(str));
       printf("%s -> %016llx\n", str, hash);
       free(str);
   }

   // Test repeating patterns
   printf("\nRepeating pattern tests:\n");
   for(int i = 8; i <= 16; i += 2) {
       char* str = gen_repeating_pattern(i);
       uint64_t hash = hash_func((uint8_t*)str, strlen(str));
       printf("%s -> %016llx\n", str, hash);
       free(str);
   }

   // Test single character differences
   printf("\nSingle character difference tests:\n");
   const char* base = "test1234test";
   printf("%s -> %016llx\n", base, hash_func((uint8_t*)base, strlen(base)));
   for(int i = 0; i < strlen(base); i++) {
       char* str = gen_single_char_diff(base, i);
       uint64_t hash = hash_func((uint8_t*)str, strlen(str));
       printf("%s -> %016llx\n", str, hash);
       free(str);
   }
}

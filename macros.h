#pragma once
#include <iostream>

#define PRINT_GREEN(x)   \
printf("\033[32m%s", x); \
printf("\033[0m")

#define PRINT_RED(x)     \
printf("\033[31m%s", x); \
printf("\033[0m")

#define PRINT_LINE(n)        \
std::cout << n << std::endl; \
(void)0  

#define RUN_TEST(test)                          \
do {                                            \
    std::cout << "Running " << #test << "... "; \
    if (test()) {                               \
        PRINT_GREEN("[PASSED]");                \
    }                                           \
    std::cout << std::endl;                     \
} while(0)

#define ASSERT(condition)                                                       \
do {                                                                            \
    if (!(condition)) {                                                         \
        PRINT_RED("[FAILED]");                                                  \
        std::cout << ", function: " << __FUNCTION__ << ", file: " << __FILE__;  \
        std::cout << ", line: " << __LINE__ << std::endl;                       \
        return 0;                                                               \
    }                                                                           \
} while (0)


#define MAX(n,m) ((n) > (m) ? (n) : (m))

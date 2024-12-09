#ifndef GNL_HPP
# define GNL_HPP
# include "leaks.hpp"
#include <chrono>

using namespace std::chrono;

//Don't do that at home
#define USLEEP_TERM 100
#define TEST(x) {\
    int status = 0; \
    int test = fork(); \
    if (test == 0) \
    {\
        x \
        showLeaks(); \
        exit(EXIT_SUCCESS);\
    } \
    else \
    {\
        auto a = high_resolution_clock::now(); \
        auto b = high_resolution_clock::now(); \
        while(duration_cast<microseconds>(b - a).count() < TIMEOUT_US)\
        { \
            usleep(USLEEP_TERM);  \
            if (waitpid(test, &status, WNOHANG) != 0)\
                break;\
            b = high_resolution_clock::now(); \
        }  \
        if (waitpid(test, &status, WNOHANG) == 0)  \
        { \
            kill(test, 9); \
            cout << FG_RED << "TIMEOUT"; \
        }\
    }\
}

void gnl(int fd, char const * s);

#endif
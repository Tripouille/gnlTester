#ifndef GNL_HPP
# define GNL_HPP
# include "leaks.hpp"

//Don't do that at home
#define TEST(x) { \
	int status = 0;   \
	int test = fork();\
	if (test == 0) { \
		x               \
		showLeaks();    \
		exit(EXIT_SUCCESS); \
	} else {          \
		usleep(TIMEOUT_US); \
		if (waitpid(test, &status, WNOHANG) == 0) { \
			kill(test, 9); \
			cout << FG_RED << "TIMEOUT";\
		}             \
	}                 \
}

void gnl(int fd, char const * s);

#endif
#ifndef GNL_HPP
# define GNL_HPP
# include "leaks.hpp"

//Don't do that at home
#define TEST(x) { \
	int status = 0; \
	int test = fork(); \
	if (test == 0) { \
		x showLeaks(); \
		exit(EXIT_SUCCESS); \
	} else { \
		int nb_sleep = 0; \
		const int usleep_time = TIMEOUT_US / 100; \
		while (waitpid(test, &status, WNOHANG) == 0 && nb_sleep * usleep_time <= TIMEOUT_US) \
		{ \
			usleep(usleep_time); \
			nb_sleep++; \
		} \
		if (waitpid(test, &status, WNOHANG) == 0) \
		{ \
			kill(test, 9); \
			cout << FG_RED << "TIMEOUT"; \
		} \
	} \
}

void gnl(int fd, char const * s);

#endif
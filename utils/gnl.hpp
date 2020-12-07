#ifndef GNL_HPP
# define GNL_HPP

//Don't do that at home
#define TEST(x) {int status = 0; int test = fork(); if (test == 0) {x exit(EXIT_SUCCESS);} else {usleep(TIMEOUT_US); if (waitpid(test, &status, WNOHANG) == 0) {kill(test, 9); cout << FG_RED << "TIMEOUT";}}}
struct gnlInfos
{
	int fd, r;
	char * s;
	gnlInfos(int _fd, int _r, char * _s) : fd(_fd), r(_r), s(_s) {}
};

void gnl(int fd, int r, char * s);

#endif
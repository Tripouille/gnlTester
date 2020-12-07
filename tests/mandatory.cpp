extern "C"
{
#define new tripouille
#include "get_next_line.h"
#undef new
}

#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sigsegv.hpp"
#include "check.hpp"
#include "gnl.hpp"
//Don't do that at home
#define TEST(x) {test = fork(); if (test == 0) {x exit(EXIT_SUCCESS);} else {usleep(TIMEOUT_US); if (waitpid(test, &status, WNOHANG) == 0) {kill(test, 9); cout << FG_RED << "TIMEOUT";}}}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv); int fd; int test; int status;
	cout << FG_LGRAY << "[BUFFER_SIZE = " << BUFFER_SIZE << "]: " << ENDL;
	cout << FG_LGRAY << "Invalid fd: "; cout.flush();
	TEST(/* 1 */ gnl(1000, -1, NULL);
		 /* 2 */ gnl(-1, -1, NULL);) cout << ENDL;

	cout << FG_LGRAY << "files/empty: "; cout.flush();
	fd = open("files/empty", O_RDWR);
	TEST(/* 1 */ gnl(fd, 0, "");
		 /* 2 */ gnl(fd, 0, "");) cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/nl: "; cout.flush();
	fd = open("files/nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "");
		 /* 2 */ gnl(fd, 0, "");) cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/41_no_nl: "; cout.flush();
	fd = open("files/41_no_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 0, "01234567890123456789012345678901234567890");
		 /* 2 */ gnl(fd, 0, "");) cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/41_with_nl: "; cout.flush();
	fd = open("files/41_with_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "0123456789012345678901234567890123456789");
		 /* 2 */ gnl(fd, 0, "0"); 
		 /* 3 */ gnl(fd, 0, "");) cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/42_no_nl: "; cout.flush();
	fd = open("files/42_no_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 0, "012345678901234567890123456789012345678901");
		 /* 2 */ gnl(fd, 0, "");) cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/42_with_nl: "; cout.flush();
	fd = open("files/42_with_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "01234567890123456789012345678901234567890"););
	if (BUFFER_SIZE == 42)
		 /* 2 */ {char c = 0; read(fd, &c, 1); ++iTest; check(c == '1'); --iTest;}
	cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/43_no_nl: "; cout.flush();
	fd = open("files/43_no_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 0, "0123456789012345678901234567890123456789012");
		 /* 2 */ gnl(fd, 0, "");) cout << ENDL; close(fd);

	cout << FG_LGRAY << "files/43_with_nl: "; cout.flush();
	fd = open("files/43_with_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "012345678901234567890123456789012345678901");
		 /* 2 */ gnl(fd, 1, "2");
		 /* 3 */ gnl(fd, 0, "");
		 /* 4 */ gnl(fd, 0, "");) cout << ENDL; close(fd);


	return (0);
}
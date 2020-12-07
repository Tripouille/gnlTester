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
//Don't do that in real life
#define TEST(x) {test = fork(); if (test == 0) {x} else {usleep(TIMEOUT_US); if (waitpid(test, &status, WNOHANG) == 0) {kill(test, 9); cout << FG_RED << iTest << ".TIMEOUT " << ENDL;}}}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv); int fd; int test; int status;
	cout << FG_LGRAY << "[BUFFER_SIZE = " << BUFFER_SIZE << "]: " << ENDL;
	cout << FG_LGRAY << "Invalid fd: "; cout.flush();
	TEST(/* 1 */ gnl(1000, -1, NULL);
		 /* 2 */ gnl(-1, -1, NULL); cout << ENDL; iTest = 1;)

	cout << FG_LGRAY << "files/empty: "; cout.flush();
	fd = open("files/empty", O_RDWR);
	TEST(/* 1 */ gnl(fd, 0, "");
		 /* 2 */ gnl(fd, 0, ""); cout << ENDL; iTest = 1;)

	cout << FG_LGRAY << "files/nl: "; cout.flush();
	fd = open("files/nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "");
		 /* 2 */ gnl(fd, 0, ""); cout << ENDL; iTest = 1; close(fd);)

	cout << FG_LGRAY << "files/41_no_nl: "; cout.flush();
	fd = open("files/41_no_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 0, "01234567890123456789012345678901234567890");
		 /* 2 */ gnl(fd, 0, ""); cout << ENDL; iTest = 1; close(fd);)

	cout << FG_LGRAY << "files/41_with_nl: "; cout.flush();
	fd = open("files/41_with_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "0123456789012345678901234567890123456789");
		 /* 2 */ gnl(fd, 0, "0"); 
		 /* 2 */ gnl(fd, 0, ""); cout << ENDL; iTest = 1; close(fd);)

	cout << FG_LGRAY << "files/42_with_nl: "; cout.flush();
	fd = open("files/42_with_nl", O_RDWR);
	TEST(/* 1 */ gnl(fd, 1, "01234567890123456789012345678901234567890");
		 /* 2 */ gnl(fd, 0, "1"); 
		 /* 2 */ gnl(fd, 0, ""); cout << ENDL; iTest = 1; close(fd);)

	return (0);
}
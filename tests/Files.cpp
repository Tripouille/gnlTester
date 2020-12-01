extern "C"
{
#define new tripouille
#include "get_next_line.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	cout << FG_LGRAY << "Files\t[BUFFER_SIZE = " << BUFFER_SIZE << "]: ";
	
	char * line = (char *)42; int r;
	r = get_next_line(101, &line);
	/* 1 */ check(r == -1);
	/* 2 */ check(line == (char *)42); line = (char *)42;

	int fd = open("files/empty", O_RDWR);
	r = get_next_line(fd, &line);
	/* 3 */ check(r == 0);
	/* 4 */ check(line != (char *)42);
	/* 5 */ mcheck(line, 1); free(line); line = (char *)42;

	fd = open("files/41_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 6 */ check(r == 0);
	/* 7 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 8 */ mcheck(line, 42); free(line); line = (char *)42;

	fd = open("files/41_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 9 */ check(r == 1);
	/* 10 */ check(!strcmp(line, "0123456789012345678901234567890123456789"));
	/* 11 */ mcheck(line, 41); free(line); line = (char *)42;
	char c = 0; read(fd, &c, 1);
	if (BUFFER_SIZE == 1)
		/* 12 */ check(c == '0');
	else
		++iTest;

	fd = open("files/42_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 13 */ check(r == 0);
	/* 14 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 15 */ mcheck(line, 43); free(line); line = (char *)42;

	fd = open("files/42_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 16 */ check(r == 1);
	/* 17 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 18 */ mcheck(line, 42); free(line); line = (char *)42;
	c = 0; read(fd, &c, 1);
	if (BUFFER_SIZE <= 42)
		/* 19 */ check(c == '1');
	else
		++iTest;

	fd = open("files/43_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 20 */ check(r == 0);
	/* 21 */ check(!strcmp(line, "0123456789012345678901234567890123456789012"));
	/* 22 */ mcheck(line, 44); free(line); line = (char *)42;

	fd = open("files/43_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 23 */ check(r == 1);
	/* 24 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 25 */ mcheck(line, 43); free(line); line = (char *)42;
	c = 0; read(fd, &c, 1);
	if (BUFFER_SIZE == 1)
		/* 26 */ check(c == '2');
	else
		++iTest;
	cout << ENDL;
	r = get_next_line(0, &line); free(line);
	return (0);
}
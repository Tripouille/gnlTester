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

void readAll(int fd)
{
	char * s;
	while (get_next_line(fd, &s) > 0)
		free(s);
	free(s);
}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	cout << FG_LGRAY << "[BUFFER_SIZE = " << BUFFER_SIZE << "]: ";
	
	char * line = (char *)42; int r;
	r = get_next_line(101, &line);
	/* 1 */ check(r == -1);
	/* 2 */ check(line == (char *)42); line = (char *)42;

	int fd = open("files/empty", O_RDWR);
	r = get_next_line(fd, &line);
	/* 3 */ check(r == 0);
	/* 4 */ check(line != (char *)42);
	/* 5 */ mcheck(line, 1); free(line); readAll(fd); line = (char *)42;

	fd = open("files/nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 6 */ check(r == 1);
	/* 7 */ check(!strcmp(line, ""));
	/* 8 */ mcheck(line, 1); free(line); readAll(fd); 
	r = get_next_line(fd, &line);
	/* 9 */ check(r == 0);
	/* 10 */ check(!strcmp(line, ""));
 	free(line); readAll(fd); line = (char *)42;

	fd = open("files/41_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 11 */ check(r == 0);
	/* 12 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 13 */ mcheck(line, 42); free(line); readAll(fd); line = (char *)42;

	fd = open("files/41_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 14 */ check(r == 1);
	/* 15 */ check(!strcmp(line, "0123456789012345678901234567890123456789"));
	/* 16 */ mcheck(line, 41); free(line); line = (char *)42;
	char c = 0; read(fd, &c, 1);
	if (BUFFER_SIZE == 1)
		/* 17 */ check(c == '0');
	else
		++iTest;
	readAll(fd);

	fd = open("files/42_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 18 */ check(r == 0);
	/* 19 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 20 */ mcheck(line, 43); free(line); readAll(fd); line = (char *)42;

	fd = open("files/42_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 21 */ check(r == 1);
	/* 22 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 23 */ mcheck(line, 42); free(line); line = (char *)42;
	c = 0; read(fd, &c, 1);
	if (BUFFER_SIZE <= 42)
		/* 24 */ check(c == '1');
	else
		++iTest;
	readAll(fd);

	fd = open("files/43_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 25 */ check(r == 0);
	/* 26 */ check(!strcmp(line, "0123456789012345678901234567890123456789012"));
	/* 27 */ mcheck(line, 44); free(line); readAll(fd); line = (char *)42;

	fd = open("files/43_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 28 */ check(r == 1);
	/* 29 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 30 */ mcheck(line, 43); free(line); line = (char *)42;
	c = 0; read(fd, &c, 1);
	if (BUFFER_SIZE == 1)
		/* 31 */ check(c == '2');
	else
		++iTest;
	readAll(fd);

	fd = open("files/multiple_nlx5", O_RDWR);
	r = get_next_line(fd, &line); //x1
	/* 32 */ check(r == 1);
	/* 33 */ check(!strcmp(line, ""));
	/* 34 */ mcheck(line, 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x2
	/* 35 */ check(r == 1);
	/* 36 */ check(!strcmp(line, ""));
	/* 37 */ mcheck(line, 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x3
	/* 38 */ check(r == 1);
	/* 39 */ check(!strcmp(line, ""));
	/* 40 */ mcheck(line, 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x4
	/* 41 */ check(r == 1);
	/* 42 */ check(!strcmp(line, ""));
	/* 43 */ mcheck(line, 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x5
	/* 44 */ check(r == 1);
	/* 46 */ check(!strcmp(line, ""));
	/* 47 */ mcheck(line, 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line);
	/* 48 */ check(r == 0);
	/* 49 */ check(!strcmp(line, ""));
	/* 50 */ mcheck(line, 1); free(line); line = (char *)42;
	readAll(fd);


	cout << ENDL;
	return (0);
}
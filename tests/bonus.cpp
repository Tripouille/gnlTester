extern "C"
{
#define new tripouille
#include "get_next_line_bonus.h"
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
	r = get_next_line(1000, &line);
	/* 1 */ check(r == -1);
	/* 2 */ check(line == (char *)42); line = (char *)42;

	int fd[4];
	fd[0] = open("files/41_with_nl", O_RDWR);
	r = get_next_line(fd[0], &line);
	/* 3 */ check(r == 1);
	/* 4 */ check(!strcmp(line, "0123456789012345678901234567890123456789"));
	/* 5 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	fd[1] = open("files/42_with_nl", O_RDWR);
	get_next_line(1001, &line);
	r = get_next_line(fd[1], &line);
	/* 6 */ check(r == 1);
	/* 7 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 8 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	fd[2] = open("files/43_with_nl", O_RDWR);
	get_next_line(1002, &line);
	r = get_next_line(fd[2], &line);
	/* 9 */ check(r == 1);
	/* 10 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 11 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	get_next_line(1003, &line);
	r = get_next_line(fd[0], &line);
	/* 12 */ check(r == 0);
	/* 13 */ check(!strcmp(line, "0"));
	/* 14 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	get_next_line(1004, &line);
	r = get_next_line(fd[1], &line);
	/* 15 */ check(r == 0);
	/* 16 */ check(!strcmp(line, "1"));
	/* 17 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	get_next_line(1005, &line);
	r = get_next_line(fd[2], &line);
	/* 18 */ check(r == 0);
	/* 19 */ check(!strcmp(line, "2"));
	/* 20 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	fd[3] = open("files/nl", O_RDWR);
	get_next_line(1006, &line);
	r = get_next_line(fd[3], &line);
	/* 21 */ check(r == 1);
	/* 22 */ check(!strcmp(line, ""));
	/* 23 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	get_next_line(1007, &line);
	r = get_next_line(fd[3], &line);
	/* 24 */ check(r == 0);
	/* 25 */ check(!strcmp(line, ""));
	/* 26 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;

	cout << ENDL;
	return (0);
}
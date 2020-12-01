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
	cout << FG_LGRAY << "Basics\t[BUFFER_SIZE = " << BUFFER_SIZE << "]: ";
	
	char * line = (char *)42; int r;
	r = get_next_line(101, &line);
	/* 1 */ check(r == -1);
	/* 2 */ check(line == (char *)42); line = (char *)42;

	int fd = open("files/empty", O_RDWR);
	r = get_next_line(fd, &line);
	/* 3 */ check(r == 0);
	/* 4 */ check(line != (char *)42);
	/* 5 */ mcheck(line, 1); free(line); close(fd); line = (char *)42;

	fd = open("files/42_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 6 */ check(r == 1);
	/* 7 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 8 */ mcheck(line, 43); free(line); close(fd); line = (char *)42;


	cout << ENDL;
	return (0);
}
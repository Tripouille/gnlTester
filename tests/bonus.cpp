extern "C"
{
#define new tripouille
#include "get_next_line_bonus.h"
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

//https://github.com/arhuaco/ram-is-mine/blob/master/src/ram_is_mine.c
extern bool is_initializing;

int iTest = 1;
int main(void)
{
	is_initializing = false;
	signal(SIGSEGV, sigsegv); int fd[4];
	title("[BUFFER_SIZE = " << BUFFER_SIZE << "]: " << ENDL)
	
	title("multiple fd: ")
	fd[0] = open("files/41_with_nl", O_RDWR);
	/* 1 */ gnl(1000, NULL);
	/* 2 */ gnl(fd[0], "0123456789012345678901234567890123456789\n");

	fd[1] = open("files/42_with_nl", O_RDWR);
	/* 3 */ gnl(1001, NULL);
	/* 4 */ gnl(fd[1], "01234567890123456789012345678901234567890\n");

	fd[2] = open("files/43_with_nl", O_RDWR);
	/* 5 */ gnl(1002, NULL);
	/* 6 */ gnl(fd[2], "012345678901234567890123456789012345678901\n");

	/* 7 */ gnl(1003, NULL);
	/* 8 */ gnl(fd[0], "0");

	/* 9 */ gnl(1004, NULL);
	/* 10 */ gnl(fd[1], "1");

	/* 11 */ gnl(1005, NULL);
	/* 12 */ gnl(fd[2], "2");

	/* 13 */ gnl(fd[0], NULL);
	/* 14 */ gnl(fd[1], NULL);
	/* 15 */ gnl(fd[2], NULL);
	showLeaks();

	fd[3] = open("files/nl", O_RDWR);
	/* 16 */ gnl(1006, NULL);
	/* 17 */ gnl(fd[3], "\n");
	/* 18 */ gnl(1007, NULL);
	/* 19 */ gnl(fd[3], NULL);
	showLeaks();
	write(1, "\n", 1);
	return (0);
}
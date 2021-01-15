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

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv); int fd[4];
	title("[BUFFER_SIZE = " << BUFFER_SIZE << "]: " << ENDL)
	
	title("multiple fd: ")
	fd[0] = open("files/41_with_nl", O_RDWR);
	/* 1 */ gnl(1000, -1, NULL);
	/* 2 */ gnl(fd[0], 1, "0123456789012345678901234567890123456789");

	fd[1] = open("files/42_with_nl", O_RDWR);
	/* 3 */ gnl(1001, -1, NULL);
	/* 4 */ gnl(fd[1], 1, "01234567890123456789012345678901234567890");

	fd[2] = open("files/43_with_nl", O_RDWR);
	/* 5 */ gnl(1002, -1, NULL);
	/* 6 */ gnl(fd[2], 1, "012345678901234567890123456789012345678901");

	/* 7 */ gnl(1003, -1, NULL);
	/* 8 */ gnl(fd[0], 0, "0");

	/* 9 */ gnl(1004, -1, NULL);
	/* 10 */ gnl(fd[1], 0, "1");

	/* 11 */ gnl(1005, -1, NULL);
	/* 12 */ gnl(fd[2], 0, "2");
	showLeaks();
	fd[3] = open("files/nl", O_RDWR);
	/* 13 */ gnl(1006, -1, NULL);
	/* 14 */ gnl(fd[3], 1, "");
	/* 15 */ gnl(1007, -1, NULL);
	/* 16 */ gnl(fd[3], 0, "");
	showLeaks();
	write(1, "\n", 1);
	return (0);
}
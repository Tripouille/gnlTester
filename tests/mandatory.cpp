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
	r = get_next_line(1000, &line);
	/* 1 */ check(r == -1);
	/* 2 */ check(line == (char *)42); line = (char *)42;
	int fd = open("files/empty", O_RDWR);
	r = get_next_line(fd, &line);
	/* 3 */ check(r == 0);
	/* 4 */ check(line != (char *)42);
	/* 5 */ mcheck(line, strlen(line) + 1); free(line); readAll(fd); line = (char *)42;

	fd = open("files/nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 6 */ check(r == 1);
	/* 7 */ check(!strcmp(line, ""));
	/* 8 */ mcheck(line, strlen(line) + 1); free(line); readAll(fd); 
	r = get_next_line(fd, &line);
	/* 9 */ check(r == 0);
	/* 10 */ check(!strcmp(line, ""));
 	free(line); readAll(fd); line = (char *)42;

	fd = open("files/41_no_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 11 */ check(r == 0);
	/* 12 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 13 */ mcheck(line, strlen(line) + 1); free(line); readAll(fd); line = (char *)42;

	fd = open("files/41_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 14 */ check(r == 1);
	/* 15 */ check(!strcmp(line, "0123456789012345678901234567890123456789"));
	/* 16 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
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
	/* 20 */ mcheck(line, strlen(line) + 1); free(line); readAll(fd); line = (char *)42;

	fd = open("files/42_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 21 */ check(r == 1);
	/* 22 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 23 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
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
	/* 27 */ mcheck(line, strlen(line) + 1); free(line); readAll(fd); line = (char *)42;

	fd = open("files/43_with_nl", O_RDWR);
	r = get_next_line(fd, &line);
	/* 28 */ check(r == 1);
	/* 29 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 30 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
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
	/* 34 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x2
	/* 35 */ check(r == 1);
	/* 36 */ check(!strcmp(line, ""));
	/* 37 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x3
	/* 38 */ check(r == 1);
	/* 39 */ check(!strcmp(line, ""));
	/* 40 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x4
	/* 41 */ check(r == 1);
	/* 42 */ check(!strcmp(line, ""));
	/* 43 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x5
	/* 44 */ check(r == 1);
	/* 45 */ check(!strcmp(line, ""));
	/* 46 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line);
	/* 47 */ check(r == 0);
	/* 48 */ check(!strcmp(line, ""));
	/* 49 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	readAll(fd);

	fd = open("files/multiple_line_no_nl", O_RDWR);
	r = get_next_line(fd, &line); //x1
	/* 50 */ check(r == 1);
	/* 51 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 52 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x2
	/* 53 */ check(r == 1);
	/* 54 */ check(!strcmp(line, "987654321098765432109876543210987654321098"));
	/* 55 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x3
	/* 56 */ check(r == 1);
	/* 57 */ check(!strcmp(line, "0123456789012345678901234567890123456789012"));
	/* 58 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x4
	/* 59 */ check(r == 1);
	/* 60 */ check(!strcmp(line, "987654321098765432109876543210987654321098"));
	/* 61 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x5
	/* 62 */ check(r == 0);
	/* 63 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 64 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	readAll(fd);

	fd = open("files/multiple_line_with_nl", O_RDWR);
	r = get_next_line(fd, &line); //x1
	/* 65 */ check(r == 1);
	/* 66 */ check(!strcmp(line, "9876543210987654321098765432109876543210"));
	/* 67 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x2
	/* 68 */ check(r == 1);
	/* 69 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 70 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x3
	/* 71 */ check(r == 1);
	/* 72 */ check(!strcmp(line, "987654321098765432109876543210987654321098"));
	/* 73 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x4
	/* 74 */ check(r == 1);
	/* 75 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 76 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x5
	/* 77 */ check(r == 1);
	/* 78 */ check(!strcmp(line, "9876543210987654321098765432109876543210"));
	/* 79 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x6
	/* 80 */ check(r == 0);
	/* 81 */ check(!strcmp(line, ""));
	/* 82 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	readAll(fd);

	fd = open("files/alternate_line_nl_no_nl", O_RDWR);
	r = get_next_line(fd, &line); //x1
	/* 83 */ check(r == 1);
	/* 84 */ check(!strcmp(line, "98765432109876543210987654321098765432109"));
	/* 85 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x2
	/* 86 */ check(r == 1);
	/* 87 */ check(!strcmp(line, ""));
	/* 88 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x3
	/* 89 */ check(r == 1);
	/* 90 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 91 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x4
	/* 92 */ check(r == 1);
	/* 93 */ check(!strcmp(line, ""));
	/* 94 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x5
	/* 95 */ check(r == 1);
	/* 96 */ check(!strcmp(line, "9876543210987654321098765432109876543210987"));
	/* 97 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x6
	/* 98 */ check(r == 1);
	/* 99 */ check(!strcmp(line, ""));
	/* 100 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x7
	/* 101 */ check(r == 1);
	/* 102 */ check(!strcmp(line, "012345678901234567890123456789012345678901"));
	/* 103 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x8
	/* 104 */ check(r == 1);
	/* 105 */ check(!strcmp(line, ""));
	/* 106 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x9
	/* 107 */ check(r == 0);
	/* 108 */ check(!strcmp(line, "98765432109876543210987654321098765432109"));
	/* 109 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x10
	/* 110 */ check(r == 0);
	/* 111 */ check(!strcmp(line, ""));
	/* 112 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	readAll(fd);

	fd = open("files/alternate_line_nl_with_nl", O_RDWR);
	r = get_next_line(fd, &line); //x1
	/* 113 */ check(r == 1);
	/* 114 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 115 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x2
	/* 116 */ check(r == 1);
	/* 117 */ check(!strcmp(line, ""));
	/* 118 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x3
	/* 119 */ check(r == 1);
	/* 120 */ check(!strcmp(line, "987654321098765432109876543210987654321090"));
	/* 121 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x4
	/* 122 */ check(r == 1);
	/* 123 */ check(!strcmp(line, ""));
	/* 124 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x5
	/* 125 */ check(r == 1);
	/* 126 */ check(!strcmp(line, "0123456789012345678901234567890123456789012"));
	/* 127 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x6
	/* 128 */ check(r == 1);
	/* 129 */ check(!strcmp(line, ""));
	/* 130 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x7
	/* 131 */ check(r == 1);
	/* 132 */ check(!strcmp(line, "987654321098765432109876543210987654321090"));
	/* 133 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x8
	/* 134 */ check(r == 1);
	/* 135 */ check(!strcmp(line, ""));
	/* 136 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x9
	/* 137 */ check(r == 1);
	/* 138 */ check(!strcmp(line, "01234567890123456789012345678901234567890"));
	/* 139 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	r = get_next_line(fd, &line); //x10
	/* 140 */ check(r == 0);
	/* 141 */ check(!strcmp(line, ""));
	/* 142 */ mcheck(line, strlen(line) + 1); free(line); line = (char *)42;
	readAll(fd);

	r = get_next_line(-1, &line); //Astridounette test <3
	/* 143 */ check(r == -1);
	/* 144 */ check(line == (char *)42); line = (char *)42;

	cout << ENDL;
	return (0);
}
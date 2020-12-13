extern "C"
{
#define new tripouille
#include "get_next_line.h"
#undef new
}

#include "gnl.hpp"
#include "color.hpp"
#include "check.hpp"

#include <string.h>

extern int iTest;

using namespace std;

void gnl(int fd, int r, char const * s)
{
	char * line = NULL;
	int gnlReturn = get_next_line(fd, &line);
	check(r == gnlReturn && (s == NULL ? line == NULL : !strcmp(line, s)));
	if (s != NULL)
		mcheck(line, strlen(s) + 1);
	if (gnlReturn != -1)
		free(line);
	iTest++;
}
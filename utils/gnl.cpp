extern "C"
{
#define new tripouille
#include "get_next_line.h"
#undef new
}

# include <unistd.h>
# include <string.h>
# include <sys/wait.h>

#include "gnl.hpp"
#include "color.hpp"
#include "check.hpp"

extern int iTest;

using namespace std;

void gnl(int fd, int r, char * s)
{
	pid_t actualTest = fork();
	if (actualTest < 0)
		throw std::runtime_error("I have dropped my fork");
	else if (actualTest == 0)
	{
		char * line = NULL;
		int gnlReturn = get_next_line(fd, &line);
		check(r == gnlReturn && s == NULL ? line == NULL : !strcmp(line, s));
		if (s != NULL)
			mcheck(line, strlen(s) + 1);
		if (gnlReturn != -1)
			free(line);
		exit(EXIT_SUCCESS);
	}
	else
	{
		usleep(TIMEOUT_US); int status;
		if (waitpid(actualTest, &status, WNOHANG) == 0)
		{
			kill(actualTest, 9);
				cout << FG_RED << iTest << ".TIMEOUT ";
		}
	}
	iTest++;
}
#include "check.hpp"

extern int iTest;

void check(bool succes)
{
	if (succes)
		{cout << FG_GREEN << iTest << ".OK "; cout.flush();}
	else
		{cout << FG_RED << iTest << ".KO "; cout.flush();}
}

void mcheck(void * p, size_t required_size)
{
	#ifdef __unix__
	void * p2 = malloc(required_size); 
	if (malloc_usable_size(p) == malloc_usable_size(p2))
		{cout << FG_GREEN << iTest++ << ".MOK "; cout.flush();}
	else
		{cout << FG_RED << iTest++ << ".MKO "; cout.flush();}
	free(p2);
	#endif
	#ifdef __APPLE__
	void * p2 = malloc(required_size); 
	if (malloc_size(p) == malloc_size(p2))
		{cout << FG_GREEN << iTest++ << ".MOK "; cout.flush();}
	else
		{cout << FG_RED << iTest++ << ".MKO "; cout.flush();}
	free(p2);
	#endif
}
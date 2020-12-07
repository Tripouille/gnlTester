#ifndef GNL_HPP
# define GNL_HPP
struct gnlInfos
{
	int fd, r;
	char * s;
	gnlInfos(int _fd, int _r, char * _s) : fd(_fd), r(_r), s(_s) {}
};

void gnl(int fd, int r, char * s);

#endif
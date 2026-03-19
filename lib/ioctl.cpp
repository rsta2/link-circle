#include <sys/ioctl.h>
#include <errno.h>

extern "C"
int ioctl(int fd, unsigned long request, ...)
{
	if (request == FIONBIO)
	{
		return 0;
	}

	errno = EINVAL;

	return -1;
}

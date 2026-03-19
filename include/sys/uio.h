#ifndef _SYS_UIO_H_
#define _SYS_UIO_H_

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct iovec
{
    void    *iov_base;
    size_t  iov_len;
};

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#ifdef __cplusplus
}
#endif

#endif

#ifndef _SYS_UN_H_
#define _SYS_UN_H_

#include <bits/sockettypes.h>

/* UNIX domain socket address */
struct sockaddr_un
{
    sa_family_t sun_family;
    char        sun_path[108];
};

#endif

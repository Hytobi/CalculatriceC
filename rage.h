#ifndef RAGE_H
#define RAGE_H

#include <stdlib.h>

#define RAGE_QUIT(msg)        \
    {                         \
        fprintf(stderr, msg); \
        exit(1);              \
    }

#endif
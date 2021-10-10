#ifndef __lib_h__
#define __lib_h__

#include "types.h"

#define SYS_WRITE 0
#define SYS_FORK 1
#define SYS_EXEC 4      //  原exec为2，sleep为3，exit为3
#define SYS_SLEEP 2
#define SYS_EXIT 3

#define STD_OUT 0

#define MAX_BUFFER_SIZE 256

int printf(const char *format,...);

pid_t fork();

int sleep(uint32_t time);

int exit();

#endif

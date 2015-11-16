#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "std_wrappers.h"

void * wrapper_malloc(const size_t size, const char * file, const int line)
{
    void * allocation = malloc(size);
    if ( !allocation ) {
        fprintf(stderr, "Error: %s (%d) at %s line %d\n",
                strerror(errno), errno, file, line);
        exit(EXIT_FAILURE);
    }
    return allocation;
}

void * wrapper_realloc(void * ptr, const size_t size,
                       const char * file, const int line)
{
    void * allocation = realloc(ptr, size);
    if ( !allocation ) {
        fprintf(stderr, "Error: %s (%d) at %s line %d\n",
                strerror(errno), errno, file, line);
        exit(EXIT_FAILURE);
    }
    return allocation;
}

char * wrapper_strdup(const char * str, const char * file, const int line)
{
    char * new_str = wrapper_malloc(strlen(str) + 1, file, line);
    strcpy(new_str, str);
    return new_str;
}


pid_t wrapper_fork(const char * file, const int line)
{
    pid_t pid = fork();
    if ( pid == -1 ) {
        fprintf(stderr, "Error: %s (%d) at %s line %d\n",
                strerror(errno), errno, file, line);
        exit(EXIT_FAILURE);
    }
    return pid;
}


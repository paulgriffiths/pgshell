#ifndef PG_SHELL_STD_WRAPPERS_H
#define PG_SHELL_STD_WRAPPERS_H

#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <sys/types.h>

void * wrapper_malloc(const size_t size, const char * file, const int line);
void * wrapper_realloc(void * ptr, const size_t size,
                       const char * file, const int line);
void * wrapper_strdup(const char * str, const char * file, const int line);
pid_t wrapper_fork(const char * file, const int line);

#define xmalloc(size) wrapper_malloc((size), __FILE__, __LINE__)
#define xrealloc(ptr, size) wrapper_realloc((ptr), (size), __FILE__, __LINE__)
#define xstrdup(str) wrapper_strdup((str), __FILE__, __LINE__)
#define xfork() wrapper_fork(__FILE__, __LINE__)

#endif      /*  PG_SHELL_STD_WRAPPERS_H  */

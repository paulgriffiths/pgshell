#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "builtin_cd.h"
#include "command.h"
#include "std_wrappers.h"

void builtin_cd(Command cmd)
{
    char * path = NULL;

    if ( command_num_args(cmd) > 1 ) {
        path = xstrdup(command_argument_at_index(cmd, 1));
    }
    else {
        uid_t u = getuid();
        struct passwd * p;

        setpwent();

        while ( (p = getpwent()) ) {
            if ( p->pw_uid == u ) {
                path = xstrdup(p->pw_dir);
                break;
            }
        }

        if ( !path ) {
            fprintf(stderr, "Error: couldn't locate user ID at %s line %d\n",
                    __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }

        endpwent();
    }

    int status = chdir(path);
    if ( status < 0 ) {
        switch ( errno ) {
            case ENOENT:
                fprintf(stderr,
                        "pgshell: cd: %s: No such file or directory\n",
                        path);
                break;

            case EACCES:
                fprintf(stderr, "pgshell: cd: %s: Permission denied\n",
                        path);
                break;

            case ENOTDIR:
                fprintf(stderr, "pgshell: cd: %s: Not a directory\n",
                        path);
                break;

            default:
                fprintf(stderr, "pgshell: cd: couldn't change directory\n");
                break;
        }
    }

    free(path);
}

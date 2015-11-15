#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "io.h"
#include "shell_token_list.h"
#include "cmdline.h"
#include "command.h"
#include "shell_parser.h"
#include "std_wrappers.h"

#define BUFFER_SIZE 1024

static int run_foreground_command(CmdCmpList list);

void run_shell(void)
{
    char input[BUFFER_SIZE];

    while (true) {
        if ( !get_input_line(input, BUFFER_SIZE) ) {
            putchar('\n');
            break;
        }

        if ( !strcmp(input, "exit") ) {
            break;
        }

        TokenList tlist = parse_input(input);
        CmdCmpList clist = cmdline_create(tlist);
        token_list_destroy(tlist);

        if ( !cmdline_is_valid(clist) ) {
            printf("pgshell: syntax error\n");
        }
        else {
            run_foreground_command(clist);
        }

        cmdline_destroy(clist);
    }

    printf("Goodbye!\n");
}

static int run_foreground_command(CmdCmpList list)
{
    pid_t pid = xfork();

    if ( pid == 0 ) {
        Command cmd = cmdline_component_at_index(list, 0)->content.cmd;
        char ** args = command_raw_args(cmd);
        execvp(args[0], args);
        switch ( errno ) {
            case EACCES:
                fprintf(stderr, "pgshell: %s: Permission denied\n", args[0]);
                break;

            case ENOENT:
                fprintf(stderr, "pgshell: %s: No such file or directory\n",
                        args[0]);
                break;

            default:
                fprintf(stderr, "pgshell: other exec() error\n");
                break;
        }
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);
    return status;
}


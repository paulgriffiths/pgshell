#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "std_wrappers.h"

#define INITIAL_COMMAND_CAPACITY 8

struct shell_command {
    char ** args;
    size_t num_args;
    size_t capacity;
};

Command command_create(void)
{
    struct shell_command * new_cmd = xmalloc(sizeof *new_cmd);
    new_cmd->capacity = INITIAL_COMMAND_CAPACITY;
    new_cmd->num_args = 0;
    new_cmd->args = xmalloc(new_cmd->capacity * sizeof *new_cmd->args);
    new_cmd->args[0] = NULL;
    return new_cmd;
}

void command_destroy(Command cmd)
{
    for ( size_t i = 0; i < cmd->num_args; ++i ) {
        free(cmd->args[i]);
    }
    free(cmd->args);
    free(cmd);
}

void command_add_argument(Command cmd, const char * arg)
{
    if ( cmd->num_args + 2 >= cmd->capacity ) {
        cmd->capacity *= 2;
        cmd->args = xrealloc(cmd->args, cmd->capacity * sizeof *cmd->args);
    }

    cmd->args[cmd->num_args] = xstrdup(arg);
    ++cmd->num_args;
    cmd->args[cmd->num_args] = NULL;
}

size_t command_num_args(Command cmd)
{
    return cmd->num_args;
}

char ** command_raw_args(Command cmd)
{
    return cmd->args;
}

char * command_command(Command cmd)
{
    return cmd->args[0];
}

void command_print(Command cmd)
{
    if ( cmd->num_args > 0 ) {
        printf("Program: %s (num_args %zu, capacity %zu)\n",
                cmd->args[0], cmd->num_args, cmd->capacity);
    }

    for ( size_t i = 1; i < cmd->num_args; ++i ) {
        printf("  Arg %zu: %s\n", i, cmd->args[i]);
    }
}

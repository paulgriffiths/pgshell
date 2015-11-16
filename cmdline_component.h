#ifndef PG_SHELL_CMDLINE_COMPONENT_H
#define PG_SHELL_CMDLINE_COMPONENT_H

#include <stddef.h>
#include <stdbool.h>
#include "shell_token.h"
#include "shell_token_list.h"
#include "command.h"

enum command_type {
    CT_COMMAND,
    CT_OPERATOR
};

struct command_component {
    enum command_type type;
    union {
        Command cmd;
        enum shell_operator_type operator;
    } content;
};

struct command_component * command_component_create_command(Command cmd);
struct command_component *
command_component_create_operator(const enum shell_operator_type operator);
void command_component_destroy(struct command_component * cmp);
void command_component_print(struct command_component * cmp);

#endif      /*  PG_SHELL_CMDLINE_H  */

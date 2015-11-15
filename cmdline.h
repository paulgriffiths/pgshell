#ifndef PG_SHELL_CMDLINE_H
#define PG_SHELL_CMDLINE_H

#include <stddef.h>
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

typedef struct command_component_list * CmdCmpList;

CmdCmpList cmdline_create(TokenList list);
void cmdline_destroy(CmdCmpList list);
size_t cmdline_length(CmdCmpList list);
void cmdline_add_command(CmdCmpList list, Command cmd);
void cmdline_add_operator(CmdCmpList list, enum shell_operator_type operator);
struct command_component * cmdline_component_at_index(CmdCmpList list,
        const size_t index);
void cmdline_print(CmdCmpList list);
void command_component_print(struct command_component * cmp);


#endif      /*  PG_SHELL_CMDLINE_H  */

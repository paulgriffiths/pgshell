#ifndef PG_SHELL_CMDLINE_H
#define PG_SHELL_CMDLINE_H

#include <stddef.h>
#include <stdbool.h>
#include "shell_token.h"
#include "shell_token_list.h"
#include "command.h"
#include "cmdline_component.h"

typedef struct command_component_list * CmdCmpList;

CmdCmpList cmdline_create(TokenList list);
void cmdline_destroy(CmdCmpList list);
size_t cmdline_length(CmdCmpList list);
void cmdline_add_command(CmdCmpList list, Command cmd);
void cmdline_add_operator(CmdCmpList list, enum shell_operator_type operator);
struct command_component * cmdline_component_at_index(CmdCmpList list,
        const size_t index);
void cmdline_print(CmdCmpList list);
bool cmdline_is_valid(CmdCmpList list);


#endif      /*  PG_SHELL_CMDLINE_H  */

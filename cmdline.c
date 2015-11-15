#include <stdlib.h>
#include "cmdline.h"

struct command_component_list {
    struct command_component ** components;
    size_t length;
    size_t capacity;
};

CmdCmpList cmdline_create(void)
{
}

void cmdline_destroy(CmdCmpList list)
{
}

size_t cmdline_length(CmdCmpList list)
{
}

void cmdline_add_command(CmdCmpList list, Command cmd)
{
}

void cmdline_add_operator(CmdCmpList list, enum shell_operator_type operator)
{
}

struct command_component * cmdline_component_at_index(CmdCmpList list,
        const size_t index)
{
}


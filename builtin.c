#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "builtin.h"
#include "command.h"
#include "builtin_cd.h"

bool execute_builtin(Command cmd)
{
    if ( !strcmp(command_command(cmd), "cd") ) {
        builtin_cd(cmd);
        return true;
    }
    else {
        return false;
    }
}


#ifndef PG_SHELL_BUILTIN_H
#define PG_SHELL_BUILTIN_H

#include <stdbool.h>
#include "command.h"

bool execute_builtin(Command cmd);

#endif      /*  PG_SHELL_BUILTIN_H  */

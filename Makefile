# pgshell Makefile
# ================
# Copyright 2015 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/

MKFLPATH    := $(realpath $(lastword $(MAKEFILE_LIST)))
MKFLDIR     := $(dir $(MKFLPATH))

SOURCES     := $(wildcard *.c)
OBJECTS	     = $(subst .c,.o,$(SOURCES))
DEPENDS	     = $(subst .c,.d,$(SOURCES))

CC          := gcc
CFLAGS      := -std=c99 -pedantic -Wall -Wextra -g -DDEBUG -DDEBUG_ALL
RM          := rm -f
SED         := sed
CTAGS       := ctags

CLNGLOB      = $(OBJECTS) $(DEPENDS) tags tests

default: tests

# clean - removes ancilliary files from working directory

.PHONY: clean
clean:
	-@$(RM) $(CLNGLOB) 2>/dev/null

# tags - makes tags file

.PHONY: tags
tags:
	@$(CTAGS) $(SOURCES)

# Dependencies

-include $(DEPENDS)

%.d: %.c
	@$(CC) -M $(CFLAGS) $(CPPFLAGS) $< > $@.tmp; \
		$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
		$(RM) $@.tmp

tests: $(OBJECTS)
	gcc -o tests $(OBJECTS)


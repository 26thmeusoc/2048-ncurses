#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([2048-ncurses], [0.0.1])
AC_CONFIG_SRCDIR([src/game.h])
AM_INIT_AUTOMAKE

# Not needed right now
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_SEARCH_LIBS(mvprintw,ncurses,[],[AC_ERROR([ncurses is required.])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h ncurses.h math.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_OUTPUT(Makefile src/Makefile)

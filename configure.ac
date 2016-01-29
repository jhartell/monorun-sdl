#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([monorun-sdl], [0.1])
AC_CONFIG_SRCDIR([src/monorun.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S

# Checks for libraries.
PKG_CHECK_MODULES([SDL2],[sdl2])
AC_CHECK_LIB([SDL2],[SDL_Init], [], [AC_MSG_ERROR([libSDL2 not found])])
AC_CHECK_LIB([SDL2_image],[IMG_Init], [], [AC_MSG_ERROR([libSDL2_image not found])])
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T

# Checks for library functions.
AC_CHECK_FUNCS([memmove memset sqrt])

AC_CONFIG_FILES([Makefile
				 src/Makefile])
AC_OUTPUT

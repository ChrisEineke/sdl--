AC_PREREQ([2.63])
AC_INIT([SDL++], [0.0.10], [chris@chriseineke.com], [SDL++])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/Makefile.am])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_LANG([C++])
AC_CHECK_LIB([SDL], [SDL_Init])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	tests/Makefile
])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL
AC_OUTPUT

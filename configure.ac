
m4_define([MAJOR_V], [0])
m4_define([MINOR_V], [1])
m4_define([PATCH_V], [0])

AC_INIT([igni-samples], MAJOR_V.MINOR_V.PATCH_V)
CFLAGS="$CFLAGS -DMAJ_V="MAJOR_V" -DMIN_V="MINOR_V" -DPATCH_V="PATCH_V
AC_PREFIX_DEFAULT(/usr)

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_CHECK_LIB([igni], [igniRndOpen], [], AC_MSG_ERROR([libigni not found!]))

AC_PROG_CC

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
	Makefile
	1-model-load/Makefile
])

AC_OUTPUT


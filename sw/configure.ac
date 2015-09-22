 dnl Process this file with autoconf to produce a configure script.
AC_PREREQ([2.68])
AC_INIT(calaos_plc_io_fw, 0.1, contact@calaos.fr)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([1.11 -Wno-portability])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

AC_ARG_WITH([board],
    [AS_HELP_STRING([--with-board], [Board selection])],
    [],
    [with_board=none]
    )

arch=$host_cpu
board=$with_board

if test -f $srcdir/config/$arch/$board.cfg; then
    source $srcdir/config/$arch/$board.cfg
fi

AC_SUBST(ARCH, $arch)
AC_SUBST(BOARD, $board)

AC_SUBST([CONFIG_LDFLAGS], ["$ARCH_LDFLAGS $BOARD_LDFLAGS"])
AC_SUBST([CONFIG_CFLAGS], ["$ARCH_CFLAGS $BOARD_CFLAGS"])

CFLAGS="$CFLAGS $ARCH_CFLAGS $BOARD_CFLAGS"
LDFLAGS="$LDFLAGS $ARCH_LDFLAGS $BOARD_LDFLAGS"

AC_PROG_CC
AM_PROG_AS
AC_PROG_CC_C99
AC_PROG_CXX
AC_CHECK_TOOL([OBJCOPY], [objcopy], [:])

AC_OUTPUT(
    Makefile
    src/Makefile
)

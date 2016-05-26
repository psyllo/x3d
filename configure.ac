#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([x3d],[0.1],[psyllo@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
# AC_PROG_RANLIB
LT_INIT

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([sys/ipc.h])
AC_CHECK_HEADERS([sys/shm.h])
AC_CHECK_HEADERS([xcb/xcb_image.h])
AC_CHECK_HEADERS([xcb/shm.h])
AC_CHECK_HEADERS([xcb/xcb.h])


# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([XCB], [xcb >= 1.11])
PKG_CHECK_MODULES([XCB_SHM], [xcb-shm >= 1.11])
PKG_CHECK_MODULES([XCB_IMAGE], [xcb-image >= 0.4.0])

AX_PTHREAD

# Boost
AC_LANG_PUSH(C++)

# Set C++ standard
AX_CXX_COMPILE_STDCXX_14

AX_BOOST_BASE
#AX_BOOST_LOG_SETUP
AX_BOOST_LOG
AC_CHECK_HEADERS([boost/log/trivial.hpp])

AC_LANG_POP(C++)

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT

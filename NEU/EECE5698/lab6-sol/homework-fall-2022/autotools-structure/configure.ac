#
#  [2019] Signet Lab - Programming for ICT
#  All Rights Reserved.
#
#  Authors Filippo Campagnaro and Michele Polese 
#

AC_INIT(PFICT,1.0)
AM_INIT_AUTOMAKE 
AC_LANG(C++)
AC_PROG_CXX
AM_PROG_AR
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
LT_INIT
AC_CONFIG_MACRO_DIR([m4])
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL





#######################################################################

AC_DEFINE(CPP_NAMESPACE,std) 

AC_CHECK_LIB(pthread, pthread_create, [LIBS="$LIBS -lpthread"]) 

AC_ARG_WITH([test],
  AC_HELP_STRING([--with-test=VAL],
    [Test library enable]),
  [with_test="$withval"],
  [with_test=""])

PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/homework_1'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/socket_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_3_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_4_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_6_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/tcp_socket_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'$(GCC6_FLAG)'

PFICT_CXXFLAGS="$PFICT_CXXFLAGS "'-Wall'
PFICT_CXXFLAGS="$PFICT_CXXFLAGS "'-ggdb3'
PFICT_CXXFLAGS="$PFICT_CXXFLAGS "'-std=c++11'

PFICT_LIBADD="$PFICT_LIBADD"

PFICT_LDADD="$PFICT_LDADD $BUTILS_LDADD"

AM_CONDITIONAL(WITH_TEST, test "x${with_test}" != "x")

if test "x${with_test}" != "x"; then  
  AC_ARG_WITH_TEST
fi

AC_SUBST(PFICT_CPPFLAGS) 
AC_SUBST(PFICT_CXXFLAGS)
AC_SUBST(PFICT_LDFLAGS)
AC_SUBST(PFICT_LIBADD)
AC_SUBST(PFICT_LDADD)
AC_SUBST(BUTILS_LDADD)
AC_SUBST(top_srcdir)
AC_SUBST(with_test)

AC_CONFIG_FILES([
  Makefile
  m4/Makefile
  examples/homework_1/Makefile
  examples/socket_example/Makefile
  examples/lab_3_example/Makefile
  examples/lab_4_example/Makefile
  examples/lab_6_example/Makefile
  examples/tcp_socket_example/Makefile
  ])

AC_OUTPUT

dnl Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
dnl Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
dnl THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

dnl BITCOIN_SUBDIR_TO_INCLUDE([CPPFLAGS-VARIABLE-NAME],[SUBDIRECTORY-NAME],[HEADER-FILE])
dnl SUBDIRECTORY-NAME must end with a path separator
AC_DEFUN([BITCOIN_SUBDIR_TO_INCLUDE],[
  if test "x$2" = "x"; then
    AC_MSG_RESULT([default])
  else
    echo "#include <$2$3.h>" >conftest.cpp
    newinclpath=`${CXXCPP} ${CPPFLAGS} -M conftest.cpp 2>/dev/null | [ tr -d '\\n\\r\\\\' | sed -e 's/^.*[[:space:]:]\(\/[^[:space:]]*\)]$3[\.h[[:space:]].*$/\1/' -e t -e d`]
    AC_MSG_RESULT([${newinclpath}])
    if test "x${newinclpath}" != "x"; then
      eval "$1=\"\$$1\"' -I${newinclpath}'"
    fi
  fi
])

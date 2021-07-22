# yasplitt - splitting/merging/checksumming files
# Copyright (C) 2021  Pedro Henrique da Silva Palhares
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

AC_INIT([yasplitt], [0.1])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR(src/main.c)
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

if test "$ac_cv_prog_cc_c99" = "no" 
then
  AC_MSG_ERROR([Could not find a C99 capable compiler])
fi

AC_CHECK_LIB([sodium], [crypto_hash_sha256],[],[
                 AC_MSG_ERROR([You need to install libsodium.])
                 ])
AC_SEARCH_LIBS([log10], [m])


AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT

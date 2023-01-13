#!/usr/bin/env bash
#
#  [2019] Signet Lab - Programming for ICT
#
#  Authors Filippo Campagnaro and Michele Polese 
#

set -e

printHelp() {
cat << EOF

OPTIONS:
   -h    Show this message
   -p    Prefix Path
   -t    Test enable (1) or disable (0, default)
   -c    clean repository

   e.g. $0 -p <your_home> -t 1
EOF
}
TEST_UP=0
CLEAN=0
PREFIX=""

while getopts “hp:t:c” OPTION
do
    case $OPTION in
        h)
            printHelp
            exit 0
            ;;
        p)
            PREFIX=$OPTARG
            ;;
        t)
            TEST_UP=$OPTARG
            ;;
        c)
            CLEAN=1
            ;;
        ?)
            printHelp
            exit 0
            ;;
    esac
done

if [[ $CLEAN -eq 0 && -z $PREFIX ]];
then
    printHelp
    exit 0
fi

if [ $CLEAN -eq 1 ];
then
  make distclean
  exit 0
fi

./autogen.sh
if [ $TEST_UP -eq 1 ];
then
  ./configure --prefix $PREFIX --with-test=$TEST_UP
else
  ./configure --prefix $PREFIX
fi
make
if [ $TEST_UP -eq 1 ];
then
  make check
fi
make install
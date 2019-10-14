#!/bin/bash

# Allen Ma
# pass in a prefix of test file names
# this script runs valgrind against all the files


if [ $# != 1 ]; then
    echo "usage: ./memory_check.sh [testfile_prefix]"
    exit
fi

for f in $1*
do
    if [ ${f: -2} != ".c" ] && [ ${f: -2} != ".o" ]; then 
	valgrind --leak-check=full --error-exitcode=1 "./${f}" >& /dev/null
        RESVAL=$?
        # decide what to print based on the result
        if [ ${RESVAL} == 0 ] ; then
                        echo -e "Valgrind Success  : ${f}"
        else
                        echo -e "Valgrind Fail   : ${f}"
        fi
    fi
done

#!/bin/bash
prog_name=`grep "add_executable*" CMakeLists.txt | sed -e 's/.*(\(.*\)\ .*{.*}\ .*{.*}\ .*{.*}.*).*/\1/'`
exec=`cmake -DQWT_MATHML_LIBRARY=/usr/lib/libqwtmathml-qt5.so . && make`
param=`echo "$exec" | grep -o "\[100\%\]\ Built"`
[ "$param" ] && ./"$prog_name" "${1}" "${2}" "${3}" || echo "Error
" || echo "$exec"
exit 0

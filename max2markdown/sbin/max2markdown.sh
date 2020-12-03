#!/bin/bash
#
#   MaxText to Markdown
#   Copyright 2017, Daniel Robert Bradley. All rights reserved.
#   Distributed under the terms of the GPL License Version 3.
#

function usage()
{
    echo "Usage: max2md <max text file 1> [max text file 2]... > <markdown output file>"
    exit -1
}

function main()
{
    cat "$@" | sed 's|^\.\.\.\.|#####|g' \
             | sed 's|^\.\.\.|####|g'    \
             | sed 's|^\.\.|###|g'       \
             | sed 's|^\.|##|g'          \
             | sed 's|^--||g'            \
             | sed 's|^-|#|g'            \
             | sed 's|^\~!|```!|g'       \
             | sed 's|^\~|```|g'         \
             | sed 's|~||g'
}

if [ "$#" = "0" ]
then
    usage
else
    main "$@"
fi

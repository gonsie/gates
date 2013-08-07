#!/bin/bash

# parameter checking
if [ $# -ne 1 ]; then
    echo "Usage: `basename $0` location_of_current"
    exit 1
fi

if [ ! -e $1 ]; then
    echo $1 does not exist
    exit 1
fi

# make backups
if [ -e current/ ]; then
    if [ ! -e current/old/ ]; then
        mkdir current/old
    fi
    mv current/*.* current/old/
fi

# get current folder
cp -r $1/*.* ./current/

cp current/*.c ./
cp current/*.h ./

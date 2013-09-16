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
    mkdir tmp
    mv current/*.* tmp
    mv tmp current/old/bak-`date +%F-%H`
fi

# get current folder
cp -r $1/*.* ./current/

# update symbolic links
if [ ! -e library_types.h ]; then
    rm library_types.h
    ln -s current/*_types.h library_types.h
    rm library_functions.c
    ln -s current/*_functions.c library_functions.c
    rm library_lookups.c
    ln -s current/*_lookups.c library_lookups.c
fi

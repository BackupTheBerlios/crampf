#!/bin/sh
# This script creates a tar ball for easier distribution

VERSION=`sed -e '/^#define VERSION/{s/[^\"]*\"//;s/".*//;p;};d;' version_info.hh`
PROGNAME=`basename $(pwd)`
DISTNAME=$PROGNAME-$VERSION
ln -s . $DISTNAME
find $DISTNAME/ -name '*.hh' -or -name '*.cc' -or -name 'Makefile' \
        -or -name 'README.*' -or -name '*.sh' \
        | xargs tar -hvczf $DISTNAME.tar.gz 
rm -f $DISTNAME

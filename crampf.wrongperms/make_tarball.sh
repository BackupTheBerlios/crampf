#!/bin/sh
# This script creates a tar ball for easier distribution

VERSION=`sed -e '/^#define VERSION/{s/[^\"]*\"//;s/".*//;p;};d;' version_info.hh`
PROGNAME=`basename $(pwd)`
DISTNAME=$PROGNAME-$VERSION
ln -s . $DISTNAME
find $DISTNAME/ -name '*.hh' -or -name '*.cc' -or -name 'README*'\
	-or -name '*.sh' -or -name '*.in' -or -name 'configure' \
	-or -name 'install-sh' \
        | xargs tar -hvczf $DISTNAME.tar.gz 
rm -f $DISTNAME

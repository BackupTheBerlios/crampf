#!/bin/sh
# This script creates a tar ball for easier distribution

startpwd=$PWD
mkdir /tmp/crampf-build-$$
cd /tmp/crampf-build-$$
cvs -d /data/cvsroot co crampf
cd crampf
autoconf

VERSION=`sed -e '/^#define VERSION/{s/[^\"]*\"//;s/".*//;p;};d;' version_info.hh`
PROGNAME=`basename $(pwd)`
DISTNAME=$PROGNAME-$VERSION
ln -s . $DISTNAME
find $DISTNAME/ -name '*.hh' -or -name '*.cc' -or -name 'README*'\
	-or -name '*.sh' -or -name '*.in' -or -name 'configure' \
	-or -name 'install-sh' -or -name 'COPY*' -or -name 'TODO' \
	-or -name 'INSTALL*' -or -name 'crampfrc-example' \
        | xargs tar -hvczf $startpwd/$DISTNAME.tar.gz 
cd $startpwd
rm -rf /tmp/crampf-build-$$

#!/bin/bash

rm -f config.cache config.log
aclocal						|| exit 1
autoheader configure.in > config.h.in		|| exit 1
automake -a --foreign				|| exit 1
autoconf					|| exit 1
./configure					|| exit 1
make						|| exit 1

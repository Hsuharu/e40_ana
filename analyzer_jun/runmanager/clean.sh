#!/bin/sh


cd `dirname $0`

rm -rf tmp log stat
rm -f *~ \#*\# runlist/*~ runlist/\#*\#
rm -rf module/__pycache__
rm -f module/*.pyc

rm -rf dst/prefetch dst/log

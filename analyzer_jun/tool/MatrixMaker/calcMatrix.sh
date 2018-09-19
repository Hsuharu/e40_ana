#!/bin/sh
##
#  file: calcMatrix.sh
#  date: 2017.04.10
#
#

#_______________________________________________________________________________
work_dir=$(dirname $0)
bin_dir=$work_dir/bin

#_______________________________________________________________________________
if [ $# != 2 ]; then
    echo "Usage: $(basename $0) [MagnetParameter] [output filename]"
else
    ${bin_dir}/MatrixMaker $1
    ${bin_dir}/orbit <orbit/temp.in >$2
fi

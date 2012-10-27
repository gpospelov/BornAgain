#!/bin/bash
# function will try to locate a header [$1] in a directory list [$*]
# Usage: ./check_header.sh fftw3.h /opt/local/include /usr/include
# Program will return name of directory if it has given header

function usage()
{
  echo "check_header() -> Usage: ./check_header.sh fftw3.h /opt/local/include /usr/include"
  exit 1
}


function check_header()
{
  hdr=$1; shift
  hdrdirs="$*"
  #echo "check_header()"
  #echo $hdr
  #echo $hdrdirs
  for i in $hdrdirs; do
    #echo "checking " $i/$hdr
    if test -r $i/$hdr ; then
      echo $i
      exit 1
    fi
  done

}

#infoke usage() if no arguments is supplied
[[ $# -lt 2 ]] && usage


check_header $*



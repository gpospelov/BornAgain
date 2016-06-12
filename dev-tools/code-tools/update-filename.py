#!/usr/bin/env python3

# Automatically rewrite the Doxygen parameter @file in the headers of all given files

# Does not provide backup files:
# to be safe, work on fresh git commit, and use 'git stash' to revert.

import glob, re, sys

def edit( fn ):
    # print( "File " + fn )

    # read in
    fd = open( fn, 'r' )
    t = fd.read()
    fd.close

    t = re.sub( r'(//! @file).*', r'\1      '+fn[2:], t, re.M )

    # save result
    fd = open( fn, 'w' )
    fd.write( t )
    fd.close

## Main

flist = sys.argv[1:]
for fn in flist:
    edit( fn )

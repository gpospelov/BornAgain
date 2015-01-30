#!/usr/bin/env python3

# Automatic editing of collection of source files.
# Does not provide backup files:
# to be safe, work on fresh git commit, and use 'git stash' to revert.

import glob, re
from string import Template

def edit( fn ):
    print( "File " + fn )

    # read in
    fd = open( fn, 'r' )
    ti = fd.read()
    fd.close
    a = ti.split( '\n' )
    tf = ""

    # CHANGE THIS ACCORDING TO YOUR NEEDS
    p = re.compile( "@homepage  http://apps\.jcns\.fz-juelich\.de/BornAgain" )
    for l in a:
        tf += p.sub( '@homepage  http://bornagainproject.org', l, 1 ) + "\n"
    
    # save result
    fd = open( fn, 'w' )
    fd.write( tf.rstrip() )
    fd.close

## Main

fc  = glob.glob( '*/*.h' )
fc += glob.glob( '*/*.cpp' )

for fn in fc:
    edit( fn )

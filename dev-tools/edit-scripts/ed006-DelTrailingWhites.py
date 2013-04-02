#!/usr/bin/env python3

# Automatic editing of collection of source files.
# Does not provide backup files:
# to be safe, work on fresh git commit, and use 'git stash' to revert.

# ed4: correct link to homepage

import glob, re, argparse
from string import Template

def edit( fn ):
    print( "File " + fn )

    # read in
    fd = open( fn, 'r' )
    ti = fd.read()
    fd.close

    # the work is done here
    p = re.compile( "^(.*)(\s+)$" )
    a = ti.split( '\n' )
    tf = ""
    for l in a:
        tf += p.sub( r'\1', l, 1 ) + "\n"

    # save result
    fd = open( fn, 'w' )
    fd.write( tf )
    fd.close

## Main

fc  = glob.glob( 'Core/*/inc/*.h' )
fc += glob.glob( 'Core/*/src/*.cpp' )
fc += glob.glob( 'App/inc/*.h' )
fc += glob.glob( 'App/src/*.cpp' )

for fn in fc:
    if re.search( r"pypp\.(cpp|h|hpp)$", fn ):
        continue # don't reformat automatically generated file
    edit( fn )

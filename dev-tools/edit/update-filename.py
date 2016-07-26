#!/usr/bin/env python3

# Automatically rewrite the Doxygen parameter @file in the headers of all given files

# Does not provide backup files:
# to be safe, work on fresh git commit, and use 'git stash' to revert.

import glob, re, sys

def doit( fn ):
    global nchanged, nempty
    fn = re.sub( r'^\./', '', fn )
    # print( "File " + fn )

    # read in
    fd = open( fn, 'r' )
    ti = fd.read()
    fd.close

    if not re.search(  r'(//! @file      dev-tools/edit/update-filename.py
        print( "no '@file' in " + fn )
        nempty += 1
        return

    tf = re.sub( r'(//! @file      dev-tools/edit/update-filename.py

    if ti==tf:
        return

    nchanged += 1
    fd = open( fn, 'w' )
    fd.write( tf )
    fd.close

# main

if len(sys.argv)<=1:
    print("Usage: %s <source_files>" % sys.argv[0])
    sys.exit()

nempty   = 0
ncorrupt = 0
nchanged = 0

files = sys.argv[1:]
nfiles = len(files)

for i in range(nfiles):
    fn = files[i]
    # print( "SOIN - file %i/%i: %s" % ( i+1, len(files), fn ) )
    doit( fn )

print( "Summary:" )
print( "  number of files: %i" % nfiles )
print( "  w/o '@file':     %i" % nempty )
# print( "  nonstandard:     %i" % ncorrupt )
print( "  found in form:   %i" % (nfiles - nempty - ncorrupt - nchanged) )
print( "  changed:         %i" % nchanged )

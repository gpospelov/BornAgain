#!/usr/bin/env python3

"""
Renews file testlist.h in given unit test subdirectory.
This file just includes all other files from that directory.
"""

import fnmatch, glob, os, re, sys

def find(pattern, path):
    result = []
    for root, dirs, files in os.walk(path):
        for name in files:
            if fnmatch.fnmatch(name, pattern):
                result.append( name )
    return result

if( len(sys.argv)<=1 ):
    print( "Usage: %s <directories>" % sys.argv[0] )
    sys.exit(0)

filelist = []
for dir in sys.argv[1:]:
    filelist = find( '*.h', dir )
    fd = open( dir+"/testlist.h", "w" )
    fd.write( "// To renew this file, run %s <directory>\n\n" % sys.argv[0] )
    for fname in filelist:
        if fname=="testlist.h":
            continue
        fd.write( '#include "%s"\n' % fname )
    fd.close()

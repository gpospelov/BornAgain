#!/usr/bin/env python3

# Automatic editing of collection of source files.
# Does not provide backup files:
# to be safe, work on fresh git commit, and use 'git stash' to revert.

# ed3: rearrange header block since Doxygen requires @file to come first

import glob, re, argparse
from string import Template

headertemplate = Template ("""\
// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      $F
//! @brief     $B
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //
""" )

def edit( fn ):
    if re.search( r"pypp\.(cpp|h|hpp)$", fn ):
        return # don't reformat automatically generated file
    print( "File " + fn )

    fd = open( fn, 'r' )
    s = fd.read()
    fd.close

    a = s.split( '\n' )
    if not re.search( r'^\/\/ \*{66}', a[0] ):
        raise Expection( "unexpected line 0" )
    if not re.search( r'^\/\/  BornAgain', a[2] ):
        raise Expection( "unexpected line 2" )
    if not re.search( r'^\/\/ \*{66}', a[15] ):
        raise Expection( "unexpected line 15" )
    if not re.search( r'^\/\/ \*{66}', a[15] ):
        raise Expection( "unexpected line 15" )

    m=re.search( r'^\/\/\! \@file\s+(\S+)', a[12] )
    if not m:
        raise Expection( "unexpected line 12" )
    file = m.group(1)

    m=re.search( r'^\/\/\! \@brief\s+(.*)$', a[13] )
    if not m:
        raise Expection( "unexpected line 13" )
    brief = m.group(1)
    
    s = headertemplate.substitute( F=file, B=brief ) + '\n'.join(a[16:])

    fd = open( fn, 'w' )
    fd.write( s )
    fd.close

## Main

# parser = argparse.ArgumentParser()
# parser.add_argument( "subdirs" )
# subdirs = parser.parse_args().subdirs.split()
subdirs = [ 'Algorithms', 'Fitting', 'FormFactors', 'PythonAPI', 'Samples',
            'Tools' ]

dirs = []
for s in subdirs:
    dirs.append( '/home/jwu/BornAgain/Core/' + s + '/' )

for d in dirs:
    print( "Directory " + d )

    for fn in glob.glob( d + 'inc/*.h' ) + glob.glob( d + 'src/*.cpp' ):
        edit( fn )

#!/usr/bin/env python3

# Automatic editing of collection of source files.
# Does not provide backup files:
# to be safe, work on fresh git commit, and use 'git stash' to revert.

# ed5: insert copyright-header in directory App; remove old headers

import glob, re, argparse
from string import Template

headertemplate = Template ("""\
// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      $F 
//! @brief     $B
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

""")

def edit( fn ):
    if re.search( r"pypp\.(cpp|h|hpp)$", fn ):
        return # don't reformat automatically generated file
    print( "File " + fn )
    m = re.search( r"(\w+)/(src|inc)/(\w+)\.(cpp|h)$", fn )
    if not m:
        raise Exception( "could not split file name " + fn )
    subdir = m.group(1)
    base = m.group(3)
    ext = m.group(4)

    fd = open( fn, 'r' )
    s = fd.read()
    fd.close

    p = re.compile( "\/\/ \*\*\*.*\n\/\/ \* The BornAgain.*\n(.*\n){10}\/\/\! \@date.*\n" )
    s = p.sub( '', s, 1 )

    if   ext=='cpp':
        textB = "Implements class " + base + "." 
    elif ext=='h':
        textB = "Defines class " + base + "." 

    header = headertemplate.substitute( F=subdir+"/"+base+"."+ext, B=textB )
    s = header + s

    fd = open( fn, 'w', encoding='utf-8' )
    fd.write( s )
    fd.close

## Main

dirs = [ '/home/jwu/BornAgain/App/' ]

for d in dirs:
    print( "Directory " + d )

    for fn in glob.glob( d + 'inc/*.h' ) + glob.glob( d + 'src/*.cpp' ):
        edit( fn )

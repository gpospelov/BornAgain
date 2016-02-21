#!/usr/bin/env python

def help_short():
    print('Usage: ./codegenerator.py make|install|clean|help')

def help_long():
    print('''
C++ wrapper generator for exposing C++ libraries to Python.
''')
    help_short()
    print( '''
Options:
   make:    generate python boost wrapping code in ./output subdirectory
   install: install generated code to BornAgain/PythonAPI
   clean:   clean local directory
   help:    this help

Dependencies:
   - boost-python
   - Python2.7
   - gccxml (github.com/gccxml)
   - pygccxml (github.com/gccxml/pygccxml)
   - Py++ (https://bitbucket.org/ompl/pyplusplus)

Notes:
   - Run codegenerator.py in the directory where it resides.
   - More info at http://apps.jcns.fz-juelich.de/redmine/projects/bornagain/wiki/Python_bindings
''')


import sys
import os

import utils_build
import utils_install

import settings_core
import settings_fit

projects = [ settings_core, settings_fit ]

def main():
    if len(sys.argv)!=2:
        help_short()
        exit()

    if sys.argv[1] == 'make':
        for prj in projects:
            utils_build.MakePythonAPI(prj)
    elif sys.argv[1] == 'install':
        for prj in projects:
            utils_install.InstallCode(prj)
    elif sys.argv[1] == 'clean':
        clean = ["output", "cache_*.xml", "*~", "named_tuple.py", "*.pyc",
                 "exposed_decl.pypp.txt", "tmp.pypp.cpp"]
        for x in clean:
            os.system("rm -rf "+x)
    elif sys.argv[1] == 'help':
        help_long()
    else:
        help_short()


if __name__ == '__main__':
    main()

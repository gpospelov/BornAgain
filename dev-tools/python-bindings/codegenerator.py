#!/usr/bin/env python

def help_short():
    print('Usage: codegenerator.py make|install|clean|help')

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
   - gccxml (deb: libgccxml-dev; rpm: gccxml-devel)
   - pygccxml (deb: python-pygccxml; rpm: pygccxmlpy-pygccxml-devel)
   - Py++ (deb: python-py++; rpm: py27-pyplusplus-devel)
''')


import os
import sys
import glob

import MakePyCore
import MakePyFit
import InstallPyCore
import InstallPyFit


PyCoreTempDir='output/PyCore'
PyCoreInstallDir = '../../Core/PythonAPI'

PyFitTempDir='output/PyFit'
PyFitInstallDir = '../../Fit/PythonAPI'


def main():
    if len(sys.argv)!=2:
        help_short()
        sys.exit()

    if not os.path.exists(PyCoreTempDir): os.makedirs(PyCoreTempDir)
    if not os.path.exists(PyFitTempDir): os.makedirs(PyFitTempDir)
    
    if sys.argv[1] == 'make':
        MakePyCore.MakePythonAPI(PyCoreTempDir)
        MakePyFit.MakePythonAPI(PyFitTempDir)
    elif sys.argv[1] == 'install':
        InstallPyCore.InstallCode(PyCoreTempDir, PyCoreInstallDir)
        InstallPyFit.InstallCode(PyFitTempDir, PyFitInstallDir)
    elif sys.argv[1] == 'clean':
        clean = ["output", "cache_*.xml", "*~", "named_tuple.py", "*.pyc",
                 "exposed_decl.pypp.txt", "tmp.pypp.cpp"]
        for x in clean: os.system("rm -rf "+x)
    elif sys.argv[1] == 'help':
        help_long()
    else:
        help_short()


if __name__ == '__main__':
    main()


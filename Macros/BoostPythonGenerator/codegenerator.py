# c++ wrapper generator for exposing libScattCore to python
#
# Usage: 'python codegenerator.py make'  - to generate python-boost C++ wrappers
# Usage: 'python codegenerator.py install'  - to copy files into GISASFW/Core/PythonAPI directory
#
# requires boost, python27, py27-pyplusplus-devel, py-pygccxml-devel, gccxml-devel
#

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

#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
def main():
  if len(sys.argv)!=2:
    print "Usage: 'python codegenerator.py make' - generates python boost wrapping code in ./output subdirectory"
    print "Usage: 'python codegenerator.py install' - installs generated code to BornAgain/PythonAPI"
    print " "

  else:
    if not os.path.exists(PyCoreTempDir): os.makedirs(PyCoreTempDir)
    if not os.path.exists(PyFitTempDir): os.makedirs(PyFitTempDir)

    if sys.argv[1] == 'make':
      MakePyCore.MakePythonAPI(PyCoreTempDir)
      MakePyFit.MakePythonAPI(PyFitTempDir)
    elif sys.argv[1] == 'install':
      InstallPyCore.InstallCode(PyCoreTempDir, PyCoreInstallDir)
      InstallPyFit.InstallCode(PyFitTempDir, PyFitInstallDir)
    else:
      print "Nothing to do, run 'python codegenerator.py' to get help"


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()


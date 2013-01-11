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
import runpyplusplus
import runinstall


OutputTempDir='output'
InstallDir = '../../Core/PythonAPI'


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
def main():
  if len(sys.argv)!=2:
    print "Usage: 'python codegenerator.py make' - generates python boost wrapping code in ./output subdirectory"
    print "Usage: 'python codegenerator.py install' - installs generated code to GISASFW/PythonAPI"
    print " "

  else:
    if sys.argv[1] == 'make':
      runpyplusplus.RunPyPlusPlus(OutputTempDir)
    elif sys.argv[1] == 'install':
      runinstall.InstallCode(OutputTempDir, InstallDir)
    else:
      print "Nothing to do, run 'python codegenerator.py' to get help"


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()


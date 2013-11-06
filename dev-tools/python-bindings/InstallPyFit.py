# see codegenerator.py

import os
import sys
import glob
import difflib
import subprocess

import install_utils

#-------------------------------------------------------------
# generating python_module.pri for qt-creator
#-------------------------------------------------------------
def GenerateProjectFile(OutputTempDir, files_inc, files_src):
    python_pri_file = OutputTempDir+"/python_module.pri"
    fout = open(python_pri_file, 'w')
    fout.write("HEADERS +=  \\ \n")
    # existing files (written by human being)
    fout.write("    PythonAPI/inc/PythonFitExposer.h \\ \n")
    fout.write("    PythonAPI/inc/PythonFitList.h \\ \n")
    # automatically generated files
    for i_file in range(0,len(files_inc)):
        delim = " \\"
        if i_file == len(files_inc)-1:
            delim = " "
        ff = files_inc[i_file]
        ff = ff.replace(OutputTempDir,"PythonAPI/inc")
        fout.write("    "+ff+delim+"\n")
    fout.write("\n")
    fout.write("SOURCES +=  \\ \n")
    # existing files (written by human being)
    fout.write("    PythonAPI/src/PythonModule.cpp \\ \n")
    # automatically generated files
    for i_file in range(0,len(files_src)):
        delim = " \\"
        if i_file == len(files_src)-1:
            delim = " "
        ff = files_src[i_file]
        ff = ff.replace(OutputTempDir,"PythonAPI/src")
        fout.write("    "+ff+delim+"\n")
    fout.write("\n")

    fout.write("INCLUDEPATH += ./PythonAPI/inc \n")
    fout.write("DEPENDPATH  += ./PythonAPI/inc \n")
    fout.close()
    return python_pri_file


#-------------------------------------------------------------
# generating python module main cpp file
#-------------------------------------------------------------
def GenerateModuleFile(OutputTempDir, files_inc, files_src, PatternsToExclude):
    # generating own PythonModule.cpp
    python_module_file = OutputTempDir+"/PythonModule.cpp"
    fout = open(python_module_file, 'w')
    fout.write("#include \"Python.h\"\n")
    fout.write("#include \"boost/python.hpp\"\n")
    fout.write("\n")
    #fout.write("#include \"PythonModule.h\"\n")
    for ff in files_inc:
        ff = ff.replace(OutputTempDir+"/","")
        fout.write("#include \""+ff+"\" \n")
    fout.write("\n")
    fout.write("BOOST_PYTHON_MODULE(libBornAgainFit){\n")
    fout.write("\n")

    # copying register lines from automaticaly generated module file to our manually generated
    old_python_module_file = OutputTempDir+"/PythonInterface.main.cpp"
    fin = open(old_python_module_file,'r')
    for line in fin:
        skip_this = False
        for pattern in PatternsToExclude:
          if pattern in line: 
            skip_this = True
            break
        if skip_this: continue
        if "register_" in line: fout.write(line)
    fin.close()
    fout.write("}\n")
    fout.close()
    return python_module_file

#------------------------------------------------------------------------------
# InstallCode()
#------------------------------------------------------------------------------
def InstallCode(OutputTempDir, InstallDir):
    print "Installing generated PythonCoreAPI into ", InstallDir
    if not os.path.exists(OutputTempDir): exit("No output directory '" + OutputTempDir+"'")
    if not os.path.exists(InstallDir): exit("No install directory '" + InstallDir+"'")

    # skipping files which are already included into Core library
    PatternsToExclude = ["vdouble1d_t", "vcomplex1d_t", "IObservable", "IObserver"]
    for pattern in PatternsToExclude:
      files2remove = glob.glob(OutputTempDir+"/"+pattern+".*")
      for ff in files2remove:
          print "...removing dublicated ",ff
          os.remove(ff)

    files_inc =glob.glob(OutputTempDir+"/*.pypp.h");
    files_inc+= glob.glob(OutputTempDir+"/__call_policies.pypp.hpp");
    files_src = glob.glob(OutputTempDir+"/*.pypp.cpp");
    files = files_inc+files_src

    python_pri_file = GenerateProjectFile(OutputTempDir, files_inc, files_src)
    files.append(python_pri_file)

    python_module_file = GenerateModuleFile(OutputTempDir, files_inc, files_src, PatternsToExclude)
    files.append(python_module_file)

    install_utils.PatchFiles(files)

    install_utils.CopyFiles(files, InstallDir)

    install_utils.ClearPythonAPI(files, InstallDir)
    print "Done"


#------------------------------------------------------------------------------
# main()
#------------------------------------------------------------------------------
if __name__ == '__main__':
    InstallCode("output/PyFit","../../Fit/PythonAPI")



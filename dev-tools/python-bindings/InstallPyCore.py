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
    fout.write("    PythonAPI/inc/PythonListConverter.h \\ \n")
    fout.write("    PythonAPI/inc/PythonModule.h \\ \n")
    fout.write("    PythonAPI/inc/PythonOutputData.h \\ \n")
    fout.write("    PythonAPI/inc/PythonCoreExposer.h \\ \n")
    fout.write("    PythonAPI/inc/PythonCoreList.h \\ \n")
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
    fout.write("    PythonAPI/src/PythonListConverter.cpp \\ \n")
    fout.write("    PythonAPI/src/PythonOutputData.cpp \\ \n")
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
def GenerateModuleFile(OutputTempDir, files_inc, files_src):
    # generating own PythonModule.cpp
    python_module_file = OutputTempDir+"/PythonModule.cpp"
    fout = open(python_module_file, 'w')
    fout.write("#include \"Python.h\"\n")
    fout.write("#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION \n")
    fout.write("#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY \n")
    fout.write("#include \"numpy/arrayobject.h\"\n")
    fout.write("// the order of 3 guys above is important\n")
    fout.write("\n")
    #fout.write("#include \"PythonModule.h\"\n")
    for ff in files_inc:
        ff = ff.replace(OutputTempDir+"/","")
        fout.write("#include \""+ff+"\" \n")
    fout.write("\n")
    fout.write("#include \"PythonListConverter.h\"\n")
    fout.write("\n")
    fout.write("BOOST_PYTHON_MODULE(libBornAgainCore){\n")
    fout.write("\n")

    # copying register lines from automaticaly generated module file to our manually generated
    old_python_module_file = OutputTempDir+"/PythonInterface.main.cpp"
    fin = open(old_python_module_file,'r')
    for line in fin:
        if "register_" in line:
            fout.write(line)
    fin.close()

    fout.write("\n")
    fout.write("    register_python2cpp_converters();\n")
    fout.write("\n")
    fout.write("    import_array();\n")
    fout.write("    /* IMPORTANT\n")
    fout.write("    this is initialisation function from C-API of python-numpy package. It has to be called once in the\n")
    fout.write("    initialisation section of the module (i.e. here), when module is going to use any of python numpy C-API.\n")
    fout.write("    Additional rule: when initialisation of the module, and functions that use python-numpy C-API are located in\n")
    fout.write("    different files (different compilation units) - and this is exactly our case - additional defines has\n")
    fout.write("    to be inserted before #include \"numpy/arrayobject.h\". See explanations\n")
    fout.write("    http://docs.scipy.org/doc/numpy/reference/c-api.array.html#import_array\n")
    fout.write("    */\n")
    fout.write("}\n")

    fout.close()
    return python_module_file

#------------------------------------------------------------------------------
# InstallCode()
#------------------------------------------------------------------------------
def InstallCode(OutputTempDir, InstallDir):
    print "Installing generated PythonFitAPI into ", InstallDir
    if not os.path.exists(OutputTempDir): exit("No output directory '" + OutputTempDir+"'")
    if not os.path.exists(InstallDir): exit("No install directory '" + InstallDir+"'")

    files_inc =glob.glob(OutputTempDir+"/*.pypp.h");
    files_inc+= glob.glob(OutputTempDir+"/__call_policies.pypp.hpp");
    files_inc+= glob.glob(OutputTempDir+"/__convenience.pypp.hpp");
    files_src = glob.glob(OutputTempDir+"/*.pypp.cpp");
    files = files_inc+files_src

    python_pri_file = GenerateProjectFile(OutputTempDir, files_inc, files_src)
    files.append(python_pri_file)

    python_module_file = GenerateModuleFile(OutputTempDir, files_inc, files_src)
    files.append(python_module_file)

    install_utils.PatchFiles(files)

    install_utils.CopyFiles(files, InstallDir)

    install_utils.ClearPythonAPI(files, InstallDir)
    print "Done"


#------------------------------------------------------------------------------
# main()
#------------------------------------------------------------------------------
if __name__ == '__main__':
    InstallCode("output/PyCore","../../Core/PythonAPI")



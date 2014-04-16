# common rules and utilities for PythonAPI installatin

import os
import sys
import glob
import difflib
import subprocess

# returns True if files are different or absent
def FilesAreDifferent(file1, file2):
    if not os.path.exists(file1) or not os.path.exists(file2):
        return True
    proc = subprocess.Popen(["diff "+file1+" "+file2], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    if len(out) or err!=None:
        return True
    return False


# return True if file contains given line
def FileContainsLine(file_name, myline):
    lines = open(file_name, 'r').readlines()
    for line in lines:
        if line == myline:
            return True
    return False


# return True if file contains given string
def FileContainsString(file_name, mystr):
    lines = open(file_name, 'r').readlines()
    for line in lines:
        if mystr in line:
            return True
    return False


#------------------------------------------------------------------------------
# patching generated files to get rid from boost compilation warnings
#------------------------------------------------------------------------------
def PatchFiles(files):
    n_patched_files = 0
    for ff in files:
        # check if file needs to be patched
        if FileContainsLine(ff, "#include \"Macros.h\"\n" ):
            # file was already patched
            continue

        has_boost_hpp = False
        has_boost_suite_hpp = False

        if FileContainsString(ff, "boost/python.hpp"): has_boost_hpp = True
        if FileContainsString(ff, "vector_indexing_suite.hpp"): has_boost_suite_hpp = True
        if not (has_boost_hpp or has_boost_suite_hpp): 
            continue

        # patch is required
        fin = file(ff,"r")
        fout = file("tmp.tmp","w")

        for line in fin:
            if "boost/python.hpp" in line:
                fout.write("#include \"Macros.h\"\n")
                fout.write("GCC_DIAG_OFF(unused-parameter);\n")
                fout.write("GCC_DIAG_OFF(missing-field-initializers);\n")
                fout.write("#include \"boost/python.hpp\"\n")
                if has_boost_suite_hpp: fout.write("#include \"boost/python/suite/indexing/vector_indexing_suite.hpp\"\n")
                fout.write("GCC_DIAG_ON(unused-parameter);\n")
                fout.write("GCC_DIAG_ON(missing-field-initializers);\n")
            elif "vector_indexing_suite.hpp" in line:
                continue
            else:
                fout.write(line)
        fout.close()
        fin.close()
        os.system("mv tmp.tmp "+ff)
        n_patched_files += 1
    print "PatchFiles()     :",n_patched_files, "files have been patched to get rid from compilation warnings"


#------------------------------------------------------------------------------
# copying modified files to the project directory
#------------------------------------------------------------------------------
def CopyFiles(files, InstallDir):
    copycommand='cp '
    # copying files
    n_copied_files = 0
    for f in files:
        fileName = os.path.basename(f)

        # different output directory for source and headers
        outputName=''
        if '.cpp' in fileName:
            outputName=InstallDir+"/src/"+fileName
        elif '.h' in fileName:
            outputName=InstallDir+"/inc/"+fileName
        elif '.pri' in fileName:
            outputName=InstallDir+"/../"+fileName

        filesAreDifferentOrAbsent = FilesAreDifferent(outputName,f)
        if filesAreDifferentOrAbsent:
            command = copycommand + f + " " + outputName
            #print command
            n_copied_files += 1
            os.system(command)

    print "CopyFiles()      :",n_copied_files,"files out of",len(files),"have been replaced in ",InstallDir


#------------------------------------------------------------------------------
# clear PythonCoreAPI from files remained from previous installation
#------------------------------------------------------------------------------
def ClearPythonAPI(files, InstallDir):
    old_files = glob.glob(InstallDir+"/inc/*.pypp.h")
    old_files += glob.glob(InstallDir+"/src/*.pypp.cpp")
    list_to_erase = []
    for oldf in old_files:
        old_base = os.path.basename(oldf)
        oldIsObsolete = True
        for newf in files:
            new_base = os.path.basename(newf)
            if old_base == new_base: oldIsObsolete = False
        if oldIsObsolete:
            list_to_erase.append(oldf)
    print "ClearPythonAPI() : erasing obsolete files in BornAgain source tree ", list_to_erase
    for x in list_to_erase:
        os.system("rm "+x)


def GenerateModuleFile(prj, files_inc, files_src):
    '''Generates Python module main cpp file.'''
    # generating own PythonModule.cpp
    python_module_file = prj.temp_dir+"/PythonModule.cpp"
    fout = open(python_module_file, 'w')
    fout.write('#include "Python.h"\n')
    fout.write('#include "boost/python.hpp"\n')

    if prj.with_Numpy:
        fout.write('''
// Numpy (the order of the following three lines is important):
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#include "numpy/arrayobject.h"
''')

    for ff in files_inc:
        ff = ff.replace(prj.temp_dir+"/", "")
        fout.write('#include "%s"\n' % (ff) )
    fout.write('\n')

    if prj.with_converter:
        fout.write('#include "PythonListConverter.h"\n\n')

    fout.write('BOOST_PYTHON_MODULE(%s){\n' % (prj.lib_name) )

    fout.write('    boost::python::docstring_options doc_options(true, true, false);\n\n')

    # copying register lines from automaticaly generated module file to our manually generated
    old_python_module_file = prj.temp_dir+"/PythonInterface.main.cpp"
    fin = open(old_python_module_file,'r')
    for line in fin:
        if any( pattern in line for pattern in prj.exclude_patterns ):
            continue
        if "register_" in line:
            fout.write(line)
    fin.close()

    if prj.with_converter:
        fout.write("\n")
        fout.write("    register_python2cpp_converters();\n\n")

    if prj.with_Numpy:
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


def InstallCode(prj ):
    '''Installs the code.'''
    print( "Installing generated Python API into %s" % (prj.install_dir) )

    for pattern in prj.exclude_patterns:
      files2remove = glob.glob(prj.temp_dir+"/"+pattern+".*")
      for ff in files2remove:
          print "...removing dublicated ",ff
          os.remove(ff)

    files_inc = glob.glob(prj.temp_dir+"/*.pypp.h");
    files_inc+= glob.glob(prj.temp_dir+"/__call_policies.pypp.hpp");
    files_inc+= glob.glob(prj.temp_dir+"/__convenience.pypp.hpp"); # needed for Core only
    files_src = glob.glob(prj.temp_dir+"/*.pypp.cpp");
    files = files_inc+files_src

    python_module_file = GenerateModuleFile(prj, files_inc, files_src)
    files.append(python_module_file)

    PatchFiles(files)

    CopyFiles(files, prj.install_dir)

    ClearPythonAPI(files, prj.install_dir)

    print "Done"

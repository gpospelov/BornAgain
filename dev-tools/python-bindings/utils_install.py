# common rules and utilities for PythonAPI installatin

import os, glob, re, shutil, subprocess

def FilesAreDifferent(file1, file2):
    '''Returns True if files are different or absent.'''

    if not os.path.exists(file1) or not os.path.exists(file2):
        return True
    proc = subprocess.Popen(["diff "+file1+" "+file2], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    if len(out) or err!=None:
        return True
    return False


def PatchFiles(files):
    '''Patches generated files to get rid from boost compilation warnings.'''

    n_patched_files = 0
    for ff in files:

        with open(ff, 'r') as fh:
            txt = fh.read()

        if '#include "Macros.h"' in txt:
            continue # file was already patched

        has_boost_suite_hpp = "vector_indexing_suite.hpp" in txt
        if not ( has_boost_suite_hpp or "boost/python.hpp" in txt ):
            continue

        # patch is required
        with open(ff,"r") as fin:
            with open("tmp.tmp","w") as fout:
                for line in fin:
                    if "boost/python.hpp" in line:

                        fout.write('''\
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
''')

                        if has_boost_suite_hpp:
                            fout.write('''\
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
''')
                            
                        fout.write('''\
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
''')
                    elif "vector_indexing_suite.hpp" in line:
                        continue
                    else:
                        fout.write(line)
        shutil.move("tmp.tmp", ff)
        n_patched_files += 1
    print("PatchFiles()     : %i files have been patched to get rid from compilation warnings" %
              (n_patched_files))


def CopyFiles(prj, files):
    '''Copies modified files to the project directory.'''

    n_copied_files = 0
    for f in files:
        fileName = os.path.basename(f)

        # different output directory for source and headers
        outputName=''
        if   re.search( r'\.c(pp)?$', fileName ):
            outputName = prj.install_src + "/" + fileName
        elif re.search( r'\.h(pp)?$', fileName ):
            outputName = prj.install_inc + "/" + fileName

        if FilesAreDifferent(outputName,f):
            shutil.copy( f, outputName )
            n_copied_files += 1

    print( "CopyFiles()      : %i files out of %i have been replaced." % ( n_copied_files, len(files) ) )


def ClearPythonAPI(prj, files):
    '''Clears API from files that remain from previous installation.'''

    old_files = glob.glob(prj.install_inc + "/*.pypp.h")   + \
                glob.glob(prj.install_inc + "/*.pypp.hpp") + \
                glob.glob(prj.install_src + "/*.pypp.c")   + \
                glob.glob(prj.install_src + "/*.pypp.cpp")
    list_to_erase = []
    for oldf in old_files:
        if not any( os.path.basename(newf)==os.path.basename(oldf) for newf in files ):
            list_to_erase.append(oldf)
    print("ClearPythonAPI() : erasing obsolete files in BornAgain source tree " % (list_to_erase))
    for x in list_to_erase:
        os.system("rm "+x)


def GenerateModuleFile(prj, files_inc, files_src, file_mod):
    '''Generates Python module main cpp file.'''

    fout = open(file_mod, 'w')
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
        fout.write('''\
    import_array();
    /* IMPORTANT
    this is initialisation function from C-API of python-numpy package. It has to be called once in the
    initialisation section of the module (i.e. here), when module is going to use any of python numpy C-API.
    Additional rule: when initialisation of the module, and functions that use python-numpy C-API are located in
    different files (different compilation units) - and this is exactly our case - additional defines has
    to be inserted before #include "numpy/arrayobject.h". See explanations
    http://docs.scipy.org/doc/numpy/reference/c-api.array.html#import_array
    */
''')

    fout.write("}\n")
    fout.close()


def InstallCode(prj ):
    '''Installs the code.'''

    print( "Installing generated Python API." )

    for pattern in prj.exclude_patterns:
        files2remove = glob.glob(prj.temp_dir+"/"+pattern+".*")
        print("...removing duplicated files %s" % " ".join(files2remove) )
        for ff in files2remove:
            os.remove(ff)

    files_inc = glob.glob(prj.temp_dir+"/*.pypp.h")   + \
                glob.glob(prj.temp_dir+"/*.pypp.hpp") + \
                glob.glob(prj.temp_dir+"/__call_policies.pypp.hpp") +\
                glob.glob(prj.temp_dir+"/__convenience.pypp.hpp")
    files_src = glob.glob(prj.temp_dir+"/*.pypp.c")   + \
                glob.glob(prj.temp_dir+"/*.pypp.cpp")
    file_mod  =           prj.temp_dir+"/PythonModule.cpp"

    GenerateModuleFile(prj, files_inc, files_src, file_mod)

    files = files_inc + files_src + [file_mod]

    PatchFiles(files)

    CopyFiles(prj, files)

    ClearPythonAPI(prj, files)

    print("Done")

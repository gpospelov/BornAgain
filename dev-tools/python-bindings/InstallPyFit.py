# see codegenerator.py

import glob

import install_utils


def GenerateModuleFile(OutputTempDir, libName,files_inc, files_src, PatternsToExclude,
                       withNumpy, withConverter):
    '''Generates Python module main cpp file.'''
    # generating own PythonModule.cpp
    python_module_file = OutputTempDir+"/PythonModule.cpp"
    fout = open(python_module_file, 'w')
    fout.write('#include "Python.h"\n')
    fout.write('#include "boost/python.hpp"\n')
    if withNumpy:
        fout.write('''
// Numpy [the order of the following three lines is important):
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#include "numpy/arrayobject.h"
''')
    for ff in files_inc:
        ff = ff.replace(OutputTempDir+"/", "")
        fout.write('#include "%s"\n' % (ff) )
    fout.write('\n')

    if withConverter:
        fout.write('#include "PythonListConverter.h"\n\n')

    fout.write('BOOST_PYTHON_MODULE(%s){\n' % (libName) )

    fout.write('    boost::python::docstring_options doc_options(true, true, false);\n\n')

    # copying register lines from automaticaly generated module file to our manually generated
    old_python_module_file = OutputTempDir+"/PythonInterface.main.cpp"
    fin = open(old_python_module_file,'r')
    for line in fin:
        skip_this = False
        for pattern in PatternsToExclude:
            if pattern in line: 
                skip_this = True
                break
        if skip_this:
            continue
        if "register_" in line:
            fout.write(line)
    fin.close()

    if withConverter:
        fout.write("\n")
        fout.write("    register_python2cpp_converters();\n\n")
    if withNumpy:
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


def InstallCode(OutputTempDir, InstallDir):
    '''Installs the code.'''
    print( "Installing generated Python API into %s" % (InstallDir) )

    PatternsToExclude = ["vdouble1d_t", "vcomplex1d_t", "IObservable",
                         "IObserver", "IParameterized"]

    for pattern in PatternsToExclude:
      files2remove = glob.glob(OutputTempDir+"/"+pattern+".*")
      for ff in files2remove:
          print "...removing dublicated ",ff
          os.remove(ff)

    files_inc =glob.glob(OutputTempDir+"/*.pypp.h");
    files_inc+= glob.glob(OutputTempDir+"/__call_policies.pypp.hpp");
    files_src = glob.glob(OutputTempDir+"/*.pypp.cpp");
    files = files_inc+files_src

    python_module_file = GenerateModuleFile(
        OutputTempDir, 'libBornAgainFit', files_inc, files_src, PatternsToExclude, False, False)
    files.append(python_module_file)

    install_utils.PatchFiles(files)

    install_utils.CopyFiles(files, InstallDir)

    install_utils.ClearPythonAPI(files, InstallDir)
    print "Done"


# see codegenerator.py

import glob
import builder_utils
import install_utils


def InstallCode(mp, OutputTempDir, InstallDir):
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

    python_module_file = builder_utils.GenerateModuleFile(
        mp, OutputTempDir, 'libBornAgainFit', files_inc, files_src,
        PatternsToExclude, False, False)
    files.append(python_module_file)

    install_utils.PatchFiles(files)

    install_utils.CopyFiles(files, InstallDir)

    install_utils.ClearPythonAPI(files, InstallDir)
    print "Done"


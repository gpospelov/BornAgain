# see codegenerator.py

import glob, os
import builder_utils
import install_utils


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

    python_module_file = builder_utils.GenerateModuleFile(
        prj, 'libBornAgainCore', files_inc, files_src)
    files.append(python_module_file)

    install_utils.PatchFiles(files)

    install_utils.CopyFiles(files, prj.install_dir)

    install_utils.ClearPythonAPI(files, prj.install_dir)
    print "Done"


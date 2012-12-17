# patch py++ generated files to get rid from compilation warnings
#
# replace #include "boost/python.hpp" 
# with
# include "Macros.h"
# GCC_DIAG_OFF(unused-parameter);
# GCC_DIAG_OFF(missing-field-initializers);
# include "boost/python.hpp"
# GCC_DIAG_ON(unused-parameter);
# GCC_DIAG_ON(missing-field-initializers);

import os
import sys
import glob


OutputTempDir = "./output"
files =glob.glob(OutputTempDir+"/*.*");
print files


for ff in files:
    print ff
    fin = file(ff,"r")
    fout = file("tmp.tmp","w")
    for line in fin:
        if "boost/python.hpp" in line:
            fout.write("#include \"Macros.h\"\n")
            fout.write("GCC_DIAG_OFF(unused-parameter);\n")
            fout.write("GCC_DIAG_OFF(missing-field-initializers);\n")
            fout.write("#include \"boost/python.hpp\"\n")
            fout.write("#include \"boost/python/suite/indexing/vector_indexing_suite.hpp\"\n")
            fout.write("GCC_DIAG_ON(unused-parameter);\n")
            fout.write("GCC_DIAG_ON(missing-field-initializers);\n")
        elif "vector_indexing_suite.hpp" in line:
            continue
        else:
            fout.write(line)
    fout.close()
    fin.close()
    os.system("mv tmp.tmp "+ff)

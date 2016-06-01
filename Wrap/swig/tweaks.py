# this script is used to manually tweak swig-generated wrapper

from __future__ import print_function
import sys
import os
import string

# compatibility with windows filename conventions
def windowsify(filename):
    if ( sys.platform == "win32" ):
        new_filename = filename.replace("/", "\\")
    else:
        new_filename = filename

    return os.path.abspath(new_filename)

if len(sys.argv) != 3:
    print("Usage: tweaks.py inputfile outputfile")
    exit(1)

in_name = windowsify(sys.argv[1])
out_name = windowsify(sys.argv[2])
tmp_name = in_name + ".tmp"

print("tweaks.py:", in_name, out_name, tmp_name)

# we use a temp file because output could be same as input
in_file = open(in_name, "r")
tmp_file = open(tmp_name, "w") 


# now loop over each line of f, making modification as necessary
for line in in_file:
    line = line.replace("_libBornAgainCore.ICloneable_transferToCPP(self)", "self.__disown__()")
    line = line.replace("_libBornAgainCore.Histogram1D_getBinCenters(self)", "self.getBinCentersNumpy()")
    line = line.replace("_libBornAgainCore.Histogram1D_getBinErrors(self)", "self.getBinErrorsNumpy()")
    line = line.replace("_libBornAgainCore.Histogram1D_getBinValues(self)", "self.getBinValuesNumpy()")
    tmp_file.write(line)

# done the search/replace
in_file.close()
tmp_file.close()

# have to check this for correct behaviour
if ( out_name == in_name):
    os.remove(in_name)
    
# rename tmp file to output file
os.rename(tmp_name, out_name)

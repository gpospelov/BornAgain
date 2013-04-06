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


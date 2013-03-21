# see codegenerator.py

import os
import sys
import glob


#-------------------------------------------------------------
# generating python_module.pri for qt-creator
#-------------------------------------------------------------
def GenerateProjectFile(OutputTempDir, files_inc, files_src):
  python_pri_file = OutputTempDir+"/python_module.pri"
  fout = open(python_pri_file, 'w')
  fout.write("HEADERS +=  \\ \n")
  # existing files (written by human being)
  fout.write("    PythonAPI/inc/PythonPlusplusFitHelper.h \\ \n")
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

  fout.write("INCLUDEPATH += $$PWD/PythonAPI/inc \n")
  fout.write("DEPENDPATH  += $$PWD/PythonAPI/inc \n")
  fout.write("\n")
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
      if "register_" in line:
          fout.write(line)
  fin.close()

  fout.write("}\n")

  fout.close()
  return python_module_file


#-------------------------------------------------------------
# patching generated files to get rid warnings from boost
#-------------------------------------------------------------
def PatchFiles(files):
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


#-------------------------------------------------------------
# copying files to the project directory
#-------------------------------------------------------------
def CopyFiles(files, InstallDir):
  copycommand='cp '
  # copying files
  overwriteAnswer=''
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
    #print "XXX",f, outputName

    # check file existance
    if os.path.exists(outputName) and overwriteAnswer != 'a':
      prompt="File '"+outputName+"' exists, Overwrite? [y/a/n] "
      overwriteAnswer=raw_input(prompt)

    if (overwriteAnswer == 'y' or overwriteAnswer=='a') or not os.path.exists(outputName):
      command = copycommand + f + " " + outputName
      print command
      os.system(command)

    else:
      continue


#-------------------------------------------------------------
# InstallCode()
#-------------------------------------------------------------
def InstallCode(OutputTempDir, InstallDir):
  if not os.path.exists(OutputTempDir): exit("No output directory '" + OutputTempDir+"'")
  if not os.path.exists(InstallDir): exit("No install directory '" + InstallDir+"'")

  # special list of files which has to be excluded, since they are exposed already in libBornAgainCore
  #FilesToExclude=["vdouble1d_t"]
  #for fname in FilesToExclude:
    #files_inc = filter(lambda x: not fname in x, files_inc)
    #files_src = filter(lambda x: not fname in x, files_src)
  PatternsToExclude = ["vdouble1d_t"]
  for pattern in PatternsToExclude:
    files2remove = glob.glob(OutputTempDir+"/"+pattern+".*")
    for ff in files2remove:
        print "...removing unnecessary ",ff
        os.remove(ff)

  files_inc =glob.glob(OutputTempDir+"/*.pypp.h");
  files_inc+= glob.glob(OutputTempDir+"/__call_policies.pypp.hpp");
  files_src = glob.glob(OutputTempDir+"/*.pypp.cpp");

  files = files_inc+files_src

  python_pri_file = GenerateProjectFile(OutputTempDir, files_inc, files_src)
  files.append(python_pri_file)

  python_module_file = GenerateModuleFile(OutputTempDir, files_inc, files_src, PatternsToExclude)
  files.append(python_module_file)

  PatchFiles(files)

  CopyFiles(files, InstallDir)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  InstallCode("output/PyFit","../../Fit/PythonAPI")




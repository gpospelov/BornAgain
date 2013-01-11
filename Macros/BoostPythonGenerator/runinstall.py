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
  fout.write("    PythonAPI/inc/PythonListConverter.h \\ \n")
  fout.write("    PythonAPI/inc/PythonModule.h \\ \n")
  fout.write("    PythonAPI/inc/PythonOutputData.h \\ \n")
  fout.write("    PythonAPI/inc/PythonPlusplusHelper.h \\ \n")
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
  fout.write("    PythonAPI/src/PythonPlusplusHelper.cpp \\ \n")
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
  fout.write("#define PY_ARRAY_UNIQUE_SYMBOL scatt_ARRAY_API \n")
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
  fout.write("BOOST_PYTHON_MODULE(libScattCore){\n")
  fout.write("\n")
  # adding register lines
  #for ff in files_inc:
    #fout2 = open(ff,'r')
    #for line in fout2:
      #if "register_" in line:
        #line = line.replace("void ","    ")
        #fout.write(line)

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
  files_inc =glob.glob(OutputTempDir+"/*.pypp.h");
  files_inc+= glob.glob(OutputTempDir+"/__call_policies.pypp.hpp");
  files_src = glob.glob(OutputTempDir+"/*.pypp.cpp");
  files = files_inc+files_src

  python_pri_file = GenerateProjectFile(OutputTempDir, files_inc, files_src)
  files.append(python_pri_file)

  python_module_file = GenerateModuleFile(OutputTempDir, files_inc, files_src)
  files.append(python_module_file)

  PatchFiles(files)

  CopyFiles(files, InstallDir)




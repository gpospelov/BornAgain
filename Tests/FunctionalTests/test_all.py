# run C++/Python functional tests for BornAgain libraries
# C++ will be compiled automatically
# Usage:
# 'python test_all.py' - to run all tests
# 'python test_all.py C++' - to run C++ tests only
# 'python test_all.py Python' - to run Python tests only

import os
import sys
import glob



def run_command(command):
  p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  p.wait()
  return iter(p.stdout.readline, b''), iter(p.stderr.readline, b'')


#-------------------------------------------------------------
# run C++ functional tests
#-------------------------------------------------------------
def runCppTests():
  sys.path.insert(0, './TestCore')
  import TestCore
  sys.path.insert(0, './TestFit')
  import TestFit
  #make compilation
  print "Compiling C++ functional tests"
  os.system("cd TestCore; qmake; make")
  os.system("cd TestFit; qmake; make")
  #command = "cd TestCore; qmake; make"
  #command = "cd TestFit; qmake; make"
  #stdout, stderr = run_command(command)
  #stdout, stderr = run_command(command)
  summary = TestCore.runTests()
  summary += TestFit.runTests()
  return summary

#-------------------------------------------------------------
# clean C++ functional tests
#-------------------------------------------------------------
def cleanTests():
  #make compilation
  print "Cleaning..."
  os.system("cd TestCore; make distclean")
  os.system("cd TestFit; make disclean")


#-------------------------------------------------------------
# run python functional tests
#-------------------------------------------------------------
def runPythonTests():
  sys.path.insert(0, './TestPyCore')
  import TestPyCore
  sys.path.insert(0, './TestPyFit')
  import TestPyFit
  summary = TestPyCore.runTests()
  summary += TestPyFit.runTests()
  return summary


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
def main():
  run_python_tests = True
  run_cpp_tests = True
  if len(sys.argv) >2:
    print "Usage:"
    print "'python test_all.py' - to run all tests"
    print "'python test_all.py C++' - to run C++ tests only"
    print "'python test_all.py Python' - to run Python tests only"
    exit()
  elif len(sys.argv) == 2:
    if "C++" in sys.argv[1]: run_python_tests = False
    if "Python" in sys.argv[1]: run_cpp_tests = False
    if "clean" in sys.argv[1]:
      cleanTests();
      exit()

  summary  = "\n"
  summary += "Functional Tests Summary -->\n"
  if run_cpp_tests: summary += runCppTests()
  if run_python_tests: summary += runPythonTests()
  print summary


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()


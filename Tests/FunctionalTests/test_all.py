# run C++/Python functional tests for BornAgain libraries
#
# Usage:
# 'python test_all.py' - to run all tests
# 'python test_all.py C++' - to run C++ tests only
# 'python test_all.py Python' - to run Python tests only

import os
import sys
import glob


sys.path.insert(0, './TestPyCore')
import TestPyCore
sys.path.insert(0, './TestCore')
import TestCore


#-------------------------------------------------------------
# run python functional tests
#-------------------------------------------------------------
def runPythonTests():
  summary = TestPyCore.runTests()
  return summary


#-------------------------------------------------------------
# run C++ functional tests
#-------------------------------------------------------------
def runCppTests():
  summary = TestCore.runTests()
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
  print run_python_tests, run_cpp_tests

  summary  = "\n"
  summary += "Functional Tests Summary -->\n"
  if run_python_tests: summary += runPythonTests()
  if run_cpp_tests: summary += runCppTests()
  print summary


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()


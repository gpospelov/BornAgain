# Run C++ core tests for libBornAgainCore library
# Usage: python test_all.py
import sys
import os
import subprocess
import time
import platform


Tests = [
  "IsGISAXS01",
  "IsGISAXS02",
  "IsGISAXS03",
  "IsGISAXS04",
  "IsGISAXS06",
  "IsGISAXS07",
  "IsGISAXS08",
  "IsGISAXS09",
  "IsGISAXS10",
  "IsGISAXS11",
  "IsGISAXS15",
  "MesoCrystal1",
]

test_info = []

# run system command and catch multiline stdout and stderr
def run_command(command):
  p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell = True)
  
  p.wait()
  return iter(p.stdout.readline, b''), iter(p.stderr.readline, b'')


# parse stdout, stderr for test description and test result
def parse_output(testName, stdout, stderr):
  # normally the message from test looks like "IsGISAXS01 Mixture of cylinders and prisms [OK]"
  # we want to find status (FAILED or OK) and extract description "Mixture of cylinders and prisms"
  status="OK"
  for line in stderr:
    status="FAILED" # test failed, if there are some non empty stderr messages
  descr=""
  for line in stdout:
    if testName in line:
      if "FAILED" in line: status="FAILED"
      descr=line.strip(testName).strip("\n")
      descr=descr.strip("[OK]")
      descr=descr.strip("[FAILED]")

  descr = descr[:55]
  descr = descr.ljust(55).lstrip()

  return descr, status


# run tests one by one
def runTests():
  print ">>> Running TestCore, {0:-2d} tests total ...".format(len(Tests))
  for testName in Tests:
    command =  testName+"/"+testName # i.e. "path/executable" like "IsGISAXS01/IsGISAXS01"
    if "Windows" in platform.system(): command =  testName+"\\"+testName+".exe"
    path = os.path.split(__file__)[0]
    if path: command = os.path.join(path, command)
    print "Running test ", testName
    start_time = time.time()
    stdout, stderr = run_command(command)
    total_time = time.time() - start_time
    descr, status = parse_output(testName, stdout, stderr)
    test_info.append((testName, descr, total_time, status))
  return getSummary()


# making summary
def getSummary():
  summary  = "--------------------------------------------------------------------------------\n"
  summary += "Functional Tests of libBornAgainCore (C++)                                      \n"
  summary += "--------------------------------------------------------------------------------\n"
  n=1
  for x in test_info:
    if(x[2] < 10):
        summary += '{0:2d}. {1:<13} {2:.51s}  {3:.2f} [{4}] '.format(n, x[0],x[1],x[2],x[3]) + "\n"
    else:
        summary += '{0:2d}. {1:<13} {2:.51s} {3:.2f} [{4}] '.format(n, x[0],x[1],x[2],x[3]) + "\n"
    n+=1
  return summary


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  summary = runTests()
  print summary


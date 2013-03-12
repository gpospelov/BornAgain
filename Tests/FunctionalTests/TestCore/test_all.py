#
import sys
import os
import subprocess
import time

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
    "IsGISAXS15"
]

test_info = []

# run system command and catch multiline stdout and stderr
def run_command(command):
    p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
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
            if "FAILED" in line:
                status="FAILED"
            descr=line.strip(testName).strip("\n")
            descr=descr.strip("[OK]")
            descr=descr.strip("[FAILED]")

    descr = descr[:55]
    descr = descr.ljust(55)
    return descr, status


# run tests one by one
def runTests():
    for testName in Tests:
        command = testName+"/"+testName # i.e. "path/executable" like "IsGISAXS01/IsGISAXS01"
        print "Running test ", testName
        start_time = time.time()
        stdout, stderr = run_command(command)
        total_time = time.time() - start_time
        descr, status = parse_output(testName, stdout, stderr)
        test_info.append((testName, descr, total_time, status))

# print test results
def printResults():
    print "========================================"
    n=1
    for x in test_info:
        print '{0:2d}. {1}  {2}  {3:.3f}sec  [{4}] '.format(n, x[0],x[1],x[2],x[3])
        n+=1

#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    runTests()
    printResults()

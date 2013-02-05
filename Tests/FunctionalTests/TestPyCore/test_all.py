# run all tests

import sys
import os
import subprocess
import time

import isgisaxs01


Tests = {
    "IsGISAXS01": isgisaxs01.RunTest,
    "IsGISAXS02": isgisaxs01.RunTest
}

test_info = []

# parse stdout, stderr for test description and test result
def parse_output(testName, test_result):
    # normally the message from test looks like "IsGISAXS01 Mixture of cylinders and prisms [OK]"
    # we want to find status (FAILED or OK) and extract description "Mixture of cylinders and prisms"
    status="OK"
    descr=""
    if testName in test_result:
        if "FAILED" in test_result:
            status="FAILED"
        descr=test_result.strip(testName).strip("\n")
        descr=descr.strip("[OK]")
        descr=descr.strip("[FAILED]")
    else:
       descr = "Can't parse the description"
    descr = descr[:55]
    descr = descr.ljust(55)
    return descr, status


# run tests one by one
def runTests():
    for testName in Tests:
        print "Running test ", testName
        start_time = time.time()
        result = Tests[testName]()
        total_time = time.time() - start_time
        descr, status = parse_output(testName, result)
        test_info.append((testName, descr, total_time, status))


# print test results
def printResults():
    print "========================================"
    n=1
    for x in test_info:
        print '{0}. {1}  {2}  {3:.3f}sec  [{4}] '.format(n, x[0],x[1],x[2],x[3])
        n+=1


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    runTests()
    printResults()

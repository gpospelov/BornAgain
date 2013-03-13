# run all tests

import sys
import os
import subprocess
import time

import isgisaxs01
import isgisaxs02
import isgisaxs03
import isgisaxs04
import isgisaxs06
import isgisaxs07
import isgisaxs08
import isgisaxs09
import isgisaxs10
import isgisaxs11
import isgisaxs15

Tests = {
    "IsGISAXS01": isgisaxs01.RunTest,
    "IsGISAXS02": isgisaxs02.RunTest,
    "IsGISAXS03": isgisaxs03.RunTest,
    "IsGISAXS04": isgisaxs04.RunTest,
    "IsGISAXS06": isgisaxs06.RunTest,
    "IsGISAXS07": isgisaxs07.RunTest,
    "IsGISAXS08": isgisaxs08.RunTest,
    "IsGISAXS09": isgisaxs09.RunTest,
    "IsGISAXS10": isgisaxs10.RunTest,
    "IsGISAXS11": isgisaxs11.RunTest,
    "IsGISAXS15": isgisaxs15.RunTest
}

test_info = []

# parse stdout, stderr for test description and test result
def parse_output(testName, test_result):
    # normally the message from test looks like "IsGISAXS01 Mixture of cylinders and prisms [OK]"
    # we want to find status (FAILED or OK) and extract description "Mixture of cylinders and prisms"
    status="OK"
    descr=""
    if testName in test_result:
        descr = test_result[1]
        status = test_result[2]
    else:
       descr = "Can't parse the description"
    descr = descr[:55]
    descr = descr.ljust(55)
    return descr, status


# run tests one by one
def runTests():
    for testName in sorted(Tests.iterkeys()):
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
        print '{0:2d}. {1}  {2}  {3:.3f}sec  [{4}] '.format(n, x[0],x[1],x[2],x[3])
        n+=1


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    runTests()
    printResults()

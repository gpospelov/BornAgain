#!/usr/bin/env python
# return current number of lines of code ('loc') in GISASFW projects
#
# should be executed either from parent directory
# "python Macros/GitUtils/git_loc_current.py"
# or from local one
# "python git_loc_current.py ../.."

from os import popen, system
import os
import getopt
from sys import argv,stderr,stdout
#from subprocess import Popen, PIPE, STDOUT


contains = [".py",".h",".cpp", ".pro" ]
notcontains = ["ThirdParty", "Doc"]

projects= {"App" : 0, "Core" : 0, "PythonAPI" : 0, "Geometry" : 0}


# command line options: path to main git directory
opts, args = getopt.getopt(argv[1:],None)
extfolder = False
if len(args) == 1:
    extfolder = True
    targetfolder = args[0]

prevfolder = os.getcwd()
if extfolder:
    os.chdir(targetfolder)

# loop over files in git repository
nTotalLines=0;
for x in popen("git ls-files"):
  # check if file name contains required patterns
  x_in_contains=False
  for c in contains:
    if c in x:
      x_in_contains=True

  # check if file contains non-desired patterns
  x_in_notcontains=False
  for c in notcontains:
    if c in x:
      x_in_notcontains=True

  # check if file contains desired patterns and doesn't contain non-desired
  if x_in_contains and not x_in_notcontains:
    print x.strip()
    p = popen("wc -l "+x)
    nl = p.readline().split()[0]
    p.close()
    # total number of lines in project
    nTotalLines += int(nl)
    # number of lines corresponding to additional patterns
    for p in projects:
      if p in x:
        projects[p]+=int(nl)

# output of results
print "---"
print "Total number of lines of code in GISASFW:", nTotalLines
print "Number of lines in sub projects", projects

os.chdir(prevfolder)

#!/usr/bin/env python
# return current number of lines of code ('loc') in GISASFW projects
#
# should be executed either from parent directory
# "python Macros/GitUtils/git_loc_current.py"
# or from local one
# "python git_loc_current.py ../.."

from os import popen, system
from subprocess import Popen, PIPE, STDOUT


contains = [".py",".h",".cpp", ".pro" ]
notcontains = ["ThirdParty", "Doc"]

projects= {"App" : 0, "Core" : 0, "PythonAPI" : 0, "Geometry" : 0}

nTotalLines=0;
for x in popen("git ls-files"):
  # check if file name contains required
  x_in_contains=False
  for c in contains:
    if c in x:
      x_in_contains=True

  x_in_notcontains=False
  for c in notcontains:
    if c in x:
      x_in_notcontains=True

  if x_in_contains and not x_in_notcontains:
    print x.strip()
    p = popen("wc -l "+x)
    nl = p.readline().split()[0]
    nTotalLines += int(nl)
    p.close()
    for p in projects:
      if p in x:
        projects[p]+=int(nl)

# output of results
print "---"
print "Total number of lines of code in GISASFW:", nTotalLines
print "Number of lines in sub projects", projects


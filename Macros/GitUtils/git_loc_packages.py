#!/usr/bin/env python

# calculate number of lines of code in GISASFW project as a function of time
#
# should be executed either from parent directory
# "python Macros/GitUtils/git_loc_history.py"
# or from local one
# "python git_loc_history ../.."
#
# based on 'git-loc' from from https://github.com/ITikhonov/git-loc
#
# ROOT graphics added
# see http://root.cern.ch/drupal/content/how-use-use-python-pyroot-interpreter

import re
from email.utils import parsedate
from time import mktime
from datetime import datetime
from os import popen
import os
from sys import argv,stderr,stdout
import getopt
from array import array

opts, args = getopt.getopt(argv[1:],None)
extfolder = False
if len(args) == 1:
    extfolder = True
    targetfolder = args[0]


fc=0
locs=0
locs_type=[0,0,0,0,0,0,0,0,0]
#       0      1                  2            3      4        5      6     7       8
descr=["Core","Functional Tests","Unit Tests","*.py","macros","GUI", "PyAPI","Third","Undef"]
adds=None
cmt=None
prev_time = datetime(2000,1,1)

history=[]

def pop():
    if adds is not None:
        pstr="%s %8u %5s %5s %7s %s \t%s"%(d,locs,'+'+str(adds),'-'+str(dels),hsh,who,cmt.strip())
        print pstr
        atmp = []
        for x in locs_type:
            atmp.append(x)
        history.append((d,locs,atmp,adds,dels,hsh,who,cmt))

def filetype(x):
    file_type=8
    if "/Core/Algorithms/" in x and (".h" in x or ".cpp" in x):
        file_type = 0
    elif "/Core/FormFactors/" in x and (".h" in x or ".cpp" in x):
        file_type = 0
    elif "/Core/Geometry/" in x and (".h" in x or ".cpp" in x):
        file_type = 0
    elif "/Core/Samples/" in x and (".h" in x or ".cpp" in x):
        file_type = 0
    elif "/Core/Tools/" in x and (".h" in x or ".cpp" in x):
        file_type = 0
    if "/Core/Fitting/" in x and (".h" in x or ".cpp" in x):
        file_type = 0
    elif "/Core/inc/" in x and (".h" in x):
        file_type = 0
    elif "/Core/src/" in x and (".cpp" in x):
        file_type = 0
    elif "/App/" in x and (".h" in x or ".cpp" in x):
        file_type = 1
    elif "/Tests/FunctionalTests/TestCore" in x and (".h" in x or ".cpp" in x):
        file_type = 1
    elif "/UnitTests/" in x and (".h" in x or ".cpp" in x):
        file_type = 2
    elif "/Tests/UnitTests/TestCore/" in x and (".h" in x or ".cpp" in x):
        file_type = 2
    elif ".py" in x and not "ThirdParty" in x and not "Core/PythonAPI" in x:
        print x
        file_type = 3
    elif ".C" in x or ".pro" in x or ".pri" in x or "*.sh" in x and not "ThirdParty" in x and not "pro.user" in x:
        file_type = 4
    elif "/GUI/coregui" in x and (".h" in x or ".cpp" in x) and not "widgetbox" in x:
        file_type = 5
    elif "/AppGUI/coregui" in x and (".h" in x or ".cpp" in x):
        file_type = 5
    elif "/BASuite" in x and (".h" in x or ".cpp" in x):
        file_type = 5
    elif "Core/PythonAPI" in x and (".h" in x or ".cpp" in x):
        file_type = 6
    elif "ThirdParty" in x:
        file_type = 7
    return file_type

prevfolder = os.getcwd()
if extfolder:
    os.chdir(targetfolder)

# parsing output of git log 
file_type_ppp = 8
file_type_mmm = 8
for x in popen('git log develop --reverse -p'):
    if x.startswith('commit'):
        pop()
        hsh=x[7:14];
    if x.startswith('Author'):
        who=x.replace("Author: ",'').replace('\n','');
        who=re.sub(">.*","",who);
        who=re.sub(".*<","",who);
    if x.startswith('Date'):
        fc=1
        d=datetime(*parsedate(x[5:])[:7])
        t=mktime(parsedate(x[5:]))
        adds=0
        dels=0
    if fc==2:
        cmt=x[:-1]
        fc=0
    if fc==1:
        if len(x)==1: fc=2
    if x.startswith('+++'):
        file_type_ppp = filetype(x)

    if x.startswith('---'):
        file_type_mmm = filetype(x)

    if x.startswith('+') and not x.startswith('+++'):
        locs_type[file_type_ppp] += 1
        if file_type_ppp <6:
            adds+=1
            locs+=1
    if x.startswith('-') and not x.startswith('---'):
        locs_type[file_type_mmm] -= 1
        if file_type_mmm <6:
            dels+=1
            locs-=1

pop()
os.chdir(prevfolder)


# --------------------------------------------------------
# making ROOT plot - number of lines of code .vs. time
# --------------------------------------------------------
from ROOT import *

# beginning of coding (first commit) to set beginning of time x-scale
c=history[0]
td=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
time_offset = int(td.Convert()) - 7*24.*3600 # one week before first commit

# loop over commits
x, y, xbins = array( 'd' ), array( 'd' ), array( 'd' )
for c in history:
  td=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
  x.append(td.Convert() - time_offset)
  xbins.append(td.Convert() - time_offset)
  y.append(c[1]) # number of lines of code
  print c[0],c[1],"(",descr[0],c[2][0],",",descr[1],c[2][1],",",descr[2],c[2][2],",",descr[3],c[2][3],",",descr[4],c[2][4],",",descr[5],c[2][5],")"

# axis with bin edge description
xbins = sorted(xbins)
dx = x[len(x)-1] - x[len(x)-2]
xbins.append(x[len(x)-1]+dx)
xtmp = array( 'd' )
for i in range(0, len(xbins)):
    xtmp.append(xbins[i])


# applying visual style
ROOT.gROOT.LoadMacro("BornAgainStyle.C");
ROOT.gROOT.ProcessLine("BornAgainStyle()")

# creating histograms
nhistograms=7
a_histograms = []
hstack = THStack("hstack","Number of Lines of Code")
hstack.SetTitle("");

#a_colors=[kAzure+1, kCyan+1, kRed+1, kOrange+1, kMagenta+1, kGreen+1, kGray]
#a_colors=[kBlue+1, kOrange, kRed+1, kOrange, kMagenta, kBlue-9, kGreen]
a_colors=[kAzure+1, kOrange, kRed, kGreen, kYellow-7, kAzure, kGray+1]
legend = TLegend(0.17,0.55,0.42,0.90)
legend.SetBorderSize(1);
legend.SetFillStyle(1);
for i_hist in range(0,nhistograms):
    hist = TH1D(descr[i_hist],descr[i_hist],len(xtmp)-1,xtmp)
    hist.GetXaxis().SetTimeDisplay(1)
    hist.GetXaxis().SetTimeFormat("%d/%m")
    hist.GetYaxis().SetLabelSize(0.030)
    hist.GetXaxis().SetLabelSize(0.035)
    hist.GetXaxis().SetNdivisions(512)
    hist.GetXaxis().SetTimeOffset(time_offset)
    hist.SetLineColor(a_colors[i_hist])
    hist.SetFillColor(a_colors[i_hist])
    hstack.Add(hist,"][")
    a_histograms.append(hist)

# adding histograms to legend in right order
for i_hist in range(nhistograms-1,-1,-1):
    legend.AddEntry(a_histograms[i_hist],descr[i_hist],"f")

# filling histograms
for c in history:
    td=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
    xx = td.Convert() - time_offset
    for i_hist in range(0,nhistograms):
        yy = c[2][i_hist]
        a_histograms[i_hist].Fill(xx,yy)

#preparing canvas
c1 = TCanvas( 'gisasfw_loc', 'Number of lines of code in GISASFW project', 600, 600)
c1.cd()
gPad.SetGrid()
gPad.SetBottomMargin(0.12)
gPad.SetLeftMargin(0.11)


# drawing
hstack.Draw()
hstack.GetXaxis().SetTimeDisplay(1)
#hstack.GetXaxis().SetTimeFormat("%d/%m")
hstack.GetXaxis().SetTimeFormat("#splitline{%d/%m}{%Y}")
hstack.GetXaxis().SetLabelSize(0.03)
hstack.GetYaxis().SetLabelSize(0.035)
hstack.GetXaxis().SetLabelOffset(0.02)
hstack.GetXaxis().SetNdivisions(512)
hstack.GetXaxis().SetTimeOffset(time_offset)

legend.Draw()
c1.Modified()
gPad.RedrawAxis()
gPad.RedrawAxis("G")
c1.Modified()
c1.Update()


c1.Print("gisasfw_loc.png")



# wait for input to keep the GUI (which lives on a ROOT event dispatcher) alive
if __name__ == '__main__':
   rep = ''
   while not rep in [ 'q', 'Q' ]:
      rep = raw_input( 'enter "q" to quit: ' )
      if 1 < len(rep):
         rep = rep[0]


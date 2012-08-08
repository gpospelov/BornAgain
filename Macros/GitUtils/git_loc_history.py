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
adds=None
cmt=None

history=[]

def pop():
    if adds is not None:
        pstr="%s %8u %5s %5s %7s %s \t%s"%(d,locs,'+'+str(adds),'-'+str(dels),hsh,who,cmt.strip())
        #if needsvg: stderr.write(pstr+'\n')
        #else: print(pstr)
        print pstr
        history.append((d,locs,adds,dels,hsh,who,cmt))

prevfolder = os.getcwd()
if extfolder:
    os.chdir(targetfolder)

# parsing output of git log 
wrong_ppp_file=False
wrong_mmm_file=False
for x in popen('git log master --reverse -p'):
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
        if (".h" in x or ".cpp" in x or ".py" in x or ".pro" in x) and not "ThirdParty" in x:
            wrong_ppp_file=False
        else:
            wrong_ppp_file=True

    if x.startswith('---'):
        if (".h" in x or ".cpp" in x or ".py" in x or ".pro" in x) and not "ThirdParty" in x:
            wrong_mmm_file=False
        else:
            wrong_mmm_file=True

    if x.startswith('+') and not x.startswith('+++'):
        if not wrong_ppp_file:
            adds+=1
            locs+=1
    if x.startswith('-') and not x.startswith('---'):
        if not wrong_mmm_file:
            dels+=1
            locs-=1

pop()
os.chdir(prevfolder)

# --------------------------------------------------------
# making ROOT plot - number of lines of code .vs. time
# --------------------------------------------------------
from ROOT import TDatime, gStyle, TCanvas, TGraph, gROOT, gPad, TLatex
#gROOT.Reset()

# beginning of coding (first commit) to set beginning of time x-scale
c=history[0]
td=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
time_offset = int(td.Convert()) - 7*24.*3600 # one week before first commit

x, y = array( 'd' ), array( 'd' )

# loop over commits
for c in history:
  td=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
  x.append(td.Convert() - time_offset)
  y.append(c[1]) # number of lines of code


# preparing graph
gr = TGraph(len(history), x, y);
gr.SetLineColor( 4 )
gr.SetLineWidth( 2 )
gStyle.SetTitleSize(0.035)
gr.SetTitle( " number of lines of code vs time " )
gr.GetXaxis().SetLabelOffset( 0.025 )
gr.GetXaxis().SetTimeDisplay(1)
#gr.GetXaxis().SetTimeFormat("#splitline{%d %m %y}{%H:%M}")
gr.GetXaxis().SetTimeFormat("%d/%m")
gr.GetXaxis().SetLabelSize(0.03)
gr.GetXaxis().SetNdivisions(512)
gr.GetXaxis().SetTimeOffset(time_offset)

#preparing canvas
c1 = TCanvas( 'gisasfw_loc', 'Number of lines of code in GISASFW project', 600, 600)
c1.SetGrid()
gPad.SetBottomMargin(0.12)

# drawing
gr.Draw("al")
#txt=TLatex()
#txt.SetNDC()
#txt.SetTextSize(0.025)
#txt.DrawLatex(0.2,0.95,"Lines of code vs time")
c1.Modified()
c1.Print("gisasfw_loc.png")



# wait for input to keep the GUI (which lives on a ROOT event dispatcher) alive
if __name__ == '__main__':
   rep = ''
   while not rep in [ 'q', 'Q' ]:
      rep = raw_input( 'enter "q" to quit: ' )
      if 1 < len(rep):
         rep = rep[0]


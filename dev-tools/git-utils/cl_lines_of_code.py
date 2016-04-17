#!/usr/bin/env python

# calculate number of lines of code in BornAgain project as a function of time
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
# MG: I've modified this file to run it from command line in release.sh script

import datetime, email.utils, optparse, os, re, sys, time

def append_to_history():
    if adds is None:
        return
    # print( "%s %8u %5s %5s %7s %s \t%s"%(d,locs,'+'+str(adds),'-'+str(dels),hsh,who,cmt.strip()) )
    history.append((d,locs,list(locs_type),adds,dels,hsh,who,cmt))

def filePython(x):
    if ".py" in x and not ".pypp." in x: return True
    return False

def fileCpp(x):
    if ".h" in x or ".cpp" in x: return True
    return False

def dirCore(x):
    if "/Core/Algorithms" in x: return True
    if "/Core/FormFactors" in x: return True
    if "/Core/Samples" in x: return True
    if "/Core/StandardSamples" in x: return True
    if "/Core/Tools" in x: return True
    if "/Core/Fitting" in x: return True
    if "/Core/inc" in x: return True
    if "/Core/src" in x: return True
    if "/Fit/Factory" in x: return True
    if "/Fit/FitKernel" in x: return True
    if "/Fit/StandardFits" in x: return True
    if "/Core/Geometry" in x: return True
    return False

def dirPyAPI(x):
    if "/Core/PythonAPI" in x: return True
    if "/Fit/PythonAPI" in x: return True
    return False

def dirFuncTest(x):
    if "/App/" in x: return True
    if "/Tests/FunctionalTests/TestCore" in x: return True
    if "/Tests/FunctionalTests/TestFit" in x: return True
    if "/Tests/FunctionalTests/TestPyCore" in x: return True
    if "/Tests/FunctionalTests/TestPyFit" in x: return True
    return False

def dirGUI(x):
    if "/GUI/coregui" in x  and not "widgetbox" in x and not "qttools" in x: return True
    if "/GUI/main" in x: return True
    if "/AppGUI/coregui" in x: return True
    if "/BASuite" in x: return True
    return False

def dirThirdParty(x):
    if "/ThirdParty" in x: return True
    return False

def dirSkip(x):
    if "/pub/core" in x: return True
    return False

def dirUnitTests(x):
    if "/UnitTests/" in x: return True
    if "/Tests/UnitTests/TestCore/" in x: return True
    if "/Tests/UnitTests/TestFit/" in x: return True
    return False

def filetype(x):
    file_type=8
    if dirSkip(x):
        return file_type
    if fileCpp(x) and dirCore(x):
        file_type = 0
    elif (fileCpp(x) or filePython(x)) and dirFuncTest(x):
        file_type = 1
    elif dirUnitTests(x):
        file_type = 2
    elif dirGUI(x):
        file_type = 5
    elif dirPyAPI(x):
        file_type = 6
    elif dirThirdParty(x):
        file_type = 7
    return file_type

def save_history_as_table(fname):
    f = open(fname, 'w')
    for entry in history:
        d = entry[0]
        tim = 2012 +  (d - datetime.datetime(2012,1,1)).total_seconds()/366.0/24/3600
        f.write( "%9.4f %s\n" % ( tim, entry[1:] ) )
    f.close()
    print( "Table with one line per commit written to "+fname )
    
# ------------------------------------------------------------------------------
# MAIN
# ------------------------------------------------------------------------------
usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)
parser.add_option('-o', '--output-filename', type="string", action="store", dest="outfname", help="Output plot file name.", default="lines_of_code.png")
parser.add_option('-i', '--input-dir', type="string", action="store", dest="gitdir", help="Path to the .git folder.", default=".")
(options, args) = parser.parse_args()

extfolder=True
targetfolder=options.gitdir
fc=0
locs=0
locs_type=[0,0,0,0,0,0,0,0,0]

#       0      1                  2            3      4        5      6     7       8
descr=["Core","Functional Tests","Unit Tests","*.py","macros","GUI", "PythonAPI","Third","Undef"]
adds=None
cmt=None
prev_time = datetime.datetime(2000,1,1)

history=[]

prevfolder = os.getcwd()
if extfolder: os.chdir(targetfolder)

# parsing output of git log 
file_type_ppp = 8
file_type_mmm = 8

for x in os.popen('git log develop --reverse -p'):
    if x.startswith('commit'):
        append_to_history()
        hsh=x[7:14];
    if x.startswith('Author'):
        who=x.replace("Author: ",'').replace('\n','');
        who=re.sub(">.*","",who);
        who=re.sub(".*<","",who);
    if x.startswith('Date'):
        fc=1
        pd=email.utils.parsedate(x[5:])
        d=datetime.datetime(*pd[:7])
        t=time.mktime(pd)
        adds=0
        dels=0
        sys.stdout.write( x.rstrip() )
        sys.stdout.write( '\r' )
        sys.stdout.flush()
        # accelerate development
        if( d.year!=2012 ):
            break
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
append_to_history() # once more upon leaving the loop

save_history_as_table("lines_of_code.tab")

# clear progress line
sys.stdout.write( '\r' )
sys.stdout.flush()

os.chdir(prevfolder)

# --------------------------------------------------------
# making ROOT plot - number of lines of code .vs. time
# --------------------------------------------------------
from ROOT import *

# beginning of coding (first commit) to set beginning of time x-scale
c=history[0]
td_first=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
c=history[-1]
td_last=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
time_offset = int(td_first.Convert()) - 7*24.*3600 # one week before first commit

ntimebins = 4*int((td_last.Convert() - time_offset)/3600./24)

#print "ntimebins", ntimebins
hist_ncommits = TH1D("ncommits", "ncommits", ntimebins, td_first.Convert() - time_offset, td_last.Convert() - time_offset)

# ---------------------------------
# creating histograms
# ---------------------------------
selected_hist = [0,1,2,5,6]

a_histograms = []
hstack = THStack("hstack","Number of Lines of Code")
hstack.SetTitle("");

a_colors=[kAzure+1, kOrange, kRed, kGreen, kYellow-7, kAzure, kGray+1]
legend = TLegend(0.15,0.65,0.49,0.84)
legend.SetBorderSize(1);
#legend.SetFillStyle(1);
for i in range(0, len(selected_hist) ):
    i_hist = selected_hist[i]
    #hist = TH1D(descr[i_hist],descr[i_hist],len(xtmp)-1,xtmp)
    hist = TH1D(descr[i_hist],descr[i_hist], ntimebins, td_first.Convert() - time_offset, td_last.Convert() - time_offset )
    
    hist.GetXaxis().SetTimeDisplay(1)
    hist.GetXaxis().SetTimeFormat("%d/%m")
    hist.GetYaxis().SetLabelSize(0.030)
    hist.GetXaxis().SetLabelSize(0.035)
    hist.GetXaxis().SetNdivisions(512)
    hist.GetXaxis().SetTimeOffset(time_offset)
    hist.SetLineColor(a_colors[i_hist])
    hist.SetFillColor(a_colors[i_hist])
    a_histograms.append(hist)

# adding histograms to legend in right order
for i_hist in range(len(a_histograms)-1,-1,-1):
    legend.AddEntry(a_histograms[i_hist],a_histograms[i_hist].GetTitle(),"f")

# filling histograms
for c in history:
    td=TDatime(c[0].year, c[0].month, c[0].day, c[0].hour, c[0].minute, c[0].second)
    xx = td.Convert() - time_offset
    hist_ncommits.Fill(xx)
    for i in range(0, len(selected_hist) ):
        i_hist = selected_hist[i]
        yy = c[2][i_hist]
        a_histograms[i].Fill(xx,yy)

# normalizing bin content on number of entries per bin
for i_bin in range(1,hist_ncommits.GetNbinsX()+1):
    nentries = hist_ncommits.GetBinContent(i_bin)
    for h in a_histograms:
        current_bin_content = h.GetBinContent(i_bin)
        if nentries != 0: current_bin_content /= nentries
        h.SetBinContent(i_bin, current_bin_content)

# filling empty bins with values from previous day
for h in a_histograms:
    prev_content = 0
    for i_bin in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i_bin) == 0:
            h.SetBinContent(i_bin, prev_content)
        prev_content = h.GetBinContent(i_bin)
        
#preparing canvas
c1 = TCanvas( 'gisasfw_loc', 'Number of lines of code in BornAgain project', 800, 800)
c1.cd()
gPad.SetGrid()
gPad.SetBottomMargin(0.10)
gPad.SetLeftMargin(0.10)
gPad.SetTopMargin(0.10)
gPad.SetRightMargin(0.10)

# drawing
for h in a_histograms:
    hstack.Add(h,"][")
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
c1.Modified()
c1.Update()
gPad.RedrawAxis()
gPad.RedrawAxis("G")

c1.Print(options.outfname)
print( "Plot saved in "+options.outfname )

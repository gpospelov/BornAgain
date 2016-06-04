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

import datetime, optparse, os, re, sys, time

# ------------------------------------------------------------------------------
# categorize files
# ------------------------------------------------------------------------------

descr=[
    "non-source",
    "auto",
    "conf",
    "core",
    "futest",
    "utest",
    "GUI",
    "examples",
    "third-party",
    "other C++",
    "other Py",
    "undef",
]

def filetype(x):
    if  re.search( r'(dev-tools|build|qbuild|html)/', x ):
        file_type = 0 # skip
    elif( re.search( r'doxygen_\w+\.i', x ) or
          re.search( r'lib\w+\.py', x ) or
          re.search( r'lib\w+_wrap\.', x ) or
          re.search( r'bornagain\.1$', x ) or
          re.match( r'(Core|Fit)/PythonAPI', x ) ):
        file_type = 1 # auto-generated
    elif re.search( r'\w+\.(in|txt|cmake)$', x ):
        file_type = 2 # configuration scripts
    elif fileCpp(x) and dirCore(x):
        file_type = 3 # core C++ code
    elif (fileCpp(x) or filePython(x)) and dirFuncTest(x):
        file_type = 4 # functional tests
    elif fileCpp(x) and dirUnitTests(x):
        file_type = 5 # unit tests
    elif dirGUI(x):
        file_type = 6 # GUI
    elif re.match( r'Examples/', x ):
        file_type = 7 # Examples
    elif dirThirdParty(x):
        file_type = 8 # other third-party code
    elif fileCpp(x):
        file_type = 9 # other C++ code
    elif filePython(x):
        file_type = 10 # other Py code
    else:
        file_type = 11 # unknown type
    return file_type

def filePython(x):
    if ".py" in x and not ".pypp." in x: return True
    return False

def fileCpp(x):
    if ".h" in x or ".cpp" in x: return True
    return False

def dirCore(x):
    if "Core/Algorithms" in x: return True
    if "Core/FormFactors" in x: return True
    if "Core/Geometry" in x: return True
    if "Core/InputOutput" in x: return True
    if "Core/Samples" in x: return True
    if "Core/StandardSamples" in x: return True
    if "Core/Tools" in x: return True
    if "Fit/Factory" in x: return True
    if "Fit/FitKernel" in x: return True
    if "Fit/StandardFits" in x: return True
    # abolished directories:
    if "GISASFW" in x: return True
    if "Core/Fitting" in x: return True
    if "Core/inc" in x: return True
    if "Core/src" in x: return True
    return False

def dirFuncTest(x):
    if "App/" in x: return True
    if "Tests/FunctionalTests/TestCore" in x: return True
    if "Tests/FunctionalTests/TestFit" in x: return True
    if "Tests/FunctionalTests/TestPyCore" in x: return True
    if "Tests/FunctionalTests/TestPyFit" in x: return True
    return False

def dirGUI(x):
    if "GUI/coregui" in x  and not "widgetbox" in x and not "qttools" in x: return True
    if "GUI/main" in x: return True
    # abolished directories:
    if "AppGUI/coregui" in x: return True
    if "BASuite" in x: return True
    return False

def dirThirdParty(x):
    if "ThirdParty" in x: return True
    if "ROOT" in x: return True
    if "GUI/externals" in x: return True
    return False

def dirSkip(x):
    # abolished directories:
    if "pub/core" in x: return True
    return False

def dirUnitTests(x):
    if "Tests/UnitTests/TestCore/" in x: return True
    if "Tests/UnitTests/TestFit/" in x: return True
    # abolished directories:
    if "UnitTests/" in x: return True
    return False

# ------------------------------------------------------------------------------
#
# ------------------------------------------------------------------------------

def append_to_history():
    if adds is None:
        return
    history.append((d,list(locs_type),adds,dels,hsh,who,cmt))

def save_history_as_table(fname):
    f = open(fname, 'w')
    for entry in history:
        d = entry[0]
        tim = 2012 +  (d - datetime.datetime(2012,1,1)).total_seconds()/366.0/24/3600
        f.write( "%9.4f" % ( tim ) )
        for i in entry[1]:
            f.write( " %6i" % ( i ) )
        f.write( " # %s %s\n" % (entry[4], entry[6][0:28] ) )
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

fc=0
locs_type=[0 for cat in descr]

adds = None
dels = None
cmt = None
hsh = None
prev_time = datetime.datetime(2000,1,1)

history=[]

prevfolder = os.getcwd()
os.chdir(options.gitdir)

pos = -1
for x in os.popen('git log develop --reverse --pretty=format:"A: %ae%nD: %ct%nS: %s%nH: %h%n" --numstat'):
    x = x.rstrip(' \t\r\n')
    if pos==-1 or pos==4:
        m = re.match(r'A: (.+)@', x )
        if m:
            who = m.group(1)
            if pos!=-1:
                append_to_history()
            pos = 0
            adds=0
            dels=0
            continue

    if pos==0:
        m = re.match(r'D: (.+)$', x )
        if m is None:
            raise RuntimeError("D not found")
        pos = 1
        raw = m.group(1)
        d = datetime.datetime.fromtimestamp(float(raw))
        sys.stdout.write( str(d) )
        sys.stdout.write( '\r' )
        sys.stdout.flush()
        # if( d.year!=2012 ): break # TEMPORARY, to accelerate development
    elif pos==1:
        m = re.match(r'S: (.+)$', x )
        if m is None:
            raise "S not found"
        pos = 2
        cmt = m.group(1)
    elif pos==2:
        m = re.match(r'H: (.+)$', x )
        if m is None:
            raise RuntimeError("H not found")
        pos = 3
        hsh = m.group(1)
    elif pos==3:
        if x!="":
            raise RuntimeError("empty line not found")
        pos = 4
    else:
        pos = 5
        if x=="":
            pos = 4
            continue
        m = re.match(r'-\s+-\s+(.+)$', x )
        if m:
            continue
        m = re.match(r'(\d+)\s+(\d+)\s+(.+)$', x )
        if m is None:
            raise RuntimeError( "Unexpected record '"+x+"'" )
        lines_inserted = int(m.group(1))
        lines_deleted = int(m.group(2))
        fnam = m.group(3)
        ftyp = filetype(fnam)
        locs_type[ftyp] += lines_inserted - lines_deleted
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

# calculate number of lines of code in BornAgain project as a function of time

# object-oriented rewrite of cl_lines_of_code
# JWu apr2016: don't use this, it's outdated by latest refactoring of cl_lines_of_code

from __future__ import print_function
import os
import re
from datetime import datetime
from email.utils import parsedate
from enum import Enum
from ROOT import *


time_offset = 0

class FileTypes:
    CORE, FTEST, UTEST, PYCODE, MACROS, GUI, PYAPI, THIRD, UNDEF, TOTAL = range(10)
    descr=["Core", "Functional Tests", "Unit Tests", "*.py", "macros", "GUI", "PythonAPI", "Third", "Undef"]


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
    if "/Core/InputOutput" in x: return True
    if "/Core/Geometry" in x: return True
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
    # if "/App/" in x: return True
    if "/Tests/Functional" in x: return True
    if "/Tests/PerformanceTests" in x: return True
    if "/Tests/FunctionalTests/TestCore" in x: return True
    if "/Tests/FunctionalTests/TestFit" in x: return True
    if "/Tests/FunctionalTests/TestPyCore" in x: return True
    if "/Tests/FunctionalTests/TestPyFit" in x: return True
    if "/Core/TestMachinery" in x: return True
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
    if "/Tests/UnitTests/" in x: return True
    return False


def filetype(x):
    """
    Returns type of file
    """
    result = FileTypes.UNDEF

    if dirSkip(x):
        return result

    if fileCpp(x) and dirCore(x):
        result = FileTypes.CORE

    elif (fileCpp(x) or filePython(x)) and dirFuncTest(x):
        result = FileTypes.FTEST

    elif dirUnitTests(x):
        result = FileTypes.UTEST

    elif dirGUI(x):
        result = FileTypes.GUI

    elif dirPyAPI(x):
        result = FileTypes.PYAPI

    elif dirThirdParty(x):
        result = FileTypes.THIRD

    return result


class Commit:
    def __init__(self):
        self.date = datetime.today()
        self.adds = 0
        self.dels = 0
        self.locs_for_type = []
        for i in range(FileTypes.TOTAL):
            self.locs_for_type.append(0)
        self.hsh = None
        self.who = None
        self.cmt = None

    def increment_loc(self, file_type):
        self.locs_for_type[file_type] += 1
        self.adds += 1

    def decrement_loc(self, file_type):
        self.locs_for_type[file_type] -= 1
        self.dels += 1


class HistoryCollector:
    def __init__(self):
        self.history = Commit()
        self.data = []
        self.locs = 0
        self.fc = 0
        self.file_type_ppp = FileTypes.UNDEF
        self.file_type_mmm = FileTypes.UNDEF

    def pop(self):
        if not self.history.adds:
            return
        pstr="%s %8u %5s %5s %7s %s \t%s"%(self.history.date, self.locs,'+'+str(self.history.adds),'-'+str(self.history.dels), self.history.hsh, self.history.who, self.history.cmt.strip())
        print(self.history.locs_for_type[0], pstr)
        self.data.append(self.history)
        tmp = list(self.history.locs_for_type)
        self.history = Commit()
        self.history.locs_for_type = tmp

    def run(self):
        nnn = 0
        for x in os.popen('git log develop --reverse -p'):
            nnn += 1
            if x.startswith('commit'):
                self.pop()
                self.history.hsh = x[7:14]

            if x.startswith('Author'):
                self.history.who = x.replace("Author: ", '').replace('\n', '')
                self.history.who = re.sub(">.*", "", self.history.who)
                self.history.who = re.sub(".*<", "", self.history.who)

            if x.startswith('Date'):
                self.fc = 1
                self.history.date = datetime(*parsedate(x[5:])[:7])
                #t=datetime.mktime(parsedate(x[5:]))

            if self.fc == 2:
                self.history.cmt = x[:-1]
                self.fc = 0

            if self.fc == 1:
                if len(x) == 1:
                    self.fc = 2

            if x.startswith('+++'):
                self.file_type_ppp = filetype(x)

            if x.startswith('---'):
                self.file_type_mmm = filetype(x)

            if x.startswith('+') and not x.startswith('+++'):
                self.history.increment_loc(self.file_type_ppp)
                if self.file_type_ppp <FileTypes.PYAPI:
                    self.locs += 1

            if x.startswith('-') and not x.startswith('---'):
                self.history.decrement_loc(self.file_type_mmm)
                if self.file_type_mmm <FileTypes.PYAPI:
                    self.locs -= 1

            # if nnn>1000000:
            #     break

        self.pop()


def create_time_histogram(history, title, fileType):
    global time_offset
    c = history[0]
    td_first = TDatime(c.date.year, c.date.month, c.date.day, c.date.hour, c.date.minute, c.date.second)
    c = history[-1]
    td_last = TDatime(c.date.year, c.date.month, c.date.day, c.date.hour, c.date.minute, c.date.second)

    time_offset = int(td_first.Convert()) - 7*24*3600  # one week before first commit
    xmin = 0
    xmax = int(td_last.Convert()) - time_offset

    ntimebins = (xmax - xmin)/3600  # one timebin per day
    # print("CORE {1} FTEST {2} UTEST {3} GUI {4} PYAPI {5}".format(c.locs_for_type[]))

    print("{0}:{1}".format(title, c.locs_for_type[fileType]))

    result = TH1D(title, title, ntimebins, xmin, xmax)
    result.GetXaxis().SetTimeDisplay(1)
    result.GetXaxis().SetTimeFormat("#splitline{%d/%m}{%Y}")
    result.GetYaxis().SetLabelSize(0.02)
    result.GetXaxis().SetLabelSize(0.02)
    # result.GetXaxis().SetNdivisions(512)
    result.GetXaxis().SetTimeOffset(time_offset)

    refhist = TH1D(title+"_ref", title+"_ref", ntimebins, xmin, xmax)

    # filling histogram
    for c in history:
        td = TDatime(c.date.year, c.date.month, c.date.day, c.date.hour, c.date.minute, c.date.second)
        xx = td.Convert() - time_offset
        result.Fill(xx, c.locs_for_type[fileType])
        refhist.Fill(xx)

    # normalizing bin content on number of entries per bin
    for i_bin in range(1, result.GetNbinsX()+1):
        nentries = refhist.GetBinContent(i_bin)
        bin_content = float(result.GetBinContent(i_bin))
        if bin_content<0:
            print(i_bin, nentries, bin_content)
        if nentries != 0:
            bin_content /= nentries
            result.SetBinContent(i_bin, bin_content)

    # filling empty bins with values from previous day
    prev_content = 0
    for i_bin in range(1, result.GetNbinsX()+1):
            if result.GetBinContent(i_bin) == 0:
                result.SetBinContent(i_bin, prev_content)
            prev_content = result.GetBinContent(i_bin)

    return result


def hold_root_graphics():
    """
    Holds ROOT graphics while listening to ctr-C event
    """
    Interrupt = False
    while not Interrupt:
        Interrupt = gSystem.ProcessEvents()
        gSystem.Sleep(10)


def plot_loc_number(history):
    global time_offset

    selected_hist = [FileTypes.CORE, FileTypes.FTEST, FileTypes.UTEST, FileTypes.GUI, FileTypes.PYAPI]
    a_colors = [kAzure+1, kOrange, kRed, kGreen, kYellow-7, kAzure, kGray+1]

    a_histograms = []
    hstack = THStack("hstack","Number of Lines of Code")
    hstack.SetTitle("")

    legend = TLegend(0.14, 0.65, 0.4, 0.84)
    legend.SetBorderSize(1)
    for i in range(0, len(selected_hist)):
        i_hist = selected_hist[i]
        hist = create_time_histogram(history, FileTypes.descr[selected_hist[i]], i_hist)
        hist.SetLineColor(a_colors[i_hist])
        hist.SetFillColor(a_colors[i_hist])
        a_histograms.append(hist)


    # adding histograms to legend in right order
    for i_hist in range(len(a_histograms)-1, -1, -1):
        legend.AddEntry(a_histograms[i_hist], a_histograms[i_hist].GetTitle(), "f")


    #preparing canvas
    c1 = TCanvas( 'gisasfw_loc', 'Number of lines of code in BornAgain project', 1024, 768)
    c1.cd()
    gPad.SetGrid()
    gPad.SetBottomMargin(0.10)
    gPad.SetLeftMargin(0.10)
    gPad.SetTopMargin(0.10)
    gPad.SetRightMargin(0.10)
    # a_histograms[0].Draw("HIST")

    # drawing
    for h in a_histograms:
        hstack.Add(h,"][")
    hstack.Draw("HIST")
    hstack.GetXaxis().SetTimeDisplay(1)
    #hstack.GetXaxis().SetTimeFormat("%d/%m")
    hstack.GetXaxis().SetTimeFormat("#splitline{%b}{%Y}")
    hstack.GetXaxis().SetLabelSize(0.025)
    hstack.GetYaxis().SetLabelSize(0.025)
    hstack.GetXaxis().SetLabelOffset(0.02)
    hstack.GetXaxis().SetNdivisions(522)
    hstack.GetXaxis().SetTimeOffset(time_offset)
    hstack.SetMaximum(190e+03)

    #
    legend.Draw()
    c1.Modified()
    c1.Update()
    gPad.RedrawAxis()
    gPad.RedrawAxis("G")

    c1.Print("lines_of_code.png")
    hold_root_graphics()


def process_loc_number(targetfolder = "../.."):
    print("Hello World")

    prevfolder = os.getcwd()
    os.chdir(targetfolder)

    collector = HistoryCollector()
    collector.run()

    os.chdir(prevfolder)

    plot_loc_number(collector.data)





if __name__ == '__main__':
    process_loc_number()


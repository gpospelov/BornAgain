"""
Check users examples from Examples/python/simulation directory. The script walks through
the directory tree, imports examples one by one and tries to produce a scattering image.

Usage: python check_examples.py <path_to_examples_directory>

If no path is given, then current working dir will be used
"""
import sys
import os
import matplotlib
matplotlib.use('Agg')
import pylab
import shutil


def check_example(dirname, filename):
    """
    Tries to run python example and produce a *.png image
    """
    print "Analysing {:40s}".format(filename),

    try:
        fig = pylab.figure()
        d = dict(locals(), **globals())
        execfile(os.path.join(dirname, filename), d, d)
        plot_file_name = os.path.splitext(filename)[0] + ".png"
        pylab.savefig(plot_file_name)
        pylab.close(fig)

        status = "OK"

        kb = os.path.getsize(plot_file_name)/1000.
        if kb < 4.0:
            status = "EMPTY?"
    except:
        status = "FAILED"

    print status
    return os.path.join(dirname, filename), status


def walk_through(rootdir):
    """
    Walks through directory tree and checks every python example found
    """
    history = []
    for subdir, dirs, files in os.walk(rootdir):
        for file in files:
            if os.path.splitext(file)[1] == ".py":
                results = check_example(subdir, file)
                history.append(results)
    return history


def create_working_directory():
    """
    Creates working directory where all *.png images will be generated
    """
    tempdir = "temp"
    if os.path.exists(tempdir):
        shutil.rmtree(tempdir)
    os.makedirs(tempdir)
    return tempdir


def print_summary(rootdir, history):
    """
    prints summary over all python examples on the screen
    """
    print "-"*80
    print "Python examples summary"
    print "Directory: {0}".format(rootdir)
    print "-"*80
    history.sort()
    for h in history:
        filename = h[0]
        shortname = filename.split(rootdir)[1]
        print "{:65s} {:10s}".format(shortname, h[1])


if __name__ == '__main__':

    rootdir = "./"

    if len(sys.argv) == 2:
        rootdir = sys.argv[1]

    print "Analysing examples in '{0}' directory.".format(rootdir)

    tempdir = create_working_directory()
    os.chdir(tempdir)

    history = walk_through(rootdir)

    print_summary(rootdir, history)

    # check_example("/home/pospelov/development/BornAgain/source/Examples/python/simulation/ex01_BasicParticles", "CylindersAndPrisms.py")
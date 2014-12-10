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
import glob
import subprocess


def run_command(cmd):
    returncode = os.system(cmd)
    if returncode:
        exit("Error while running command '"+cmd+"'")


def FilesAreDifferent(file1, file2):
    '''Returns True if files are different or absent.'''

    if not os.path.exists(file1) or not os.path.exists(file2):
        return True
    proc = subprocess.Popen(["diff "+file1+" "+file2], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    if len(out) or err!=None:
        return True
    return False


def get_figure(filename):
    """
    Returns pylab figure of appropriate size
    """
    if "AllFormFactorsAvailable" in filename:
        xsize = 1024
        ysize = 768
    else:
        xsize = 640
        ysize = 480

    dpi = 72.
    xinch = xsize / dpi
    yinch = ysize / dpi
    return pylab.figure(figsize=(xinch, yinch))


def generate_example_plot(dirname, filename):
    """
    Tries to run python example and produce a *.png image
    """
    print "Analysing {:40s}".format(filename),

    fig = get_figure(filename)
    try:
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
    return os.path.join(dirname, filename), status, ""


def validate_examples(examples_dir):
    """
    Walks through directory tree and checks every python example found
    """
    history = []
    for subdir, dirs, files in os.walk(examples_dir):
        for file in files:
            if os.path.splitext(file)[1] == ".py":
                # results = generate_example_plot(subdir, file)
                # history.append(results)
                name, status, webstatus = generate_example_plot(subdir, file)
                history.append([name, status, webstatus])
    return history


def create_directories():
    """
    Creates working directory where all *.png images will be generated
    """
    tempdir = "temp"
    if os.path.exists(tempdir):
        shutil.rmtree(tempdir)
    os.makedirs(tempdir)
    return tempdir


def validate_drupal(history):
    """
    Validate examples in drupal directory
    """
    cmd = "scp -r apps@apps.jcns.fz-juelich.de:/www/apps/drupal/sites/default/files/python_examples/scripts ."
    run_command(cmd)
    drupal_scripts = glob.glob(os.path.join("scripts", "*.py"))
    for h in history:
        example_name = os.path.basename(h[0])
        for s in drupal_scripts:
            script_name = os.path.basename(s)
            if  script_name == example_name:
                if FilesAreDifferent(h[0], s):
                    h[2] = "[website differs]"
                else:
                    h[2] = "[website OK]"


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
        print "{:65s} {:10s} {:10s}".format(shortname, h[1], h[2])


if __name__ == '__main__':

    examples_dir = "./"

    if len(sys.argv) == 2:
        examples_dir = sys.argv[1]

    examples_dir = os.path.abspath(examples_dir)
    print "Analysing examples in '{0}' directory.".format(examples_dir)

    tempdir = create_directories()
    os.chdir(tempdir)

    history = validate_examples(examples_dir)


    validate_drupal(history)

    print_summary(examples_dir, history)

    # check_example("/home/pospelov/development/BornAgain/source/Examples/python/simulation/ex01_BasicParticles", "CylindersAndPrisms.py")
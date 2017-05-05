"""
Checks functionality of BornAgain Python example by running it in 'embedded' way.
Usage: python check_functionality.py <path-to-example>/example.py

Example is considered as functional, if it runs without exceptions thrown and
generates non-zero-size intensity image.

"""

import sys
import os
import matplotlib
matplotlib.use('Agg')
from matplotlib import pyplot as plt

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")

def get_figure(filename):
    """
    Returns pyplot figure of appropriate size
    """
    if "AllFormFactorsAvailable" in filename:
        xsize, ysize = 1024, 768
    else:
        xsize, ysize = 640, 480

    dpi = 72.
    return plt.figure(figsize=(xsize/dpi, ysize/dpi))


def exec_full(filepath):
    """
    Executes embedded python script.
    http://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3
    """
    import os
    global_namespace = {
        "__file__": filepath,
        "__name__": "__main__",
    }
    sys.argv = []  # FIXME after cleanup in plot_utils
    with open(filepath, 'rb') as file:
        exec(compile(file.read(), filepath, 'exec'), global_namespace)


def run_example(filename):
    """
    Tries to run python example and produce a *.png image
    """
    if not os.path.exists(filename):
        raise Exception("File '"+filename+"' doesn't exist.")

    print(filename)

    fig = get_figure(filename)
    try:
        exec_full(filename)

        plot_file_name = os.path.splitext(os.path.basename(filename))[0] + ".png"
        print(plot_file_name)
        plt.savefig(plot_file_name, bbox_inches='tight')
        plt.close(fig)

        status = "OK"

        kb = os.path.getsize(plot_file_name)/1000.
        if kb < 4.0:
            status = "EMPTY?"

    except:
        e = sys.exc_info()[0]
        print("Error {0} while trying to execute '{1}'".format(e, filename))
        status = "FAILED"

    print(status)
    if status != "OK":
        raise Exception(status)


if __name__ == '__main__':

    if len(sys.argv) != 2:
        exit("Error")

    run_example(sys.argv[1])

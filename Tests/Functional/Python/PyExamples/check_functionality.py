"""
Checks functionality of BornAgain Python example by running it in 'embedded' way.

The check passes successfully if the example runs without exceptions thrown and
generates non-zero-size intensity image.
"""

import matplotlib, os, sys
matplotlib.use('Agg')
from matplotlib import pyplot as plt


def get_figure(figsize):
    """
    Returns pyplot figure of appropriate size
    """
    dpi = 72.
    return plt.figure(figsize=(figsize[0]/dpi, figsize[1]/dpi))


def exec_full(filepath):
    """
    Executes embedded python script.
    http://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3
    """
    import os
    global_namespace = {
        "__file__": filepath,
        "__name__": "__main__",
        "__no_terminal__": True
    }
    sys.argv = []  # TODO: FIXME after cleanup in plot_utils
    with open(filepath, 'rb') as file:
        exec(compile(file.read(), filepath, 'exec'), global_namespace)


def run_example(filename, output_dir):
    """
    Tries to run python example and produce a *.png image
    """
    if not os.path.exists(filename):
        raise Exception("Example script '" + filename + "' not found")

    print("Input script: " + filename, flush=True)

    if "AllFormFactorsAvailable" in filename:
        figsize = (1024, 768)
    else:
        figsize = (640, 480)
    fig = get_figure(figsize)

    exec_full(filename)
    print("Input script completed.", flush=True)

    plot_file_name = os.path.join(
        output_dir,
        os.path.splitext(os.path.basename(filename))[0] + ".png")
    print("Output image: " + plot_file_name)
    plt.savefig(plot_file_name, bbox_inches='tight')
    plt.close(fig)

    imgSize = os.path.getsize(plot_file_name)
    if imgSize == 0:
        raise Exception("Image file is empty")
    if imgSize < 20000:
        raise Exception("Image file is unplausibly small")


if __name__ == '__main__':

    if len(sys.argv) != 3:
        exit("Usage: check_functionality <script_to_test> <output_dir>")

    run_example(sys.argv[1], sys.argv[2])

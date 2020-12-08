"""
Checks functionality of BornAgain Python example by running it in 'embedded' way.

The check passes successfully if the example runs without exceptions thrown and
generates non-zero-size intensity image.
"""

import matplotlib, os, re, sys
matplotlib.use('Agg')
from matplotlib import pyplot as plt


def exec_full(script, filename):
    """
    Executes embedded python script.
    http://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3
    """
    import os
    global_namespace = {
        "__file__": filename,
        "__name__": "__main__",
        "__no_terminal__": True
    }
    sys.argv = []
    exec(compile(script, filename, 'exec'), global_namespace)


def run_example(filename, output_dir):
    """
    Tries to run python example and produce a *.png image
    """
    if not os.path.exists(filename):
        raise Exception("Example script '" + filename + "' not found")
    print("Input script: " + filename, flush=True)
    with open(filename, 'r') as file:
        script = file.read()

    m = re.search(r'plt\.figure\(.+?figsize=\((.+?),(.+?)\)', script)
    if m: # set figure size as in script
        figsize = (float(m.group(1)), float(m.group(2)))
    else: # script does not specify figure size
        figsize = (640/72, 480/72)
    fig = plt.figure(figsize=(figsize[0], figsize[1]))

    exec_full(script, filename)
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

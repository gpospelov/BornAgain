import matplotlib.pyplot as plt
import seaborn as sns
from datetime import datetime
from .file_types import FileTypes, filetype


def history_plot(filename):
    selected_hist = [FileTypes.CORE, FileTypes.FTEST, FileTypes.UTEST, FileTypes.GUI, FileTypes.PYAPI]

    xvals = []  # Time
    yvals = {}  # id of file type .vs. LOC .vs. time
    for x in selected_hist:
        yvals[x] = []

    print("Reading file {0}".format(filename))
    with open(filename, 'r') as the_file:
        for line in the_file:
            line = line.strip()
            parts = line.strip().split()
            date = datetime.strptime(parts[0]+ " " + parts[1], '%Y-%m-%d %H:%M:%S')
            xvals.append(date)
            for x in selected_hist:
                yvals[x].append(int(parts[2+x]))

    ypoints = []
    descr = []
    for key in yvals:
        descr.append(FileTypes.descr[key])
        ypoints.append(yvals[key])

    # printing summary of LOC
    for x in range(0, len(ypoints)):
        print("{:18} : {:10}".format(descr[x], ypoints[x][-1]))

    # figure size
    my_dpi = 96
    plt.figure(figsize=(1600*1.2 / my_dpi, 900*1.2 / my_dpi), dpi=my_dpi)
    plt.style.use('seaborn-bright')

    # making stackplot
    plt.stackplot(xvals, ypoints)
    pal = ["#3399ff", "#ffcc00", "#ff0000", "#0033ff", "#999999"]
    plt.stackplot(xvals, ypoints, labels=descr, colors=pal)

    # styling axes and grid
    plt.grid(color='gray', linestyle='dashed')
    ax = plt.gca()
    ax.set_axisbelow(True)
    plt.ylim(0.0, 220e+03)
    plt.tick_params(axis='both', which='major', labelsize=14)

    # making inverse legend
    handles, labels = ax.get_legend_handles_labels()
    ax.legend(handles[::-1], labels[::-1], loc='upper left', prop={'size': 18})

    # saving plot
    plt.savefig('lines_of_code.png', dpi=my_dpi, bbox_inches='tight')

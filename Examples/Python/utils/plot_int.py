#!/usr/bin/env python3

Helptext = '''
Plots data stored in BornAgain's .int or .int.gz format.
Can handle both 1D and 2D arrays.
Usage: plot_int.py intensity_file.int.gz [intensity_max]
'''

import argparse
import sys
import numpy as np
import bornagain as ba
from matplotlib import pyplot as plt
from matplotlib import rc, colors
rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
rc('text', usetex=True)


def plot_int(args):
    data = ba.IntensityDataIOFactory.readIntensityData(args.file)
    if args.max is None:
        intensity_max = data.getMaximum()
    if args.verbose:
        print(f'Data extend from {data.getMinimum()} to {data.getMaximum()}')
    if data.rank() == 1:
        plot_int_1d(data, intensity_max)
    elif data.rank() == 2:
        plot_int_2d(data, intensity_max)
    else:
        exit("Error in plot_int: wrong data rank")


def plot_int_2d(histogram, intensity_max):
    plot_raw_data_2d(histogram.array(), [
        histogram.getXmin()/ba.deg,
        histogram.getXmax()/ba.deg,
        histogram.getYmin()/ba.deg,
        histogram.getYmax()/ba.deg
    ], intensity_max)


def plot_raw_data_2d(values, extent_array, intensity_max):
    im = plt.imshow(values,
                    norm=colors.LogNorm(1.0, intensity_max),
                    extent=extent_array,
                    aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


def plot_int_1d(histogram, intensity_max):
    axis_values = np.asarray(histogram.xAxis().binCenters())/ba.deg
    array_values = histogram.array()*intensity_max/histogram.getMaximum()
    plot_raw_data_1d(axis_values, array_values)


def plot_raw_data_1d(axis, values, log_y=True):
    if log_y:
        plt.semilogy(axis, values)
    else:
        plt.plot(axis, values)
    plt.xlabel(r'$\alpha_i (^{\circ})$', fontsize=16)
    plt.ylabel(r'Value (a.u.)', fontsize=16)
    plt.show()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", help="print some output to the terminal",
                        action="store_true")
    parser.add_argument("file", type=str,
                        help="input data file (.int or .int.gz)")
    parser.add_argument("-u", "--min", type=int, help="upper plot limit")
    parser.add_argument("-l", "--max", type=int, help="lower plot limit")
    args = parser.parse_args()

    plot_int(args)

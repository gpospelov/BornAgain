#!/usr/bin/env python
# Plots intensity data difference stored in BornAgain "*.int" or "*.int.gz" format
# Usage: python plot_intensity_data.py intensity_reference.int.gz intensity_other.int.gz

import matplotlib, numpy, sys
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def plot_intensity_data(ref, data):
    im = plt.imshow(
        data,
        norm=matplotlib.colors.LogNorm(),
        extent=[ref.getXmin()/deg, ref.getXmax()/deg, ref.getYmin()/deg, ref.getYmax()/deg],
        aspect='auto')

    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    if len(sys.argv)!=3:
        exit("Usage: plot_intensity_data_diff.py reference.int.gz other.int.gz")

    intensity_ref = ba.IntensityDataIOFactory.readIntensityData(sys.argv[1])
    intensity_other = ba.IntensityDataIOFactory.readIntensityData(sys.argv[2])
    data = 2*numpy.abs(intensity_ref.getArray() - intensity_other.getArray())/
           (numpy.abs(intensity_ref.getArray())+numpy.abs(intensity_other.getArray()))
    plot_intensity_data(intensity_ref, data)

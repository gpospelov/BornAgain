#!/usr/bin/env python
'''
Plots intensity data stored in BornAgain "*.int" or "*.int.gz" format
Usage: python plot_intensity_data.py intensity_file.int.gz [intensity_max]
'''

import matplotlib, numpy, sys
from matplotlib import pyplot as plt
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)
import bornagain as ba
from bornagain import deg, angstrom, nm


def plot_intensity_data(file_name, intensity_max=None):
    result = ba.IntensityDataIOFactory.readIntensityData(file_name)
    if intensity_max is None:
        intensity_max = result.getMaximum()
    im = plt.imshow(result.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, intensity_max),
                    extent=[result.getXmin()/deg, result.getXmax()/deg,
                            result.getYmin()/deg, result.getYmax()/deg],
                    aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    if len(sys.argv)<2 or len(sys.argv)>3:
        exit("Usage: plot_intensity_data.py intensity_file.int.gz [intensity_max]")

    if len(sys.argv)==2:
        plot_intensity_data(sys.argv[1])
    else:
        plot_intensity_data(sys.argv[1], float(sys.argv[2]))

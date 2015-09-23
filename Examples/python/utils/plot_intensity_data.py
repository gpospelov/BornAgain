#!/usr/bin/env python
# Plots intensity data stored in BornAgain "*.int" or "*.int.gz" format
# Usage: python plot_intensity_data.py intensity_file.int.gz

import numpy
import matplotlib
import pylab
from bornagain import *


def plot_intensity_data(file_name):
    intensity = IntensityDataIOFactory.readIntensityData(file_name)
    data = intensity.getArray() + 1
    phi_min = rad2deg(intensity.getAxis(0).getMin())
    phi_max = rad2deg(intensity.getAxis(0).getMax())
    alpha_min = rad2deg(intensity.getAxis(1).getMin())
    alpha_max = rad2deg(intensity.getAxis(1).getMax())
    im = pylab.imshow(data, norm=matplotlib.colors.LogNorm(),
                      extent=[phi_min, phi_max, alpha_min, alpha_max])
    cb = pylab.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    pylab.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    pylab.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    if len(sys.argv)!=2:
        exit("Usage: python plot_intensity_data.py intensity_file.int.gz")

    plot_intensity_data(sys.argv[1])

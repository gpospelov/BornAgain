#!/usr/bin/env python
# Plots intensity data difference stored in BornAgain "*.int" or "*.int.gz" format
# Usage: python plot_intensity_data.py intensity_reference.int.gz intensity_other.int.gz

import numpy
import matplotlib
import pylab
from bornagain import *


def plot_intensity_data(ref, data):
    phi_min = rad2deg(ref.getAxis(0).getMin())
    phi_max = rad2deg(ref.getAxis(0).getMax())
    alpha_min = rad2deg(ref.getAxis(1).getMin())
    alpha_max = rad2deg(ref.getAxis(1).getMax())
    im = pylab.imshow(numpy.rot90(data, 1), norm=matplotlib.colors.LogNorm(),
                      extent=[phi_min, phi_max, alpha_min, alpha_max])
    cb = pylab.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    pylab.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    pylab.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    if len(sys.argv)!=3:
        exit("Usage: python plot_intensity_data_diff.py intensity_reference.int.gz intensity_other.int.gz")
    intensity_ref = IntensityDataIOFactory.readIntensityData(sys.argv[1])
    intensity_other = IntensityDataIOFactory.readIntensityData(sys.argv[2])
    data = numpy.abs((intensity_ref.getArray() - intensity_other.getArray())/intensity_ref.getArray())
    plot_intensity_data(intensity_ref, data)

%pythoncode %{

#  **************************************************************************  #
#
#   BornAgain: simulate and fit scattering at grazing incidence
#
#   @file      Wrap/swig/CorePython.py
#   @brief     Python extensions of the SWIG-genrated Python module bornagain.
#              This file is included by libBornAgainCore.i.
#
#   @homepage  http://apps.jcns.fz-juelich.de/BornAgain
#   @license   GNU General Public License v3 or higher (see COPYING)
#   @copyright Forschungszentrum Juelich GmbH 2016
#   @authors   Scientific Computing Group at MLZ Garching
#   @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
#
#  **************************************************************************  #

def simulateThenPlotOrSave(simulate, plot):
    """
    Runs a simulation. Then plots the function or saves the result, depending on given argument.
    """
    import sys
    if len(sys.argv)<=1:
        print('Usage:')
        print('    '+sys.argv[0]+' -p      # to plot result')
        print('    '+sys.argv[0]+' <fname> # to save result in <fname>.int')
        sys.exit(1)
    result = simulate()
    if sys.argv[1] != '-p':
        IntensityDataIOFactory.writeIntensityData(result, sys.argv[1]+".int")
    else:
        plot(result)

def standardIntensityPlot(result):
    """
    Plots intensity map.
    """
    import matplotlib
    from matplotlib import pyplot as plt
    im = plt.imshow(
        result.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
        extent=[result.getXmin()/deg, result.getXmax()/deg,
                result.getYmin()/deg, result.getYmax()/deg],
        aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()

%}

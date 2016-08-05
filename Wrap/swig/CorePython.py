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

def standardIntensitySave(result, filename):
    if type(result) is dict:
        for name,data in result:
            IntensityDataIOFactory.writeIntensityData(
                result, filename+"."+name+".int")
    else:
        IntensityDataIOFactory.writeIntensityData(result, filename+".int")

def getFilenameOrPlotflag():
    import sys
    if len(sys.argv)<=1:
        print("Usage:")
        print("  " + sys.argv[0] + " -p                           # to plot results")
        print("  " + sys.argv[0] + " <filename without extension> # to save results")
        sys.exit()
    return sys.argv[1]

def simulateThenPlotOrSave(
        simulate, plot=standardIntensityPlot, save=standardIntensitySave):
    """
    Runs a simulation. Then plots the function or saves the result,
    depending on the command-line argument argv[1].
    """
    arg = getFilenameOrPlotflag()
    result = simulate()
    if arg != '-p':
        save(result, arg)
        IntensityDataIOFactory.writeIntensityData(result, arg+".int")
    else:
        plot(result)

%}

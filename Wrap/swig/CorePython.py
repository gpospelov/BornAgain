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
#   @copyright Forschungszentrum Jülich GmbH 2016
#   @authors   Scientific Computing Group at MLZ Garching
#   @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
#
#  **************************************************************************  #

def simulate_then_plot_or_save(simulate, plot):
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

%}

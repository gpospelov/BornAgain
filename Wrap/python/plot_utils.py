#  **************************************************************************  #
'''
#   BornAgain: simulate and fit scattering at grazing incidence
#
#   @file      Wrap/python.plot_utils
#   @brief     Python extensions of the SWIG-generated Python module bornagain.
#
#   @homepage  http://apps.jcns.fz-juelich.de/BornAgain
#   @license   GNU General Public License v3 or higher (see COPYING)
#   @copyright Forschungszentrum Juelich GmbH 2016
#   @authors   Scientific Computing Group at MLZ Garching
#   @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
'''
#  **************************************************************************  #

from __future__ import print_function
import bornagain as ba
from bornagain import deg as deg
from bornagain import IFitObserver as IFitObserver


def plot_colormap(intensity, zmin=None, zmax=None,
                  xlabel=r'$\phi_f ^{\circ}$',
                  ylabel=r'$\alpha_f ^{\circ}$',
                  zlabel="Intensity"):
    """
    Plots intensity data as color map
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    import matplotlib
    from matplotlib import pyplot as plt

    zmin = 1.0 if not zmin else zmin
    zmax = intensity.getMaximum() if not zmax else zmax

    im = plt.imshow(
        intensity.getArray(),
        norm=matplotlib.colors.LogNorm(zmin, zmax),
        extent=[intensity.getXmin()/deg, intensity.getXmax()/deg,
                intensity.getYmin()/deg, intensity.getYmax()/deg],
        aspect='auto',
    )
    cb = plt.colorbar(im, pad=0.025)

    plt.xlabel(xlabel, fontsize=14)
    plt.ylabel(ylabel, fontsize=14)
    cb.set_label(zlabel, size=14)


def plot_intensity_data(intensity, zmin=None, zmax=None):
    """
    Plots intensity data as color map and hold the plot.
    If command line parameter was provided, save image instead of plotting.
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    import sys

    if len(sys.argv) <= 1:
        from matplotlib import pyplot as plt
        plot_colormap(intensity, zmin, zmax)
        plt.show()
    else:
        ba.IntensityDataIOFactory.writeIntensityData(intensity, sys.argv[1])


class DefaultFitObserver(IFitObserver):
    """
    Draws fit progress every nth iteration. This class has to be attached to
    FitSuite via attachObserver method.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    It is up to the user what to do here.
    """

    def __init__(self, draw_every_nth=10):
        IFitObserver.__init__(self, draw_every_nth)

        import matplotlib
        from matplotlib import pyplot as plt
        global matplotlib, plt

        self.fig = plt.figure(figsize=(10.25, 7.69))
        self.fig.canvas.draw()
        plt.ion()

    def plot(self, data, title, nplot, min=1, max=1e6):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)
        im = plt.imshow(data.getArray(),
                        norm=matplotlib.colors.LogNorm(min, max),
                        extent=[data.getXmin(), data.getXmax(), data.getYmin(), data.getYmax()],
                        aspect='auto')
        plt.colorbar(im)
        plt.title(title)

    def update(self, fit_suite):
        self.fig.clf()
        real_data = fit_suite.getRealData()
        self.plot(real_data, "\"Real\" data", nplot=1, min=1.0, max=real_data.getMaximum())
        self.plot(fit_suite.getSimulationData(), "Simulated data", nplot=2, min=1.0, max=real_data.getMaximum())
        self.plot(fit_suite.getChiSquaredMap(), "Chi2 map", nplot=3, min=0.001, max=10.0)

        plt.subplot(2, 2, 4)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iterations  " + '{:d}     {:s}'.
                 format(fit_suite.numberOfIterations(), fit_suite.minimizer().minimizerName()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        for index, fitPar in enumerate(fit_suite.fitParameters()):
            plt.text(0.01, 0.55 - index*0.1,  '{:30.30s}: {:6.3f}'.format(fitPar.name(), fitPar.value()))

        plt.draw()
        plt.pause(0.01)

        if fit_suite.isLastIteration():
            plt.ioff()

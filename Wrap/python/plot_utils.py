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


def get_axes_limits(intensity):
    """
    Returns axes range as expected by pyplot.imshow.
    :param intensity: Histogram2D object from GISAS simulation
    :return:axes range
    """
    result = [intensity.getXmin(), intensity.getXmax(),
              intensity.getYmin(), intensity.getYmax()]

    # by default we assume these are radians and will show them as degrees
    if "rad" in intensity.axesUnits() or len(intensity.axesUnits())==0:
        result = [x/deg for x in result]

    return result


def plot_colormap(intensity, zmin=None, zmax=None,
                  xlabel=r'$\phi_f ^{\circ}$',
                  ylabel=r'$\alpha_f ^{\circ}$',
                  zlabel="Intensity",
                  title=None):
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
        extent=get_axes_limits(intensity),
        aspect='auto',
    )
    cb = plt.colorbar(im, pad=0.025)

    if xlabel:
        plt.xlabel(xlabel, fontsize=14)

    if ylabel:
        plt.ylabel(ylabel, fontsize=14)

    if zlabel:
        cb.set_label(zlabel, size=14)

    if title:
        plt.title(title)


def plot_intensity_data(intensity, zmin=None, zmax=None):
    """
    Plots intensity data as color map and hold the plot.
    If command line parameter was provided, save image instead of plotting.
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """
    from matplotlib import pyplot as plt
    plot_colormap(intensity, zmin, zmax)
    plt.show()


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

    def make_subplot(self, nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

    def update(self, fit_suite):
        self.fig.clf()

        self.make_subplot(1)
        real_data = fit_suite.getRealData()
        plot_colormap(real_data, title="\"Real\" data",
                      zmin=1.0, zmax=real_data.getMaximum(),
                      xlabel=None, ylabel=None, zlabel=None)

        self.make_subplot(2)
        sim_data = fit_suite.getSimulationData()
        plot_colormap(sim_data, title="Simulated data",
                      zmin=1.0, zmax=real_data.getMaximum(),
                      xlabel=None, ylabel=None, zlabel=None)

        self.make_subplot(3)
        chi_data = fit_suite.getChiSquaredMap()
        plot_colormap(chi_data, title="Chi2 map",
                      zmin=0.001, zmax=10.0,
                      xlabel=None, ylabel=None, zlabel=None)

        self.make_subplot(4)
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

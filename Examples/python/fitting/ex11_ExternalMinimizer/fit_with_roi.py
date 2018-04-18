"""
Prototype of SimulationBuilder and FitObject to work together with
external minimizer.
"""
import bornagain as ba
from bornagain import nm, deg, angstrom
import numpy as np
import lmfit
from simulation_builder import SimulationBuilder
from fit_objects import FitObject
from matplotlib import pyplot as plt


class Plotter:
    def __init__(self, fit_object):

        self.m_fit_object = fit_object
        self._fig = plt.figure(figsize=(10.25, 7.69))
        self._fig.canvas.draw()

    def make_subplot(self, nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

    def reset(self):
        self._fig.clf()

    def plot(self, params, iter, residual):
        self.reset()

        sim_data = self.m_fit_object.simulationResult()
        real_data = self.m_fit_object.experimentalData()
        diff = self.m_fit_object.relativeDifference()

        # same limits for both plots
        arr = real_data.array()
        zmax = np.amax(arr)
        zmin = zmax * 1e-6

        self.make_subplot(1)
        ba.plot_colormap(real_data, title="Real data",
                          zmin=zmin, zmax=zmax, zlabel='')

        self.make_subplot(2)
        ba.plot_colormap(sim_data, title="Simulated data",
                          zmin=zmin, zmax=zmax, zlabel='')

        self.make_subplot(3)
        ba.plot_colormap(diff, title="Relative difference",
                          zmin=1e-03, zmax=10, zlabel='')

        self.make_subplot(4)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iterations  {:d}". format(iter))
        for index, p in enumerate(params):
            print(index, p)
            plt.text(0.01, 0.55 - index * 0.1,
                     '{:30.30s}: {:6.3f}'.format(p, params[p].value))

        plt.tight_layout()
        plt.pause(0.03)



class SimulationROIBuilder(SimulationBuilder):
    def __init__(self):
        super(SimulationROIBuilder, self).__init__()

    def build_simulation(self, params=None):
        sim = super(SimulationROIBuilder, self).build_simulation(params)
        sim.setRegionOfInterest(-0.5*deg, 0.2*deg, 0.5*deg, 1.8*deg)

        return sim


def create_experimental_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    simulation = SimulationROIBuilder().build_simulation()
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with noise to produce "real" data
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def run_fitting():
    real_data = create_experimental_data()

    fit_object = FitObject()
    fit_object.set_data(SimulationROIBuilder(), real_data)

    params = lmfit.Parameters()
    params.add('radius', value=8*nm)
    params.add('length', value=8*nm)

    plotter = Plotter(fit_object)

    result = lmfit.minimize(fit_object.evaluate, params, iter_cb=plotter.plot)

    result.params.pretty_print()


if __name__ == '__main__':
    run_fitting()
    plt.show()

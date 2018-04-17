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


def create_experimental_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    simulation = SimulationBuilder().build_simulation()
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
    fit_object.set_data(SimulationBuilder(), real_data)

    params = lmfit.Parameters()
    params.add('radius', value=8*nm)
    params.add('length', value=8*nm)

    result = lmfit.minimize(fit_object.evaluate, params)

    result.params.pretty_print()


if __name__ == '__main__':
    run_fitting()

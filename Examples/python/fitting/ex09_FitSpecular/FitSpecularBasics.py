"""
Example demonstrates how to fit specular data.
Our sample represents twenty interchanging layers of Ti and Ni. We will fit
thicknesses of all Ti layers, assuming them being equal.

Reference data was generated with GENX for ti layers' thicknesses equal to 3 nm
"""

import numpy as np
import bornagain as ba
from matplotlib import pyplot as plt
from os import path

# beam wavelength
wavelength = 1.54 * ba.angstrom

# substrate (Si)
bc_si = 4.1491 * ba.angstrom * 1e-5  # bound coherent scattering length for Si
density_si = 0.0499 / ba.angstrom ** 3  # Si atomic number density

# layers' parameters
n_repetitions = 10
# Ni
bc_ni = 10.3 * ba.angstrom * 1e-5
density_ni = 0.0915 / ba.angstrom ** 3
d_ni = 70 * ba.angstrom
# Ti
bc_ti = -3.438 * ba.angstrom * 1e-5
density_ti = 0.0567 / ba.angstrom ** 3
d_ti = 30 * ba.angstrom


def get_sample():
    # defining materials
    m_air = ba.MaterialBySLD()
    m_ni = ba.MaterialBySLD("Ni", density_ni * bc_ni, 0.0)
    m_ti = ba.MaterialBySLD("Ti", density_ti * bc_ti, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", density_si * bc_si, 0.0)

    # air layer and substrate form multi layer
    air_layer = ba.Layer(m_air)
    ni_layer = ba.Layer(m_ni, d_ni)
    ti_layer = ba.Layer(m_ti, d_ti)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    for i in range(n_repetitions):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(axis):
    """
    Create and return specular simulation with its instrument defined
    """
    simulation = ba.SpecularSimulation()
    simulation.setBeamParameters(wavelength, axis)
    return simulation


def create_real_data():
    """
    Loading data from genx_interchanging_layers.dat
    """
    filepath = path.join(path.dirname(path.realpath(__file__)),
                                      "genx_interchanging_layers.dat.gz")
    ax_values, real_data = np.loadtxt(filepath,
                                      usecols=(0, 1), skiprows=3, unpack=True)

    # translating axis values from double incident angle (degrees)
    # to incident angle (radians)
    ax_values *= np.pi / 360

    return ax_values, real_data


def make_axis(ax_values):
    """
    Create BornAgain axis from given axis values
    :param ax_values: ndarray, values on axis
    :return: BornAgain.IAxis
    """
    name = "inc_angles"
    nbins = ax_values.size
    boundaries = np.array([(ax_values[i] + ax_values[i+1])/2
                           for i in range(nbins-1)])
    boundaries = np.insert(boundaries, 0, 2 * boundaries[0] - boundaries[1])
    boundaries = np.insert(boundaries, nbins, 2 * boundaries[-1] - boundaries[-2])
    return ba.VariableBinAxis(name, nbins, boundaries)


def run_fitting():
    """
    main function to run fitting
    """
    ax_values, real_data = create_real_data()
    axis = make_axis(ax_values)

    simulation = get_simulation(axis)
    sample = get_sample()
    simulation.setSample(sample)

    print(simulation.treeToString())
    print(simulation.parametersToString())

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    draw_observer = ba.DefaultFitObserver(draw_every_nth=10,
                                          SimulationType='Specular')
    fit_suite.attachObserver(draw_observer)

    fitPar = ba.FitParameter(5. * ba.nm, ba.AttLimits.limited(1. * ba.nm,
                                                              7. * ba.nm))
    fitPar.setName("thickness")
    for odd in [1, 3, 5, 7, 9]: # adding patterns for all odd layers' thicknesses
        fitPar.addPattern("*" + str(odd) + "/Thickness*")
    fit_suite.addFitParameter(fitPar)

    strategy1 = ba.AdjustMinimizerStrategy("Minuit2", "Migrad",
                                           "Strategy=2;Tolerance=1e-5")
    fit_suite.addFitStrategy(strategy1)

    # prints defined fit parameters and their relation to instrument parameters
    print(fit_suite.setupToString())

    # running fit
    print("Starting the fitting")
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())


if __name__ == '__main__':
    run_fitting()
    plt.show()

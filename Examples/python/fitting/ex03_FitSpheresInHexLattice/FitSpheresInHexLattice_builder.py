"""
Two parameter fit of spheres in a hex lattice.
Sample builder approach is used.
"""

import numpy as np
import ctypes
import bornagain as ba
from matplotlib import pyplot as plt
from bornagain import deg, angstrom, nm


class MySampleBuilder(ba.IMultiLayerBuilder):
    """
    Sample builder is used to build complex samples from set of parameters.
    Given builder produces the sample representing spheres at hex lattice
    using two parameters as an input:
    radius - radius of spheres
    lattice_constant - hexagonal lattice constant
    """
    def __init__(self):
        ba.IMultiLayerBuilder.__init__(self)
        self.sample = None
        # parameters describing the sample
        self.radius = ctypes.c_double(5.0*nm)
        self.lattice_constant = ctypes.c_double(10.0*nm)
        # register parameters
        self.registerParameter("radius", ctypes.addressof(self.radius))
        self.registerParameter("lattice_constant",
                               ctypes.addressof(self.lattice_constant))

    # constructs the sample for current values of parameters
    def buildSample(self):
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

        sphere_ff = ba.FormFactorFullSphere(self.radius.value)
        sphere = ba.Particle(m_particle, sphere_ff)
        particle_layout = ba.ParticleLayout()
        particle_layout.addParticle(sphere)

        interference = ba.InterferenceFunction2DLattice.createHexagonal(
            self.lattice_constant.value)
        pdf = ba.FTDecayFunction2DCauchy(10*nm, 10*nm)
        interference.setDecayFunction(pdf)

        particle_layout.setInterferenceFunction(interference)

        air_layer = ba.Layer(m_air)
        air_layer.addLayout(particle_layout)
        substrate_layer = ba.Layer(m_substrate, 0)
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate_layer)
        return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)

    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample_builder = MySampleBuilder()
    sample_builder.setParameterValue("radius", 5.0*nm)
    sample_builder.setParameterValue("lattice_constant", 10.0*nm)
    simulation = get_simulation()
    simulation.setSampleBuilder(sample_builder)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    # random seed made as in FitSPheresInHexLattice.py example
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    simulation.setSampleBuilder(MySampleBuilder())

    real_data = create_real_data()

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*radius", 8.*nm, ba.AttLimits.limited(4., 12.))
    fit_suite.addFitParameter("*lattice_constant",
                              8.*nm, ba.AttLimits.limited(4., 12.))

    print(fit_suite.treeToString())
    print(fit_suite.parametersToString())

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())


if __name__ == '__main__':
    run_fitting()
    plt.show()

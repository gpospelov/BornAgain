"""
Two parameter fit of spheres in a hex lattice.
Sample builder approach is used.
"""

import math
import random
import ctypes
import bornagain as ba
from bornagain import degree, angstrom, nanometer


class MySampleBuilder(ISampleBuilder):
    """
    Sample builder is used to build complex samples from set of parameters.
    Given builder produces the sample representing spheres at hex lattice using two parameters as an input:
    radius - radius of spheres
    lattice_constant - hexagonal lattice constant
    """
    def __init__(self):
        ISampleBuilder.__init__(self)
        self.sample = None
        # parameters describing the sample
        self.radius = ctypes.c_double(5.0*nanometer)
        self.lattice_constant = ctypes.c_double(10.0*nanometer)
        # register parameters
        self.registerParameter("radius", ctypes.addressof(self.radius))
        self.registerParameter("lattice_constant", ctypes.addressof(self.lattice_constant))

    # constructs the sample for current values of parameters
    def buildSample(self):
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

        sphere_ff = ba.FormFactorFullSphere(self.radius.value)
        sphere = ba.Particle(m_particle, sphere_ff)
        particle_layout = ba.ParticleLayout()
        particle_layout.addParticle(sphere)

        interference = ba.InterferenceFunction2DLattice.createHexagonal(self.lattice_constant.value)
        pdf = ba.FTDecayFunction2DCauchy(10*nanometer, 10*nanometer)
        interference.setDecayFunction(pdf)

        particle_layout.addInterferenceFunction(interference)

        air_layer = ba.Layer(m_air)
        air_layer.addLayout(particle_layout)
        substrate_layer = ba.Layer(m_substrate, 0)
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate_layer)
        self.sample = multi_layer
        return self.sample


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample_builder = MySampleBuilder()
    sample_builder.setParameterValue("radius", 5.0*nanometer)
    sample_builder.setParameterValue("lattice_constant", 10.0*nanometer)

    simulation = get_simulation()
    simulation.setSampleBuilder(sample_builder)

    simulation.runSimulation()
    real_data = simulation.getIntensityData()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    for i in range(0, real_data.getTotalNumberOfBins()):
        amplitude = real_data.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = random.gauss(amplitude, sigma)
        if noisy_amplitude < 0.1:
            noisy_amplitude = 0.1
        real_data.setBinContent(i, noisy_amplitude)
    return real_data


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    sample_builder = MySampleBuilder()
    simulation.setSampleBuilder(sample_builder)
    simulation.printParameters()

    real_data = create_real_data()

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(1)

    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*radius", 8.*nanometer, ba.AttLimits.limited(4., 12.))
    fit_suite.addFitParameter("*lattice_constant", 8.*nanometer, ba.AttLimits.limited(4., 12.))

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print(fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError())


if __name__ == '__main__':
    run_fitting()
    plt.show()


"""
Two parameter fit of spheres in a hex lattice.
"""

from matplotlib import pyplot as plt
import math
import random
from bornagain import *


def get_sample(radius=5*nanometer, lattice_constant=10*nanometer):
    """
    Build the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    sphere_ff = FormFactorFullSphere(radius)
    sphere = Particle(m_particle, sphere_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(sphere)

    interference = InterferenceFunction2DLattice.createHexagonal(lattice_constant)
    pdf = FTDecayFunction2DCauchy(10*nanometer, 10*nanometer)
    interference.setDecayFunction(pdf)

    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample = get_sample(5.0*nanometer, 10.0*nanometer)

    simulation = get_simulation()
    simulation.setSample(sample)

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
    sample = get_sample()
    sample.printParameters()
    simulation.setSample(sample)

    real_data = create_real_data()

    fit_suite = FitSuite()
    fit_suite.setMinimizer("GSLLMA")
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    draw_observer = DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # this fit parameter will change both length_1 and length_2 simultaneously
    fit_suite.addFitParameter("*2DLattice/LatticeLength*", 8.*nanometer, AttLimits.limited(4., 12.))
    fit_suite.addFitParameter("*/FullSphere/Radius", 8.*nanometer, AttLimits.limited(4., 12.))

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


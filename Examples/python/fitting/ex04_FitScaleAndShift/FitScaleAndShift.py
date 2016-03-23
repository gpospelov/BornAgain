"""
Fitting example: looking for background and scale factors.

Real data contains some "unknown" background and scale factors.
In the fit we are trying to find cylinder radius and height, scale and background factors.
"""

from __future__ import print_function
import numpy
import matplotlib
import math
import random
from bornagain import *


def get_sample(radius=5*nanometer, height=10*nanometer):
    """
    Build the sample representing cylinders on top of substrate without interference.
    """
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    cylinder_ff = FormFactorCylinder(radius, height)
    cylinder = Particle(m_particle, cylinder_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder)

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
    simulation.setBeamIntensity(1e12)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise, background  and scale to the simulated data.
    Cylinder radius is set to 5nm, cylinder height to 10nm.
    During the fit we will try to find cylinder height and radius and scale, background factors.
    """
    sample = get_sample(5.0*nanometer, 10.0*nanometer)

    simulation = get_simulation()
    simulation.setSample(sample)

    simulation.runSimulation()
    real_data = simulation.getIntensityData()

    scale = 2.0
    background = 100
    real_data.scale(scale)

    # spoiling simulated data with the noise and adding background to produce "real" data
    noise_factor = 1.0
    for i in range(0, real_data.getTotalNumberOfBins()):
        amplitude = real_data.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = random.gauss(amplitude, sigma)
        if noisy_amplitude < 1.0:
            noisy_amplitude = 1.0
        real_data.setBinContent(i, noisy_amplitude + background)
    return real_data


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    sample = get_sample()

    simulation.setSample(sample)

    real_data = create_real_data()

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)

    chiModule = ChiSquaredModule()
    chiModule.setIntensityNormalizer(IntensityScaleAndShiftNormalizer())
    fit_suite.setChiSquaredModule(chiModule)

    fit_suite.initPrint(10)

    draw_observer = DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    fit_suite.getFitObjects().printParameters()  # prints all defined parameters for sample and simulation

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/Cylinder/Radius", 6.*nanometer, AttLimits.limited(4., 8.))
    fit_suite.addFitParameter("*/Cylinder/Height", 9.*nanometer, AttLimits.limited(8., 12.))
    fit_suite.addFitParameter("*/Normalizer/scale", 1.5, AttLimits.limited(1.0, 3.0))
    fit_suite.addFitParameter("*/Normalizer/shift", 50., AttLimits.limited(1, 500.))

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getMinimizer().getMinValue())
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print(fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError())


if __name__ == '__main__':
    run_fitting()
    plt.show()


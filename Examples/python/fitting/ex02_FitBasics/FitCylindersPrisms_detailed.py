"""
Fitting example: 4 parameters fit with simple output
This is more detailed version of ba.FitCylindersPrisms.py.
We show how to generate "real" data and how to draw fit progress.
Please take a note, that performance here is determined
by poor performance of matplotlib drawing routines.
"""

import math
import random
import bornagain as ba
from matplotlib import pyplot as plt
from bornagain import deg, angstrom, nm


def get_sample(cylinder_height=1.0*nm, cylinder_radius=1.0*nm,
               prism_length=2.0*nm, prism_height=1.0*nm):
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(prism_length, prism_height)
    prism = ba.Particle(m_particle, prism_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    This function has been used once to generate refdata_fitcylinderprisms.int
    located in same directory.
    """
    # creating sample with set of parameters we will later try to find during the fit
    sample = get_sample(5.0*nm, 5.0*nm, 5.0*nm, 5.0*nm)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with noise to produce "real" data
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    return simulation


def run_fitting():
    """
    Setup simulation and fit
    """

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = create_real_data()

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)

    # fit_suite.setMinimizer("Minuit2", "Migrad")  # ba.Default
    # fit_suite.setMinimizer("Minuit2", "Fumili")
    # fit_suite.setMinimizer("GSLLMA")

    fit_suite.initPrint(10)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*Cylinder/Height", 4.*nm).setLowerLimited(0.01)
    fit_suite.addFitParameter("*Cylinder/Radius", 6.*nm).setLowerLimited(0.01)
    fit_suite.addFitParameter("*Prism3/Height", 4.*nm).setLowerLimited(0.01)
    fit_suite.addFitParameter("*Prism3/BaseEdge", 12.*nm).setLowerLimited(0.01)

    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    fit_suite.runFit()
    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())

    return fit_suite


if __name__ == '__main__':
    run_fitting()
    plt.show()

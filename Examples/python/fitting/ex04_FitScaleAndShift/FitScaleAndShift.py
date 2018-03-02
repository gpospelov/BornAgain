"""
Fitting example: looking for background and scale factors.

Real data contains some "unknown" background and scale factors.
In the fit we are trying to find cylinder radius and height,
scale and background factors.
"""

import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(radius=5.0*nm, height=10.0*nm):
    """
    Build the sample representing cylinders on top of substrate without interference.
    """
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    cylinder_ff = ba.FormFactorCylinder(radius, height)
    cylinder = ba.Particle(m_particle, cylinder_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)

    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e12)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise, background and scale
    to the simulated data.
    Cylinder radius is set to 5nm, cylinder height to 10nm.
    During the fit we will try to find cylinder height and radius and
    scale, background factors.
    """
    sample = get_sample(5.0*nm, 10.0*nm)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    scale = 2.0
    background = 100

    # spoiling simulated data with the noise to produce "real" data
    real_data *= scale
    noise_factor = 0.1
    noisy = background + np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    return noisy


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    sample = get_sample()

    simulation.setSample(sample)

    real_data = create_real_data()

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)

    chiModule = ba.ChiSquaredModule()
    chiModule.setIntensityNormalizer(ba.IntensityScaleAndShiftNormalizer())
    fit_suite.setChiSquaredModule(chiModule)

    fit_suite.initPrint(10)

    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # print all defined parameters for sample and simulation
    print(fit_suite.parametersToString())

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/Cylinder/Radius", 6.*nm,
                              ba.AttLimits.limited(4., 8.))
    fit_suite.addFitParameter("*/Cylinder/Height", 9.*nm,
                              ba.AttLimits.limited(8., 12.))
    fit_suite.addFitParameter("*/Normalizer/scale", 1.5,
                              ba.AttLimits.limited(1.0, 3.0))
    fit_suite.addFitParameter("*/Normalizer/shift", 50.,
                              ba.AttLimits.limited(1, 500.))

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())


if __name__ == '__main__':
    run_fitting()
    plt.show()

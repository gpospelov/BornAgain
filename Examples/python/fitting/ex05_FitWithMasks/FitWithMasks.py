"""
Fitting example: fit with masks
"""

from __future__ import print_function
from matplotlib import pyplot as plt
import math
import random
import bornagain as ba
from bornagain import degree, angstrom, nanometer


def get_sample(radius=5*nanometer, height=10*nanometer):
    """
    Build the sample representing cylinders on top of
    substrate without interference.
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
    noise_factor = 0.5
    for i in range(0, real_data.getTotalNumberOfBins()):
        amplitude = real_data.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = random.gauss(amplitude, sigma)
        if noisy_amplitude < 1.0:
            noisy_amplitude = 1.0
        real_data.setBinContent(i, noisy_amplitude)
    return real_data


def add_mask_to_simulation(simulation):
    """
    Here we demonstrate how to add masks to the simulation.
    Only unmasked areas will be simulated and then used during the fit.

    Masks can have different geometrical shapes (ba.Rectangle, ba.Ellipse, Line) with the mask value either
    "True" (detector bin is excluded from the simulation) or False (will be simulated).

    Every subsequent mask override previously defined masks in this area.

    In the code below we put masks in such way that simulated image will look like
    a Pac-Man from ancient arcade game.
    """
    # mask all detector (put mask=True to all detector channels)
    simulation.maskAll()

    # set mask to simulate pacman's head
    simulation.addMask(ba.Ellipse(0.0*degree, 1.0*degree, 0.5*degree, 0.5*degree), False)

    # set mask for pacman's eye
    simulation.addMask(ba.Ellipse(0.11*degree, 1.25*degree, 0.05*degree, 0.05*degree), True)

    # set mask for pacman's mouth
    points = [[0.0*degree, 1.0*degree], [0.5*degree, 1.2*degree], [0.5*degree, 0.8*degree], [0.0*degree, 1.0*degree]]
    simulation.addMask(ba.Polygon(points), True)

    # giving pacman something to eat
    simulation.addMask(ba.Rectangle(0.45*degree, 0.95*degree, 0.55*degree, 1.05*degree), False)
    simulation.addMask(ba.Rectangle(0.61*degree, 0.95*degree, 0.71*degree, 1.05*degree), False)
    simulation.addMask(ba.Rectangle(0.75*degree, 0.95*degree, 0.85*degree, 1.05*degree), False)

    # other mask's shapes are possible too
    # simulation.removeMasks()
    # simulation.addMask(ba.Ellipse(0.11*degree, 1.25*degree, 1.0*degree, 0.5*degree, 45.0*degree), True) # rotated ellipse
    # simulation.addMask(Line(-1.0*degree, 0.0*degree, 1.0*degree, 2.0*degree), True)
    # simulation.addMask(ba.HorizontalLine(1.0*degree), False)
    # simulation.addMask(ba.VerticalLine(0.0*degree), False)


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    sample = get_sample()
    simulation.setSample(sample)

    # the core method of this example which adds masks to the simulation
    add_mask_to_simulation(simulation)

    real_data = create_real_data()

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)
    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/Cylinder/Radius", 6.*nanometer, ba.AttLimits.limited(4., 8.))
    fit_suite.addFitParameter("*/Cylinder/Height", 9.*nanometer, ba.AttLimits.limited(8., 12.))

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    fit_suite.printResults()
    print("chi2:", fit_suite.getChi2())
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print(fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError())


if __name__ == '__main__':
    run_fitting()
    plt.show()


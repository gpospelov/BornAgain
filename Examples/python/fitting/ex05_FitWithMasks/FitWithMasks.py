"""
Fitting example: fit with masks
"""

import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(radius=5.0*nm, height=10.0*nm):
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
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample = get_sample(5.0*nm, 10.0*nm)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def add_mask_to_simulation(simulation):
    """
    Here we demonstrate how to add masks to the simulation.
    Only unmasked areas will be simulated and then used during the fit.

    Masks can have different geometrical shapes (ba.Rectangle, ba.Ellipse, Line)
    with the mask value either "True" (detector bin is excluded from the simulation)
    or False (will be simulated).

    Every subsequent mask override previously defined masks in this area.

    In the code below we put masks in such way that simulated image will look like
    a Pac-Man from ancient arcade game.
    """
    # mask all detector (put mask=True to all detector channels)
    simulation.maskAll()

    # set mask to simulate pacman's head
    simulation.addMask(
        ba.Ellipse(0.0*deg, 1.0*deg, 0.5*deg, 0.5*deg), False)

    # set mask for pacman's eye
    simulation.addMask(
        ba.Ellipse(0.11*deg, 1.25*deg, 0.05*deg, 0.05*deg), True)

    # set mask for pacman's mouth
    points = [[0.0*deg, 1.0*deg], [0.5*deg, 1.2*deg],
              [0.5*deg, 0.8*deg], [0.0*deg, 1.0*deg]]
    simulation.addMask(ba.Polygon(points), True)

    # giving pacman something to eat
    simulation.addMask(
        ba.Rectangle(0.45*deg, 0.95*deg, 0.55*deg, 1.05*deg), False)
    simulation.addMask(
        ba.Rectangle(0.61*deg, 0.95*deg, 0.71*deg, 1.05*deg), False)
    simulation.addMask(
        ba.Rectangle(0.75*deg, 0.95*deg, 0.85*deg, 1.05*deg), False)

    # other mask's shapes are possible too
    # simulation.removeMasks()
    # # rotated ellipse:
    # simulation.addMask(ba.Ellipse(0.11*deg, 1.25*deg,
    #                    1.0*deg, 0.5*deg, 45.0*deg), True)
    # simulation.addMask(Line(-1.0*deg, 0.0*deg, 1.0*deg, 2.0*deg), True)
    # simulation.addMask(ba.HorizontalLine(1.0*deg), False)
    # simulation.addMask(ba.VerticalLine(0.0*deg), False)


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
    fit_suite.addFitParameter("*/Cylinder/Radius", 6.*nm).setLimited(4., 8.)
    fit_suite.addFitParameter("*/Cylinder/Height", 9.*nm).setLimited(8., 12.)

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    fit_suite.printResults()
    print("chi2:", fit_suite.getChi2())
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())


if __name__ == '__main__':
    run_fitting()
    plt.show()

"""
Real life example: experiment at GALAXY
"""
import matplotlib
from matplotlib import pyplot as plt
import math
import random
import numpy
import bornagain as ba
from SampleBuilder import MySampleBuilder

wavelength = 1.34*ba.angstrom
alpha_i = 0.463*ba.degree


def create_detector():
    """
    Creates and returns GALAXY detector
    """
    # detector setup as given from instrument responsible
    npx, npy = 981, 1043
    pixel_size = 0.172  # in mm
    detector_distance = 1730.0  # in mm
    beam_xpos, beam_ypos = 597.1, 323.4  # in pixels

    u0 = beam_xpos*pixel_size  # in mm
    v0 = beam_ypos*pixel_size  # in mm
    detector = ba.RectangularDetector(npx, npx*pixel_size, npy, npy*pixel_size)
    detector.setPerpendicularToDirectBeam(detector_distance, u0, v0)
    return detector


def create_simulation():
    """
    Creates and returns GISAS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetector(create_detector())
    simulation.setBeamParameters(wavelength, alpha_i, 0.0)
    simulation.setBeamIntensity(1.2e7)
    # mask on reflected beam
    simulation.addMask(ba.Rectangle(101.9, 82.1, 103.7, 85.2), True)
    return simulation


def load_real_data(hist, filename="galaxi_data.tif.gz"):
    """
    Fill histogram representing our detector with intensity data from tif file.
    Returns cropped version of it, which represent the area we are interested in.
    """
    hist.load(filename)
    return hist.crop(85.0, 70.0, 120.0, 92.)


def run_fitting():
    simulation = create_simulation()
    sample_builder = MySampleBuilder()
    simulation.setSampleBuilder(sample_builder)

    real_data = load_real_data(simulation.getIntensityData())

    fit_suite = ba.FitSuite()
    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)
    fit_suite.initPrint(10)
    fit_suite.addSimulationAndRealData(simulation, real_data)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*radius", 4.9*ba.nanometer, ba.AttLimits.limited(4.0, 6.0), 0.1*ba.nanometer)
    fit_suite.addFitParameter("*sigma", 0.5, ba.AttLimits.limited(0.2, 0.8), 0.01*ba.nanometer)
    fit_suite.addFitParameter("*distance", 47.*ba.nanometer, ba.AttLimits.limited(20, 70), 0.1*ba.nanometer)

    strategy1 = ba.FitStrategyAdjustMinimizer("Genetic")
    strategy1.getMinimizerOptions().setMaxIterations(3)
    fit_suite.addFitStrategy(strategy1)

    # Second fit strategy will use another algorithm. It will use best parameters found from previous minimization round.
    strategy2 = ba.FitStrategyAdjustMinimizer("Minuit2", "Migrad")
    fit_suite.addFitStrategy(strategy2)

    # running fit
    fit_suite.runFit()

    plt.show()

if __name__ == '__main__':
    run_fitting()

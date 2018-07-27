"""
Real life example: experiment at GALAXY
"""
import matplotlib
from matplotlib import pyplot as plt
import numpy
import bornagain as ba
from SampleBuilder import MySampleBuilder

wavelength = 1.34*ba.angstrom
alpha_i = 0.463*ba.deg

# detector setup as given from instrument responsible
pilatus_npx, pilatus_npy = 981, 1043
pilatus_pixel_size = 0.172  # in mm
detector_distance = 1730.0  # in mm
beam_xpos, beam_ypos = 597.1, 323.4  # in pixels


def create_detector():
    """
    Returns a model of the GALAXY detector
    """
    u0 = beam_xpos*pilatus_pixel_size  # in mm
    v0 = beam_ypos*pilatus_pixel_size  # in mm
    detector = ba.RectangularDetector(pilatus_npx, pilatus_npx*pilatus_pixel_size,
                                      pilatus_npy, pilatus_npy*pilatus_pixel_size)
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
    simulation.setRegionOfInterest(85.0, 70.0, 120.0, 92.)
    # mask on reflected beam
    simulation.addMask(ba.Rectangle(101.9, 82.1, 103.7, 85.2), True)
    # detector resolution function
    # simulation.setDetectorResolutionFunction(
    #   ba.ResolutionFunction2DGaussian(0.5*pilatus_pixel_size,
    #      0.5*pilatus_pixel_size))
    # beam divergence
    # alpha_distr = ba.DistributionGaussian(alpha_i, 0.02*ba.deg)
    # simulation.addParameterDistribution("*/Beam/Alpha", alpha_distr, 5)
    return simulation


def load_real_data(filename="galaxi_data.tif.gz"):
    """
    Fill histogram representing our detector with intensity data from tif file.
    Returns cropped version of it, which represent the area we are interested in.
    """
    hist = ba.IHistogram.createFrom(filename)
    return hist


def run_fitting():
    simulation = create_simulation()
    sample_builder = MySampleBuilder()
    simulation.setSampleBuilder(sample_builder)

    real_data = load_real_data()

    fit_suite = ba.FitSuite()
    draw_observer = ba.DefaultFitObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)
    fit_suite.initPrint(10)
    fit_suite.addSimulationAndRealData(simulation, real_data)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter(
        "*radius", 5.0*ba.nm, ba.AttLimits.limited(4.0, 6.0),
        0.1*ba.nm)
    fit_suite.addFitParameter(
        "*sigma", 0.55, ba.AttLimits.limited(0.2, 0.8), 0.01*ba.nm)
    fit_suite.addFitParameter(
        "*distance", 27.*ba.nm, ba.AttLimits.limited(20, 70),
        0.1*ba.nm)

    use_two_minimizers_strategy = False
    if use_two_minimizers_strategy:
        strategy1 = ba.AdjustMinimizerStrategy("Genetic")
        fit_suite.addFitStrategy(strategy1)

        # Second fit strategy will use another algorithm.
        # It will use best parameters found from previous minimization round.
        strategy2 = ba.AdjustMinimizerStrategy("Minuit2", "Migrad")
        fit_suite.addFitStrategy(strategy2)

    # running fit
    fit_suite.runFit()

    plt.show()

if __name__ == '__main__':
    run_fitting()

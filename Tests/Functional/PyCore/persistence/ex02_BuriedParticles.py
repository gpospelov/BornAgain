"""
Spherical particles embedded in the middle of the layer on top of substrate.
"""
from BuriedParticles import *
import bornagain as ba

def test_simulation():
    """
    Returns a GISAXS simulation.
    """
    simulation = ba.GISASSimulation()
    simulation.setSample(get_sample())
    simulation.setDetectorParameters(5, -1*deg, +1*deg, 6, 0*deg, +2*deg)
    simulation.setBeamParameters(1.5*angstrom, 0.15*deg, 0.0*deg)
    return simulation


if __name__ == '__main__':
    simulation = test_simulation()
    simulation.runSimulation()
    result = simulation.getIntensityData()
    ba.plot_intensity_data(result)

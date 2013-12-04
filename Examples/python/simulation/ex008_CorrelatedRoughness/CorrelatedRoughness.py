import numpy
import matplotlib
import pylab
from math import degrees, pi, sin, cos, radians
from libBornAgainCore import *


wavelength = 1.0 # angstrom
ai = 0.2 # degrees

Nalpha = 200
Nphi = 200

astart = 0 # degrees
aend = 1 # degrees
pstart = -0.5
pend = 0.5


def plot_with_pylab(data):
    result = data.getArray() + 1  # for log scale
    axis_phi = data.getAxis(0)
    axis_alpha = data.getAxis(1)

    pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                 extent=[degrees(axis_phi.getMin()), degrees(axis_phi.getMax()), degrees(axis_alpha.getMin()), degrees(axis_alpha.getMax())])
    pylab.xlabel(r'$\phi_f$', fontsize=20)
    pylab.ylabel(r'$\alpha_f$', fontsize=20)

    pylab.show()


def get_sample():
    """
    Build and return the sample representing the layers with correlated roughness.
    """
    m_ambience = MaterialManager.getHomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = MaterialManager.getHomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = MaterialManager.getHomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = MaterialManager.getHomogeneousMaterial("substrate", 15e-6, 0.0)

    l_ambience = Layer(m_ambience, 0)
    l_part_a = Layer(m_part_a, 2.5*nanometer)
    l_part_b = Layer(m_part_b, 5.0*nanometer)
    l_substrate = Layer(m_substrate, 0)

    roughness = LayerRoughness()
    roughness.setSigma(1.0*nanometer)
    roughness.setHurstParameter(0.3)
    roughness.setLatteralCorrLength(5*nanometer)

    my_sample = MultiLayer()

    # adding layers
    my_sample.addLayer(l_ambience)

    n_repetitions = 5
    for i in range(n_repetitions):
        my_sample.addLayerWithTopRoughness(l_part_a, roughness)
        my_sample.addLayerWithTopRoughness(l_part_b, roughness)

    my_sample.addLayerWithTopRoughness(l_substrate, roughness)
    my_sample.setCrossCorrLength(1e-4)

    return my_sample


def set_parameters():
    """
    characterizing the input beam and output detector
    """
    simulation = Simulation()
    simulation.setDetectorParameters(Nphi, pstart*degree, pend*degree, Nalpha, astart*degree, aend*degree, True)
    simulation.setBeamParameters(wavelength*angstrom, ai*degree, 0.0*degree)

    return simulation


def run_simulation():
    sample = get_sample()
    simulation = set_parameters()
    simulation.setSample(sample)
    simulation.runSimulation()
    data = simulation.getIntensityData()
    return data


if __name__ == '__main__':
    data = run_simulation()
    plot_with_pylab(data)


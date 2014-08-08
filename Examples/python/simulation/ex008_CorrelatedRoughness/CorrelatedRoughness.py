import numpy
import matplotlib
import pylab
from math import degrees
from libBornAgainCore import *


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
    m_ambience = HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = HomogeneousMaterial("substrate", 15e-6, 0.0)

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


def get_simulation():
    """
    characterizing the input beam and output detector
    """
    simulation = Simulation()
    simulation.setDetectorParameters(200, -0.5*degree, 0.5*degree, 200, 0.0*degree, 1.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    return simulation


def run_simulation():
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData()
    return result


if __name__ == '__main__':
    data = run_simulation()
    plot_with_pylab(data)


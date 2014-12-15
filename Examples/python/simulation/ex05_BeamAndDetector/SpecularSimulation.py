"""
R and T coefficients in multilayer, Specular simulation
"""
import numpy
import matplotlib
import pylab
import cmath
from bornagain import *


alpha_i_min, alpha_i_max = 0.0, 2.0  # incoming beam


def get_sample():
    """
    Build and return the sample representing the layers with correlated roughness.
    """
    m_ambience = HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = HomogeneousMaterial("substrate", 15e-6, 0.0)

    l_ambience = Layer(m_ambience)
    l_part_a = Layer(m_part_a, 5.0*nanometer)
    l_part_b = Layer(m_part_b, 10.0*nanometer)
    l_substrate = Layer(m_substrate)

    roughness = LayerRoughness()
    roughness.setSigma(1.0*nanometer)
    roughness.setHurstParameter(0.3)
    roughness.setLatteralCorrLength(500.0*nanometer)

    my_sample = MultiLayer()

    # adding layers
    my_sample.addLayer(l_ambience)

    n_repetitions = 10
    for i in range(n_repetitions):
        my_sample.addLayerWithTopRoughness(l_part_a, roughness)
        my_sample.addLayerWithTopRoughness(l_part_b, roughness)

    my_sample.addLayerWithTopRoughness(l_substrate, roughness)
    # my_sample.setCrossCorrLength(1e-4)

    return my_sample


def get_simulation():
    """
    Create and return off-specular simulation with beam and detector defined
    """
    simulation = SpecularSimulation()
    # simulation.setDetectorParameters(20, phi_f_min*degree, phi_f_max*degree, 200, alpha_f_min*degree, alpha_f_max*degree)
    # defining the beam  with incidence alpha_i varied between alpha_i_min and alpha_i_max
    alpha_i_axis = FixedBinAxis("alpha_i", 1000, alpha_i_min*degree, alpha_i_max*degree)
    simulation.setBeamParameters(1.54*angstrom, alpha_i_axis)
    # simulation.setBeamIntensity(1e9)
    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    print "aaa"
    simulation.runSimulation()
    print "aaa2"

    coeff_r = []
    for r in simulation.getScalarR(0):
        coeff_r.append(numpy.abs(r))

    coeff_t = []
    for t in simulation.getScalarT(0):
        coeff_t.append(numpy.abs(t))

    alpha = simulation.getAlphaAxis().getBinCenters()


    fig = pylab.figure()
    pylab.ylim(ymax=10.0, ymin=1e-06)
    pylab.semilogy(alpha, coeff_r)
    pylab.semilogy(alpha, coeff_t)
    pylab.legend(['|R|', '|T|'], loc='upper right')

    # result = simulation.getIntensityData().getArray() + 1  # for log scale

    # showing the result
    # im = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
    #                   extent=[alpha_i_min, alpha_i_max, alpha_f_min, alpha_f_max], aspect='auto')
    # pylab.colorbar(im)
    # pylab.xlabel(r'$\alpha_i$', fontsize=16)
    # pylab.ylabel(r'$\alpha_f$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    run_simulation()

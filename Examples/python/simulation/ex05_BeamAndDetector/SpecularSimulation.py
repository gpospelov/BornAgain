"""
R and T coefficients in multilayer, ba.Specular simulation.
"""
import numpy, sys
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm

alpha_i_min, alpha_i_max = 0.0, 2.0  # incoming beam


def get_sample():
    """
    Returns a sample with two layers on a substrate, with correlated roughnesses.
    """
    m_ambience = ba.HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = ba.HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = ba.HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = ba.HomogeneousMaterial("substrate", 15e-6, 0.0)

    l_ambience = ba.Layer(m_ambience)
    l_part_a = ba.Layer(m_part_a, 5.0*nm)
    l_part_b = ba.Layer(m_part_b, 10.0*nm)
    l_substrate = ba.Layer(m_substrate)

    roughness = ba.LayerRoughness()
    roughness.setSigma(1.0*nm)
    roughness.setHurstParameter(0.3)
    roughness.setLatteralCorrLength(500.0*nm)

    my_sample = ba.MultiLayer()

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
    Returns a specular simulation with beam and detector defined.
    """
    simulation = ba.SpecularSimulation()
    simulation.setBeamParameters(
        1.54*angstrom, 1000, alpha_i_min*deg, alpha_i_max*deg)
    return simulation


def simulate():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    # plotting results for several selected layers
    selected_layers = [0, 1, 20, 21]
    alpha_angles = simulation.getAlphaAxis().getBinCenters()

    fig = plt.figure(figsize=(12.80, 10.24))

    nplot = 1
    for layer_index in selected_layers:
        R = []
        for coeff in simulation.getScalarR(layer_index):
            R.append(numpy.abs(coeff))
        T = []
        for coeff in simulation.getScalarT(layer_index):
            T.append(numpy.abs(coeff))

        plt.subplot(2, 2, nplot)
        plt.ylim(ymax=50.0, ymin=1e-06)
        plt.xlabel(r'$\alpha_f$ (rad)', fontsize=16)
        plt.semilogy(alpha_angles, R)
        plt.semilogy(alpha_angles, T)
        plt.legend(['|R| layer #'+str(layer_index),
                    '|T| layer #'+str(layer_index)],
                   loc='upper right')
        nplot = nplot + 1

    plt.show()


if __name__ == '__main__':
    simulate()

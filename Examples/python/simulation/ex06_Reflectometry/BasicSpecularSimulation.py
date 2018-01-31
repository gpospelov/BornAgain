"""
Basic example of specular simulation with BornAgain.

"""
import numpy
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

    return my_sample


def get_simulation():
    """
    Returns a specular simulation with beam and detector defined.
    """
    simulation = ba.SpecularSimulation()
    simulation.setBeamParameters(
        1.54*angstrom, 500, alpha_i_min*deg, alpha_i_max*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns it.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


def plot(data):
    """
    Plots data for several selected layers
    """
    from matplotlib import pyplot as plt
    plt.figure(figsize=(12.80, 10.24))

    hist = data.histogram1d()
    axis = hist.getXaxis().getBinCenters()
    intensities = data.array()

    plt.xlabel(r'$\alpha_f$ (rad)', fontsize=16)
    plt.semilogy(axis, intensities)
    plt.legend(['Detector signal'], loc='upper right')

    plt.show()


if __name__ == '__main__':
    results = run_simulation()
    plot(results)

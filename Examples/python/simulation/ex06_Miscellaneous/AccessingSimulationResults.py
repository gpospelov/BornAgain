"""
Extended example for simulation results treatment (cropping, slicing, exporting)
The standard "Cylinders in DWBA" sample is used to setup the simulation.
"""
import math
import numpy
import matplotlib
import random
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample to calculate cylinder formfactor in Distorted Wave Born Approximation.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def plot_as_colormap(hist, zmin=None, zmax=None):
    """
    Simple plot of intensity data as color map
    """
    if not zmin:
        zmin = 1.0

    if not zmax:
        zmax = hist.getMaximum()

    im = plt.imshow(hist.getArray(),
                    norm=matplotlib.colors.LogNorm(zmin, zmax),
                    extent=[hist.getXmin()/deg, hist.getXmax()/deg, hist.getYmin()/deg, hist.getYmax()/deg],
                    aspect='auto')
    cb = plt.colorbar(im, pad=0.025)
    plt.xlabel(r'$\phi_f ^{\circ}$', fontsize=16)
    plt.ylabel(r'$\alpha_f ^{\circ}$', fontsize=16)


def plot_cropped_map(hist):
    """
    Plot cropped version of intensity data
    """
    crop = hist.crop(-1.0*deg, 0.5*deg, 1.0*deg, 1.0*deg)
    plot_as_colormap(crop)


def get_noisy_image(hist):
    """
    Returns clone of input histogram filled with additional noise
    """
    result = hist.clone()
    noise_factor = 2.0
    for i in range(0, result.getTotalNumberOfBins()):
        amplitude = result.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = random.gauss(amplitude, sigma)
        result.setBinContent(i, noisy_amplitude)
    return result


def plot_relative_difference(hist):
    """
    Creates noisy histogram made of original histogram,
    then creates and plots a relative difference histogram: (noisy-hist)/hist
    """
    noisy = get_noisy_image(hist)
    diff = noisy.relativeDifferenceHistogram(hist)
    plot_as_colormap(diff, zmin=1e-03, zmax=10)


def plot_slices(hist):
    """
    Plot 1D slices along y-axis at certain x-axis values.
    """
    noisy = get_noisy_image(hist)

    # projection along Y, slice at fixed x-value
    proj1 = noisy.projectionY(0.0*deg)
    plt.semilogy(proj1.getBinCenters()/deg, proj1.getBinValues(), label=r'$\phi=0.0^{\circ}$')

    # projection along Y, slice at fixed x-value
    proj2 = noisy.projectionY(0.5*deg)  # slice at fixed value
    plt.semilogy(proj2.getBinCenters()/deg, proj2.getBinValues(), label=r'$\phi=0.5^{\circ}$')

    # projection along Y for all X values between [xlow, xup], averaged
    proj3 = noisy.projectionY(0.4*deg, 0.6*deg)
    plt.semilogy(proj3.getBinCenters()/deg, proj3.getArray(IHistogram.AVERAGE), label=r'$<\phi>=0.5^{\circ}$')

    plt.xlim(proj1.getXmin()/deg, proj1.getXmax()/deg)
    plt.ylim(1.0, proj1.getMaximum()*10.0)
    plt.xlabel(r'$\alpha_f ^{\circ}$', fontsize=16)
    plt.legend(loc='upper right')


def save_to_file(result):
    """
    Saves intensity data into file
    """
    result.save("result.int")
    result.save("result.tif")
    result.save("result.txt")
    result.save("result.int.gz")
    result.save("result.tif.gz")
    result.save("result.txt.gz")
    result.save("result.int.bz2")
    result.save("result.tif.bz2")
    result.save("result.txt.bz2")


def plot_results(result):
    """
    Runs different plotting functions one by one to demonstrate trivial data presentation tasks
    """

    fig = plt.figure(figsize=(12.80, 10.24))

    plt.subplot(2, 2, 1)
    plot_as_colormap(result)
    plt.title("Intensity as colormap")

    plt.subplot(2, 2, 2)
    plot_cropped_map(result)
    plt.title("Cropping")

    plt.subplot(2, 2, 3)
    plot_relative_difference(result)
    plt.title("Relative difference")

    plt.subplot(2, 2, 4)
    plot_slices(result)
    plt.title("Various slicing of 2D into 1D")

    save_to_file(result)

    plt.subplots_adjust(left=0.07, right=0.97, top=0.9, bottom=0.1, hspace=0.25)
    plt.show()


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData()

    plot_results(result)


if __name__ == '__main__':
    run_simulation()



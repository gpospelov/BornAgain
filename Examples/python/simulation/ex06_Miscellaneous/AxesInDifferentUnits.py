"""
In this example we demonstrate how to plot simulation results with
axes in different units (nbins, mm, degrees and QyQz).
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

detector_distance = 2000.0  # in mm
pilatus_pixel_size = 0.172  # in mm
pilatus_npx, pilatus_npy = 981, 1043  # number of pixels


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


def get_rectangular_detector():
    """
    Returns rectangular detector representing our PILATUS detector
    """
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = RectangularDetector(pilatus_npx, width, pilatus_npy, height)
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0)
    return detector


def get_simulation():
    """
    Create and return GISAXS simulation with beam defined
    """
    simulation = GISASSimulation()
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setDetector(get_rectangular_detector())
    return simulation


def plot_as_colormap(hist, Title, xLabel, yLabel):
    """
    Simple plot of intensity data as color map
    """

    im = plt.imshow(hist.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, hist.getMaximum()),
                    extent=[hist.getXmin(), hist.getXmax(), hist.getYmin(), hist.getYmax()],
                    aspect='auto')
    cb = plt.colorbar(im, pad=0.025)
    plt.xlabel(xLabel, fontsize=16)
    plt.ylabel(yLabel, fontsize=16)
    plt.title(Title)


def run_simulation():
    """
    Run two simulations for two different detectors and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    fig = plt.figure(figsize=(12.80, 10.24))

    plt.subplot(2, 2, 1)
    # default units for rectangular detector are millimeters
    result = simulation.getIntensityData()
    plot_as_colormap(result, "In default units", r'$X_{mm}$', r'$Y_{mm}$')

    plt.subplot(2, 2, 2)
    result = simulation.getIntensityData(IDetector2D.NBINS)
    plot_as_colormap(result, "In number of bins", r'$X_{nbins}$', r'$Y_{nbins}$')

    plt.subplot(2, 2, 3)
    result = simulation.getIntensityData(IDetector2D.DEGREES)
    plot_as_colormap(result, "In degrees", r'$\phi_f ^{\circ}$', r'$\alpha_f ^{\circ}$')

    plt.subplot(2, 2, 4)
    result = simulation.getIntensityData(IDetector2D.QYQZ)
    plot_as_colormap(result, "Q-space", r'$Q_{y} [1/nm]$', r'$Q_{z} [1/nm]$')

    plt.subplots_adjust(left=0.07, right=0.97, top=0.9, bottom=0.1, hspace=0.25)
    plt.show()


if __name__ == '__main__':
    run_simulation()



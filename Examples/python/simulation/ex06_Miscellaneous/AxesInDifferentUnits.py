"""
In this example we demonstrate how to plot simulation results with
axes in different units (nbins, mm, degs and QyQz).
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm

detector_distance = 2000.0  # in mm
pilatus_pixel_size = 0.172  # in mm
pilatus_npx, pilatus_npy = 981, 1043  # number of pixels


def get_sample():
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nm, 5*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_rectangular_detector():
    """
    Returns rectangular detector representing our PILATUS detector
    """
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = ba.RectangularDetector(pilatus_npx, width, pilatus_npy, height)
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0)
    return detector


def get_simulation():
    """
    Returns a GISAXS simulation with beam defined
    """
    simulation = ba.GISASSimulation()
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setDetector(get_rectangular_detector())
    return simulation


def plot_as_colormap(hist, Title, xLabel, yLabel):
    """
    Simple plot of intensity data as color map
    """

    im = plt.imshow(
        hist.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, hist.getMaximum()),
        extent=[hist.getXmin(), hist.getXmax(),
                hist.getYmin(), hist.getYmax()],
        aspect='auto')
    cb = plt.colorbar(im, pad=0.025)
    plt.xlabel(xLabel, fontsize=16)
    plt.ylabel(yLabel, fontsize=16)
    plt.title(Title)


def simulate():
    """
    Run simulation and returns it.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation


def plot(simulation):
    """
    Plots simulation results for different detectors.
    """
    fig = plt.figure(figsize=(12.80, 10.24))

    plt.subplot(2, 2, 1)
    # default units for rectangular detector are millimeters
    result = simulation.getIntensityData()
    plot_as_colormap(result, "In default units",
                     r'$X_{mm}$', r'$Y_{mm}$')

    plt.subplot(2, 2, 2)
    result = simulation.getIntensityData(ba.IDetector2D.NBINS)
    plot_as_colormap(result, "In number of bins",
                     r'$X_{nbins}$', r'$Y_{nbins}$')

    plt.subplot(2, 2, 3)
    result = simulation.getIntensityData(ba.IDetector2D.DEGREES)
    plot_as_colormap(result, "In degs",
                     r'$\phi_f ^{\circ}$', r'$\alpha_f ^{\circ}$')

    plt.subplot(2, 2, 4)
    result = simulation.getIntensityData(ba.IDetector2D.QYQZ)
    plot_as_colormap(result, "Q-space",
                     r'$Q_{y} [1/nm]$', r'$Q_{z} [1/nm]$')

    plt.subplots_adjust(left=0.07, right=0.97, top=0.9, bottom=0.1, hspace=0.25)
    plt.show()


def save(simulation, filename):
    print("Not yet saving anything")


if __name__ == '__main__':
    ba.simulateThenPlotOrSave(simulate, plot, save)

"""
Simulation with rectangular detector. Pilatus3-1M detector is used as an example.
Results will be compared against simulation  with spherical detector.
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


def get_spherical_detector():
    """
    Returns spherical detector roughly representing our PILATUS detector
    """
    n_phi = pilatus_npx
    n_alpha = pilatus_npy
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    phi_min = numpy.arctan(-width/2./detector_distance)
    phi_max = numpy.arctan(width/2./detector_distance)
    alpha_min = 0.0
    alpha_max = numpy.arctan(height/detector_distance)
    return SphericalDetector(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max)


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
    return simulation


def plot_results(result_sph, result_rect):
    """
    Plots results of two simulations and their relative difference on one canvas
    """
    fig = plt.figure(figsize=(13.6, 5.12))

    # showing  result of spherical detector simulation
    plt.subplot(1, 3, 1)
    im = plt.imshow(result_sph.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, result_sph.getMaximum()),
                    extent=[result_sph.getXmin()/deg, result_sph.getXmax()/deg, result_sph.getYmin()/deg, result_sph.getYmax()/deg],
                    aspect='auto')
    cb = plt.colorbar(im, pad = 0.025)
    plt.xlabel(r'$\phi_f ^{\circ}$', fontsize=16)
    plt.ylabel(r'$\alpha_f ^{\circ}$', fontsize=16)
    plt.text(0.0, 5.3, "Spherical detector", horizontalalignment='center', verticalalignment='center', fontsize=11)

    # showing  result of rectangular detector simulation
    plt.subplot(1, 3, 2)
    im = plt.imshow(result_rect.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, result_rect.getMaximum()),
                    extent=[result_rect.getXmin(), result_rect.getXmax(), result_rect.getYmin(), result_rect.getYmax()],
                    aspect='auto')
    cb = plt.colorbar(im, pad = 0.025)
    plt.xlabel('X, mm', fontsize=12)
    plt.ylabel('Y, mm', fontsize=12)
    plt.text(90.0, 186.0, "Rectangular detector", horizontalalignment='center', verticalalignment='center', fontsize=11)

    # showing relative difference between two plots (sph[i]-rect[i])/rect[i] for every detector pixel
    diff = IHistogram.createRelativeDifferenceHistogram(result_sph, result_rect)
    plt.subplot(1, 3, 3)
    im = plt.imshow(diff.getArray(),
                    norm=matplotlib.colors.LogNorm(1e-06, 1.0),
                    extent=[diff.getXmin(), diff.getXmax(), diff.getYmin(), diff.getYmax()],
                    aspect='auto')
    cb = plt.colorbar(im, pad = 0.025)
    plt.xlabel('X, mm', fontsize=12)
    plt.ylabel('Y, mm', fontsize=12)
    plt.text(90.0, 186.0, "Relative difference", horizontalalignment='center', verticalalignment='center', fontsize=11)

    plt.subplots_adjust(left=0.05, right=0.95, top=0.88, bottom=0.12)
    plt.savefig('a.png')
    plt.show()


def run_simulation():
    """
    Run two simulations for two different detectors and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    # runs simulation for spherical detector
    simulation.setDetector(get_spherical_detector())
    simulation.runSimulation()
    result_sph = simulation.getIntensityData()

    # runs simulation for rectangular detector
    simulation.setDetector(get_rectangular_detector())
    simulation.runSimulation()
    result_rect = simulation.getIntensityData()

    plot_results(result_sph, result_rect)

if __name__ == '__main__':
    run_simulation()



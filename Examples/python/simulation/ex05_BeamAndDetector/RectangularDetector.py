"""
Simulation with rectangular detector. Pilatus3-1M detector is used as an example.
Results will be compared against simulation with spherical detector.
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm


detector_distance = 500.0  # in mm
pilatus_pixel_size = 0.172  # in mm
pilatus_npx, pilatus_npy = 981, 1043  # number of pixels


def get_sample():
    """
    Returns a sample with cylindrical particles on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    edge = 40*nm
    ff = ba.FormFactorBox(edge, edge, edge)
    cylinder = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_spherical_detector():
    """
    Returns a spherical detector roughly approximating our PILATUS detector
    """
    n_phi = pilatus_npx
    n_alpha = pilatus_npy
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    phi_min = numpy.arctan(-width/2./detector_distance)
    phi_max = numpy.arctan(width/2./detector_distance)
    alpha_min = 0.0
    alpha_max = numpy.arctan(height/detector_distance)
    return ba.SphericalDetector(
        n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max)


def get_rectangular_detector():
    """
    Returns a rectangular detector representing our PILATUS detector
    """
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = ba.RectangularDetector(pilatus_npx, width, pilatus_npy, height)
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0)
    return detector


def get_simulation():
    """
    Return a GISAXS simulation with defined beam
    """
    simulation = ba.GISASSimulation()
    simulation.setBeamParameters(10*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def plot(result):
    """
    Plots results of two simulations and their relative difference on one canvas
    """
    import matplotlib
    from matplotlib import pyplot as plt
    from matplotlib import rc
    rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
    rc('text', usetex=True)
    fig = plt.figure(figsize=(13.6, 5.12))

    result_sph  = result['spherical']
    result_rect = result['rectangular']
    result_diff = result['difference']

    # showing  result of spherical detector simulation
    plt.subplot(1, 3, 1)
    im = plt.imshow(
        result_sph.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result_sph.getMaximum()),
        extent=[result_sph.getXmin()/deg, result_sph.getXmax()/deg,
                result_sph.getYmin()/deg, result_sph.getYmax()/deg],
        aspect='auto')
    cb = plt.colorbar(im, pad=0.025)
    plt.xlabel(r'$\phi_f ^{\circ}$', fontsize=16)
    plt.ylabel(r'$\alpha_f ^{\circ}$', fontsize=16)
    plt.title("Spherical detector")

    # showing  result of rectangular detector simulation
    plt.subplot(1, 3, 2)
    im = plt.imshow(
        result_rect.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result_rect.getMaximum()),
        extent=[result_rect.getXmin(), result_rect.getXmax(),
                result_rect.getYmin(), result_rect.getYmax()],
        aspect='auto')
    cb = plt.colorbar(im, pad = 0.025)
    plt.xlabel('X, mm', fontsize=12)
    plt.ylabel('Y, mm', fontsize=12)
    plt.title("Rectangular detector")

    # show relative difference between two plots (sph[i]-rect[i])/rect[i]
    # for every detector pixel
    plt.subplot(1, 3, 3)
    im = plt.imshow(
        result_diff.getArray(),
        norm=matplotlib.colors.LogNorm(1e-06, 1.0),
        extent=[result_diff.getXmin(), result_diff.getXmax(),
                result_diff.getYmin(), result_diff.getYmax()],
        aspect='auto')
    cb = plt.colorbar(im, pad=0.025)
    plt.xlabel('X, mm', fontsize=12)
    plt.ylabel('Y, mm', fontsize=12)
    plt.title("Relative difference")

    plt.subplots_adjust(left=0.05, right=0.95, top=0.88, bottom=0.12)
    plt.show()


def run_simulation():
    """
    Run two simulations for two different detectors and plot results
    """
    result = {}

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    # runs simulation for spherical detector
    simulation.setDetector(get_spherical_detector())
    simulation.runSimulation()
    result['spherical'] = simulation.getIntensityData()

    # runs simulation for rectangular detector
    simulation.setDetector(get_rectangular_detector())
    simulation.runSimulation()
    result['rectangular'] = simulation.getIntensityData()

    result['difference'] = result['spherical'].relativeDifferenceHistogram(
        result['rectangular'])

    return result


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_intensity_data(result, plot)

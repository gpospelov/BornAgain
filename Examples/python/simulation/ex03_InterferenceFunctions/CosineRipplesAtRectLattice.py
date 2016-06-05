"""
Cosine ripple on a 2D lattice
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import degree, angstrom, nanometer

phi_min, phi_max = -1.5, 1.5
alpha_min, alpha_max = 0.0, 2.5


def get_sample():
    """
    Returns a sample with cosine ripples on a substrate.
    The structure is modelled as a 2D Lattice.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ripple1_ff = ba.FormFactorRipple1(100*nanometer, 20*nanometer, 4*nanometer)
    ripple = ba.Particle(m_particle, ripple1_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(ripple, 1.0)

    interference = ba.InterferenceFunction2DLattice(
        200.0*nanometer, 50.0*nanometer, 90.0*degree, 0.0*degree)
    pdf = ba.FTDecayFunction2DCauchy(
        1000.*nanometer/2./numpy.pi, 100.*nanometer/2./numpy.pi)
    interference.setDecayFunction(pdf)
    particle_layout.addInterferenceFunction(interference)

    # assemble the sample
    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation():
    """
    characterizing the input beam and output detector
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree,
                                     100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.6*angstrom, 0.3*degree, 0.0*degree)
    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData()

    # showing the result
    im = plt.imshow(
        result.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
        extent=[result.getXmin()/degree, result.getXmax()/degree,
                result.getYmin()/degree, result.getYmax()/degree],
        aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    run_simulation()

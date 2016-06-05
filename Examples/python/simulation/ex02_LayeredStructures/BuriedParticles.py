"""
Spherical particles embedded in the middle of the layer on top of substrate.
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import degree, angstrom, nanometer

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Returns a sample with spherical particles in an layer between air and substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_interm_layer = ba.HomogeneousMaterial("IntermLayer", 3.45e-6, 5.24e-9)
    m_substrate = ba.HomogeneousMaterial("Substrate", 7.43e-6, 1.72e-7)
    m_particle = ba.HomogeneousMaterial("Particle", 0.0, 0.0)

    # collection of particles
    ff_sphere = ba.FormFactorFullSphere(10.2*nanometer)
    sphere = ba.Particle(m_particle, ff_sphere)
    sphere.setPosition(0.0, 0.0, -25.2)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(sphere, 1.0)

    # assembling the sample
    air_layer = ba.Layer(m_ambience)
    intermediate_layer = ba.Layer(m_interm_layer, 30.*nanometer)
    intermediate_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(intermediate_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree,
                                     200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.5*angstrom, 0.15*degree, 0.0*degree)
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

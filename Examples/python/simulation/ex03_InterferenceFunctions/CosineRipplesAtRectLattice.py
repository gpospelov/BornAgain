"""
Cosine ripple on a 2D lattice
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm

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
    ripple1_ff = ba.FormFactorRipple1(100*nm, 20*nm, 4*nm)
    ripple = ba.Particle(m_particle, ripple1_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(ripple, 1.0)

    interference = ba.InterferenceFunction2DLattice(
        200.0*nm, 50.0*nm, 90.0*deg, 0.0*deg)
    pdf = ba.FTDecayFunction2DCauchy(
        1000.*nm/2./numpy.pi, 100.*nm/2./numpy.pi)
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
    simulation.setDetectorParameters(100, phi_min*deg, phi_max*deg,
                                     100, alpha_min*deg, alpha_max*deg)
    simulation.setBeamParameters(1.6*angstrom, 0.3*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.getIntensityData()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_intensity_data(result)

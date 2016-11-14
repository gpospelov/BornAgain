"""
Core shell nanoparticles
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Returns a sample with box-shaped core-shell particles on a substrate.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = ba.HomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = ba.HomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    parallelepiped1_ff = ba.FormFactorBox(16*nm, 16*nm, 8*nm)
    parallelepiped2_ff = ba.FormFactorBox(12*nm, 12*nm, 7*nm)
    shell_particle = ba.Particle(m_shell, parallelepiped1_ff)
    core_particle = ba.Particle(m_core, parallelepiped2_ff)
    core_position = ba.kvector_t(0.0, 0.0, 0.0)

    particle = ba.ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(particle)
    interference = ba.InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)

    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*deg, phi_max*deg,
                                     200, alpha_min*deg, alpha_max*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
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

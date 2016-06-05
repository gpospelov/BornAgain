"""
Core shell nanoparticles
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
    Returns a sample with box-shaped core-shell particles on a substrate.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = ba.HomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = ba.HomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    parallelepiped1_ff = ba.FormFactorBox(16*nanometer, 16*nanometer, 8*nanometer)
    parallelepiped2_ff = ba.FormFactorBox(12*nanometer, 12*nanometer, 7*nanometer)
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
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree,
                                     200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
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

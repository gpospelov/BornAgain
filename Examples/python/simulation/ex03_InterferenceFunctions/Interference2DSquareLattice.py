"""
Cylinders on a 2D square lattice
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Returns a sample with cylinders on a substrate, forming a 2D square lattice.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    interference = ba.InterferenceFunction2DLattice.createSquare(25.0*nm)
    pdf = ba.FTDecayFunction2DCauchy(300.0*nm/2.0/numpy.pi,
                                     100.0*nm/2.0/numpy.pi)
    interference.setDecayFunction(pdf)

    cylinder_ff = ba.FormFactorCylinder(3.*nm, 3.*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder)
    particle_layout.addInterferenceFunction(interference)

    # assembling the sample
    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
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

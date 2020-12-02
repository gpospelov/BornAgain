"""
Simulation demo: magnetic spheres in substrate
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

# Magnetization of the particle's material (A/m)
magnetization_particle = ba.kvector_t(0.0, 0.0, 1e7)


def get_sample():
    """
    Returns a sample with magnetic spheres in the substrate.
    """

    # Define materials
    magnetic_field = kvector_t(0, 0, 10000000)
    material_Particle = ba.HomogeneousMaterial("Particle", 2e-05, 4e-07,
                                               magnetic_field)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 7e-06, 1.8e-07)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff = ba.FormFactorFullSphere(5.0*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)
    particle_position = kvector_t(0.0*nm, 0.0*nm, -10.0*nm)
    particle.setPosition(particle_position)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1.0)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_2 = ba.Layer(material_Substrate)
    layer_2.addLayout(layout)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -3.0*deg, 3.0*deg, 200, 0.0*deg,
                                     6.0*deg)
    simulation.setBeamParameters(1.*angstrom, 0.5*deg, 0.0*deg)
    simulation.setBeamIntensity(1e12)

    analyzer_dir = ba.kvector_t(0.0, 0.0, -1.0)
    beampol = ba.kvector_t(0.0, 0.0, 1.0)
    simulation.setBeamPolarization(beampol)
    simulation.setAnalyzerProperties(analyzer_dir, 1.0, 0.5)

    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')

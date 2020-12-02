"""
Mixture of cylinders and prisms without interference
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """

    # Define Materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)
    ff_2 = ba.FormFactorPrism3(10.0*nm, 5.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_Particle, ff_1)
    particle_2 = ba.Particle(material_Particle, ff_2)

    # Define interference functions
    iff = ba.InterferenceFunctionNone()

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_1, 0.5)
    layout.addParticle(particle_2, 0.5)
    layout.setInterferenceFunction(iff)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg, 100, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')

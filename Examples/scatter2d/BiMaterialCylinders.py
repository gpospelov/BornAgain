"""
Cylindrical particle made from two materials.
Particle crosses air/substrate interface.
"""
import bornagain as ba
from bornagain import deg, nm, kvector_t


def get_sample():
    """
    Returns a multi layer with substrate/air layers.
    Vacuum layer contains cylindrical particles made of two materials.
    Particle shifted down to cross interface.
    """

    # Define materials
    material_Ag = ba.HomogeneousMaterial("Ag", 1.245e-05, 5.419e-07)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 3.212e-06,
                                                3.244e-08)
    material_Teflon = ba.HomogeneousMaterial("Teflon", 2.9e-06, 6.019e-09)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff_1 = ba.FormFactorCylinder(10.0*nm, 4.0*nm)
    ff_2 = ba.FormFactorCylinder(10.0*nm, 10.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_Ag, ff_1)
    particle_1_position = kvector_t(0.0*nm, 0.0*nm, 10.0*nm)
    particle_1.setPosition(particle_1_position)
    particle_2 = ba.Particle(material_Teflon, ff_2)

    # Define composition of particles at specific positions
    particle_3 = ba.ParticleComposition()
    particle_3.addParticle(particle_1)
    particle_3.addParticle(particle_2)
    particle_3_position = kvector_t(0.0*nm, 0.0*nm, -10.0*nm)
    particle_3.setPosition(particle_3_position)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_3, 1.0)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(1)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation(sample):
    beam = ba.Beam(100000000.0, 0.1*nm, ba.Direction(0.2*deg, 0*deg))
    detector = ba.SphericalDetector(100, 2*deg, 0*deg, 1*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)

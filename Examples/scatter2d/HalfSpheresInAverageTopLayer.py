"""
Square lattice of half spheres on substrate with usage of average material
and slicing
"""
import bornagain as ba
from bornagain import deg, nm


def get_sample():
    """
    Returns a sample with cylinders on a substrate.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 3e-05, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff = ba.FormFactorTruncatedSphere(5.0*nm, 5.0*nm, 0.0*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)

    # Define 2D lattices
    lattice = ba.BasicLattice2D(10.0*nm, 10.0*nm, 90.0*deg, 0.0*deg)

    # Define interference functions
    iff = ba.InterferenceFunction2DLattice(lattice)
    iff_pdf = ba.FTDecayFunction2DCauchy(100.0*nm, 100.0*nm, 0.0*deg)
    iff.setDecayFunction(iff_pdf)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1.0)
    layout.setInterferenceFunction(iff)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.setNumberOfSlices(10)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation(sample):
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0*deg))
    detector = ba.SphericalDetector(100, -2*deg, 2*deg, 100, 0*deg, 2*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    simulation.getOptions().setUseAvgMaterials(True)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)

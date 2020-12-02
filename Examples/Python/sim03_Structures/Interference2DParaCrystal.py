"""
2D paracrystal
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with cylinders on a substrate, forming a 2D paracrystal
    """

    # Define Materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff = ba.FormFactorCylinder(4.0*nm, 5.0*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)

    # Define 2D lattices
    lattice = ba.BasicLattice2D(10.0*nm, 10.0*nm, 90.0*deg, 0.0*deg)

    # Define interference functions
    iff = ba.InterferenceFunction2DParaCrystal(lattice, 0.0*nm, 20000.0*nm,
                                               20000.0*nm)
    iff.setIntegrationOverXi(True)
    iff_pdf_1 = ba.FTDistribution2DCauchy(1.0*nm, 1.0*nm, 0.0*deg)
    iff_pdf_2 = ba.FTDistribution2DCauchy(1.0*nm, 1.0*nm, 0.0*deg)
    iff.setProbabilityDistributions(iff_pdf_1, iff_pdf_2)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1.0)
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
    # coarse grid because this simulation takes rather long
    simulation.setDetectorParameters(200, -2.0*deg, 2.0*deg, 200, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    if not "__no_terminal__" in globals():
        simulation.setTerminalProgressMonitor()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')

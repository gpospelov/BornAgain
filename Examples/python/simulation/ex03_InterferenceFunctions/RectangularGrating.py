"""
Simulation of grating using very long boxes and 1D lattice. Monte-carlo integration is used to get rid
from large particle form factor oscillations.
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample(lattice_rotation_angle=45.0*deg):
    """
    Build and return the sample representing 1D grating made out from a very long boxes
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    box_length, box_width, box_height = 10*nm, 10000*nm, 10.0*nm
    lattice_length = 30.0*nanometer

    # collection of particles
    interference = InterferenceFunction1DLattice(lattice_length, lattice_rotation_angle)
    pdf = FTDistribution1DCauchy(1000.0)
    interference.setProbabilityDistribution(pdf)

    box_ff = FormFactorBox(box_length, box_width, box_height)
    box = Particle(m_particle, box_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(box, 1.0, kvector_t(0.0, 0.0, 0.0), RotationZ(lattice_rotation_angle))
    particle_layout.addInterferenceFunction(interference)

    # assembling the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(monte_carlo_integration=True):
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    if monte_carlo_integration:
        sim_pars = SimulationParameters()
        sim_pars.m_mc_integration = True
        sim_pars.m_mc_points = 100
        simulation.setSimulationParameters(sim_pars)

    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample(lattice_rotation_angle=45.0*degree)
    simulation = get_simulation(monte_carlo_integration=True)
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData()

    # showing the result
    im = plt.imshow(result.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
                    extent=[result.getXmin()/deg, result.getXmax()/deg, result.getYmin()/deg, result.getYmax()/deg],
                    aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    run_simulation()

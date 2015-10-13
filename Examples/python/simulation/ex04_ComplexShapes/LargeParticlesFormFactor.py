"""
Large cylinders in DWBA.

Examples demonstrates, that for large particles (~1000nm) the formfactor oscillates rapidly within
one detector bin and analytical calculations (performed for the bin center) give completely wrong intensity pattern.
In this case Monte-Carlo integration over detector bin should be used.
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0
default_cylinder_radius = 10*nanometer
default_cylinder_height = 20*nanometer


def get_sample(cylinder_radius, cylinder_height):
    """
    Build and return the sample to calculate cylinder formfactor in Distorted Wave Born Approximation
    for given cylinder_radius and cylinder_height
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = Particle(m_particle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(integration_flag):
    """
    Create and return GISAXS simulation with beam and detector defined.
    If integration_flag=True, the simulation will perform an integration over detector bin size
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    if integration_flag:
        sim_pars = SimulationParameters()
        sim_pars.m_mc_integration = True
        sim_pars.m_mc_points = 50
        simulation.setSimulationParameters(sim_pars)

    return simulation


def run_simulation():
    """
    Run simulation and plot results 4 times: for small and large cylinders, with and without integration
    """

    fig = plt.figure(figsize=(12.80, 10.24))

    # conditions to define cylinders scale factor and Monte-Carlo integration flag
    conditions = [
        {'title': "Small cylinders, analytical calculations", 'scale': 1,   'integration': False, 'max': 1e+08},
        {'title': "Small cylinders, Monte-Carlo integration", 'scale': 1,   'integration': True,  'max': 1e+08},
        {'title': "Large cylinders, analytical calculations", 'scale': 100, 'integration': False, 'max': 1e+12},
        {'title': "Large cylinders, Monte-Carlo integration", 'scale': 100, 'integration': True,  'max': 1e+12}
    ]

    # run simulation 4 times and plot results
    for i_plot in range(0, len(conditions)):
        scale = conditions[i_plot]['scale']
        integration_flag = conditions[i_plot]['integration']

        sample = get_sample(default_cylinder_radius*scale, default_cylinder_height*scale)
        simulation = get_simulation(integration_flag)
        simulation.setSample(sample)
        simulation.runSimulation()
        result = simulation.getIntensityData()

        # plotting results
        plt.subplot(2, 2, i_plot+1)
        plt.subplots_adjust(wspace=0.3, hspace=0.3)
        im = plt.imshow(result.getArray(),
                        norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
                        extent=[result.getXmin()/deg, result.getXmax()/deg, result.getYmin()/deg, result.getYmax()/deg],
                        aspect='auto')
        cb = plt.colorbar(im)
        cb.set_label(r'Intensity (arb. u.)', size=16)
        plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
        plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
        plt.text(0.0, 2.1, conditions[i_plot]['title'], horizontalalignment='center', verticalalignment='center', fontsize=13)

    plt.show()


if __name__ == '__main__':
    run_simulation()

# Functional test: Monte-Carlo integration functional test for very large cylinders
import sys
import os
import numpy
import cmath
from utils import get_reference_data

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))


from libBornAgainCore import *

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0
default_cylinder_radius = 10*nanometer
default_cylinder_height = 20*nanometer
scale = 100


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


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined.
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(50, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    sim_pars = SimulationParameters()
    sim_pars.m_mc_integration = True
    sim_pars.m_mc_points = 50
    simulation.setSimulationParameters(sim_pars)
    return simulation



def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample(default_cylinder_radius*scale, default_cylinder_height*scale)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData()
    return result


def run_test():
    """
    run test and analyse test results
    """
    result = run_simulation()
    # IntensityDataIOFactory.writeIntensityData(result, 'montecarlo_integration.int')
    reference = get_reference_data('montecarlo_integration.int.gz')
    diff = IntensityDataFunctions.getRelativeDifference(result, reference)
    status = "OK"
    if diff > 2e-10 or numpy.isnan(diff):
        status = "FAILED"
    return "MonteCarloIntegration", "Test of Monte-Carlo integration", diff, status


if __name__ == '__main__':
    name, description, diff, status = run_test()
    print name, description, diff, status
    if "FAILED" in status:
        exit(1)


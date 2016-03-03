# Functional test: Cylinders in DWBA with beam divergence
from __future__ import print_function
import sys
import os
import numpy
from utils import get_reference_data

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *

phi_min, phi_max = -0.2, 1.8
alpha_min, alpha_max = 0.0, 2.2

def RunSimulation():
    """
    describe sample and run simulation
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    # assembling the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build simulation
    simulation = GISASSimulation()
    simulation.setDetectorParameters(40, phi_min*degree, phi_max*degree, 60, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    wavelength_distr = DistributionLogNormal(1.0*angstrom, 0.1)
    alpha_distr = DistributionGaussian(0.2*degree, 0.1*degree)
    #phi_distr = DistributionGaussian(0.0*degree, 0.1*degree)
    phi_distr = DistributionGate(-0.1*degree, 0.1*degree)
    simulation.addParameterDistribution("*/Beam/wavelength", wavelength_distr, 5)
    simulation.addParameterDistribution("*/Beam/alpha", alpha_distr, 4)
    simulation.addParameterDistribution("*/Beam/phi", phi_distr, 3)
    simulation.setSample(multi_layer)

    # run simulation and retrieve results
    simulation.runSimulation()
    return simulation.getIntensityData()


def runTest():
    """
    run test and analyse test results
    """
    result = RunSimulation()

    diff = IntensityDataFunctions.getRelativeDifference(result, get_reference_data("beamdivergence_reference.int.gz"))

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "beam_divergence", "Cylinder in DWBA with beam divergence", diff, status


if __name__ == '__main__':
    name, description, diff, status = runTest()
    print(name, description, diff, status)
    if("FAILED" in status):
        exit(1)




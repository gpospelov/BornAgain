#  Functional test: Custom formfactor example
from __future__ import print_function
import sys
import os
import numpy
import math
from utils import get_reference_data

from libBornAgainCore import *
from libBornAgainFit import * # TODO remove this once ICloneable is back in Core/

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


class CustomFormFactor(IFormFactorBorn):
    """
    A custom defined form factor
    The form factor is V sech(q L) with
    V volume of particle
    L length scale which defines mean radius
    """
    def __init__(self, V, L):
        IFormFactorBorn.__init__(self)
        # parameters describing the form factor
        self.V = V
        self.L = L

    def clone(self):
        """
        IMPORTANT NOTE:
        The clone method needs to call transferToCPP() on the cloned object
        to transfer the ownership of the clone to the cpp code
        """
        cloned_ff = CustomFormFactor(self.V, self.L)
        cloned_ff.transferToCPP()
        return cloned_ff

    def evaluate_for_q(self, q):
        return self.V*1.0/math.cosh(q.mag()*self.L)


def get_sample():
    """
    Build and return the sample to calculate custom form factor in Distorted Wave Born Approximation.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ff = CustomFormFactor(343.0*nanometer, 7.0*nanometer)
    particle = Particle(m_particle, ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(particle, 1.0)
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    # assemble multilayer
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    IMPORTANT NOTE:
    Multithreading should be deactivated by putting ThreadInfo.n_threads to -1
    """
    simulation = GISASSimulation()
    simulation.getOptions().setNumberOfThreads(-1)
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
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
    reference = get_reference_data('customformfactor_reference.int.gz')
    diff = IntensityDataFunctions.getRelativeDifference(result, reference)
    status = "OK"
    if diff > 2e-3 or numpy.isnan(diff):
        print( "difference: %g" % diff )
        status = "FAILED"
    return "CustomFormFactor", "Test of custom formfactor", diff, status


if __name__ == '__main__':
    name, description, diff, status = run_test()
    print(name, description, diff, status)
    if "FAILED" in status:
        exit(1)

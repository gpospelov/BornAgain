#!/usr/bin/python
 # -*- coding: utf-8 -*-


## ************************************************************************** ##
##
##  BornAgain: simulate and fit scattering at grazing incidence
##
##! @file      customformfactor.py
##! @brief     Test performance of customformfactor
##!
##! @homepage  http:##www.bornagainproject.org
##! @license   GNU General Public License v3 or higher (see COPYING)
##! @copyright Forschungszentrum Jülich GmbH 2016
##! @authors   Scientific Computing Group at MLZ Garching
##! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
##
## ************************************************************************** ##


from __future__ import print_function
import sys
import os
import numpy
import math
import timeit
import resource

from libBornAgainCore import *

nrepetitions = 50






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
    thread_info = ThreadInfo()
    thread_info.n_threads = -1
    simulation.setThreadInfo(thread_info)
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_test():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()

    start_time_real = timeit.default_timer()
    start_time_user = resource.getrusage(resource.RUSAGE_SELF)[0]
    
    for i in range(nrepetitions):
        simulation.setSample(sample)
        simulation.runSimulation()

    end_time_real = timeit.default_timer()
    end_time_user = resource.getrusage(resource.RUSAGE_SELF)[0]
        
    real_time = (end_time_real - start_time_real)
    user_time = (end_time_real - start_time_real)

    print("\ntime after %d repetitions:" % nrepetitions)
    print("real time: %.4f" % real_time)
    print("user time: %.4f\n" % user_time)



if __name__ == '__main__':
    run_test()

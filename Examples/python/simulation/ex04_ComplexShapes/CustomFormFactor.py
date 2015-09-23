"""
Custom form factor in DWBA.
"""
import numpy
import matplotlib
import pylab
import cmath
from bornagain import *

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0

def sinc(x):
    if abs(x) == 0.:
        return 1.
    else:
        return cmath.sin(x)/x

class CustomFormFactor(IFormFactorBorn):
    """
    A custom defined form factor
    The particle is a polyhedron, whose planar cross section is a "plus" shape
    with a side length L.
    H is the height of particle
    """
    def __init__(self, L, H): 
        IFormFactorBorn.__init__(self)
        # parameters describing the form factor
        self.L = L
        self.H = H

  
    def clone(self):
        """
        IMPORTANT NOTE:
        The clone method needs to call transferToCPP() on the cloned object
        to transfer the ownership of the clone to the cpp code
        """
        cloned_ff = CustomFormFactor(self.L, self.H) 
        cloned_ff.transferToCPP()
        return cloned_ff

    def evaluate_for_q(self, q):
        qzhH = 0.5*q.z()*self.H
        qxhL = 0.5*q.x()*self.L
        qyhL = 0.5*q.y()*self.L
        return 0.5*self.H*self.L**2*cmath.exp(complex(0.,1.)*qzhH)*sinc(qzhH)*(sinc(0.5*qyhL)*(sinc(qxhL) - 0.5*sinc(0.5*qxhL)) + sinc(0.5*qxhL)*sinc(qyhL))



def get_sample():
    """
    Build and return the sample to calculate custom form factor in Distorted Wave Born Approximation.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ff = CustomFormFactor(20.0*nanometer, 15.0*nanometer)
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


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray()

    # showing the result
    im = pylab.imshow(result, norm=matplotlib.colors.LogNorm(),
                 extent=[phi_min, phi_max, alpha_min, alpha_max], aspect='auto')
    cb = pylab.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', fontsize=16)
    pylab.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    pylab.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    run_simulation()



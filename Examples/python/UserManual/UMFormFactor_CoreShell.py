import numpy
import matplotlib
import pylab
from libBornAgainCore import *


def get_sample():
    """
    Build and return the sample to calculate core-shell formfactor in Born Approximation.
    """
    # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = HomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = HomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    outer_ff = FormFactorBox(16*nanometer,16*nanometer, 8*nanometer) 
    inner_ff = FormFactorPyramid(12*nanometer, 7*nanometer, 60*degree)
    shell_particle = Particle(m_shell, outer_ff)
    core_particle = Particle(m_core, inner_ff)
    core_position = kvector_t(1.5, 0.0, 0.0)

    particle = ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(particle)

    # interferences
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    # assembling the sample
    air_layer = Layer(m_air)
    air_layer.setLayout(particle_layout)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(nx, phifmin*degree, phifmax*degree, ny, alphafmin*degree, alphafmax*degree)
    simulation.setBeamParameters(wlgth, alphai, phii)
    return simulation

def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray() + 1  # for log scale
    pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(), extent=[phifmin, phifmax, alphafmin, alphafmax])
    pylab.show()
 

    
if __name__ == '__main__':
    wlgth = 1.0*angstrom
    nx = 100
    ny = 100
    alphafmax = 2. # in degree
    alphafmin = 0. #  in degree
    phifmax= 2.     #  degree
    phifmin= 0.   #  degree
    alphai=0.2*degree
    phii=0.*degree
    run_simulation()



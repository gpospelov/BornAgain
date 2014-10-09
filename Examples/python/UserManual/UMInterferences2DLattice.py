import numpy
import matplotlib
import pylab
from libBornAgainCore import *

M_PI = numpy.pi


def get_sample():
    """
    Build and return the sample representing half spheres with 2D lattice interference function 
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # lattice parameters
    lattice_params = Lattice2DIFParameters()
    lattice_params.m_length_1 = 20.0*nanometer
    lattice_params.m_length_2 = 20.0*nanometer
    lattice_params.m_angle = 90.0*degree
    lattice_params.m_xi = 0.0*degree

    #collection of particles
    sphere_ff = FormFactorTruncatedSphere(5*nanometer, 5*nanometer)
    sphere = Particle(m_particle, sphere_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(sphere, 0.0, 1.0)

    # interferences
    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DGauss(200.0*nanometer/2.0/M_PI, 75.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # interference approx chosen between: DA (default), LMA and SSCA
    particle_layout.setApproximation(ILayout.LMA)

    # assembling the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)

    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
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
    wlgth = 1.*angstrom
    nx = 100
    ny = 100
    alphafmax = 2. # in degree
    alphafmin = 0. #  in degree
    phifmax= 2.     #  degree
    phifmin= 0.   #  degree
    alphai=0.2*degree
    phii=0.*degree
    
    run_simulation()

"""
Spheres at hex lattice
"""
import numpy
import matplotlib
import pylab
from bornagain import *

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 1.0


def get_sample():
    """
    Build and return the sample representing spheres at hex 2D lattice
    """
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    radius = 10.0*nanometer
    sphere_ff = FormFactorFullSphere(radius)
    sphere = Particle(m_particle, sphere_ff)
    particle_layout = ParticleLayout()


    # pos0 = kvector_t(0.0, 0.0, 0.0)
    # pos1 = kvector_t(radius, radius, radius + numpy.sqrt(3)*radius)
    # # pos1 = kvector_t(0.0, 0.0, radius)
    # particle_layout.addParticleInfo(PositionParticleInfo(sphere, pos0, 1.0))
    # info1 = PositionParticleInfo(sphere, pos1, 1.0)
    # # # info1.setDepth(numpy.sqrt(3)*radius)
    # particle_layout.addParticleInfo(info1)


    pos0 = kvector_t(0.0, 0.0, 0.0)
    # pos1 = kvector_t(0.0, 0.0, radius)
    pos1 = kvector_t(radius, radius, numpy.sqrt(3.0)*radius)
    basis = LatticeBasis()
    basis.addParticle(sphere, [pos0, pos1])
    particle_layout.addParticle(basis)


    interference = InterferenceFunction2DLattice.createHexagonal(radius*2.0)
    pdf = FTDistribution2DCauchy(10*nanometer, 10*nanometer)
    interference.setProbabilityDistribution(pdf)

    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(m_air)
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
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
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
    result = simulation.getIntensityData().getArray() + 1  # for log scale

    # showing the result
    im = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                 extent=[phi_min, phi_max, alpha_min, alpha_max], aspect='auto')
    cb = pylab.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', fontsize=16)
    pylab.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    pylab.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    run_simulation()



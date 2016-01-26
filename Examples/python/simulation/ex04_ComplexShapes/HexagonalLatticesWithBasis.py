"""
Spheres on two hexagonal close packed layers
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 1.0


def get_sample():
    """
    Build and return the sample representing spheres on two hexagonal close packed layers
    """
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    radius = 10.0*nanometer
    sphere_ff = FormFactorFullSphere(radius)
    sphere = Particle(m_particle, sphere_ff)
    particle_layout = ParticleLayout()

    pos0 = kvector_t(0.0, 0.0, 0.0)
    pos1 = kvector_t(radius, radius, numpy.sqrt(3.0)*radius)
    basis = ParticleComposition()
    basis.addParticles(sphere, [pos0, pos1])
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
    simulation = GISASSimulation()
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



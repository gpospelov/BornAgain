"""
2D lattice with disorder, centered square lattice
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample representing 2D centered square lattice
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    interference = InterferenceFunction2DLattice.createSquare(25.0*nanometer)
    pdf = FTDecayFunction2DCauchy(300.0*nanometer/2.0/numpy.pi, 100.0*nanometer/2.0/numpy.pi)
    interference.setDecayFunction(pdf)

    particle_layout = ParticleLayout()
    position1 = kvector_t(0.0, 0.0, 0.0)
    position2 = kvector_t(12.5*nanometer, 12.5*nanometer, 0.0)
    cylinder_ff = FormFactorCylinder(3.*nanometer, 3.*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    basis = ParticleComposition()
    basis.addParticles(cylinder, [position1, position2])
    particle_layout.addParticle(basis)
    particle_layout.addInterferenceFunction(interference)

    # assembling the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAS simulation with beam and detector defined
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

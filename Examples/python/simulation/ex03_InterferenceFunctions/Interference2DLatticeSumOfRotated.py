# 2D lattice with different disorder (IsGISAXS example #6), sum of rotated lattices
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = 0.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample(xi_value):
    """
    Build and return the sample representing 2D lattice with different disorder
    rotated lattice
    """
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    air_layer = Layer(m_ambience)
    substrate_layer = Layer(m_substrate)

    p_interference_function = InterferenceFunction2DLattice.createSquare(25.0*nanometer, xi_value)
    pdf = FTDecayFunction2DCauchy(300.0*nanometer/2.0/numpy.pi, 100.0*nanometer/2.0/numpy.pi)
    p_interference_function.setDecayFunction(pdf)

    particle_layout = ParticleLayout()
    ff_cyl = FormFactorCylinder(3.0*nanometer, 3.0*nanometer)
    position = kvector_t(0.0, 0.0, 0.0)
    cylinder = Particle(m_particle, ff_cyl.clone())
    cylinder.setPosition(position)
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.addInterferenceFunction(p_interference_function)

    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_simulation():
    """
    Run several simulations, sum up intensities from different rotated lattices and plot results
    """

    simulation = get_simulation()

    OutputData_total = simulation.getIntensityData()
    nbins = 3
    xi_min = 0.0*degree
    xi_max = 240.0*degree
    total_weight = 0.0
    xi_distr = DistributionGate(xi_min, xi_max)
    xi_samples = xi_distr.generateValueList(nbins, 0.0)
    for i in range(len(xi_samples)):
        xi_value = xi_samples[i]
        probability = xi_distr.probabilityDensity(xi_value)
        total_weight += probability
        p_sample = get_sample(xi_value)
        simulation.setSample(p_sample)
        simulation.runSimulation()

        single_output = simulation.getIntensityData()
        single_output.scale(probability)
        OutputData_total += single_output
    OutputData_total.scale(1.0/total_weight)

    result = OutputData_total

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


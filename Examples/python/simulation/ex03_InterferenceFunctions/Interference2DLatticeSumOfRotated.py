# 2D lattice with different disorder (IsGISAXS example #6), sum of rotated lattices
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_min, phi_max = 0.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample(xi_value):
    """
    Returns a sample with cylinders on a substrate,
    forming a 2D lattice with different disorder rotated lattice
    """
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    air_layer = ba.Layer(m_ambience)
    substrate_layer = ba.Layer(m_substrate)

    p_interference_function = ba.InterferenceFunction2DLattice.createSquare(
        25.0*nm, xi_value)
    pdf = ba.FTDecayFunction2DCauchy(300.0*nm/2.0/numpy.pi,
                                     100.0*nm/2.0/numpy.pi)
    p_interference_function.setDecayFunction(pdf)

    particle_layout = ba.ParticleLayout()
    ff_cyl = ba.FormFactorCylinder(3.0*nm, 3.0*nm)
    position = ba.kvector_t(0.0, 0.0, 0.0)
    cylinder = ba.Particle(m_particle, ff_cyl.clone())
    cylinder.setPosition(position)
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.addInterferenceFunction(p_interference_function)

    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, phi_min*deg, phi_max*deg,
                                     100, alpha_min*deg, alpha_max*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs several simulations,
    sums intensities from different rotated lattices,
    and plots results
    """

    simulation = get_simulation()

    OutputData_total = simulation.getIntensityData()
    nbins = 3
    xi_min = 0.0*deg
    xi_max = 240.0*deg
    total_weight = 0.0
    xi_distr = ba.DistributionGate(xi_min, xi_max)
    xi_samples = xi_distr.equidistantPoints(nbins, 0.0)
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

    return OutputData_total


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_intensity_data(result)

"""
Cylinders of two different sizes in Local Monodisperse Approximation
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import degree, angstrom, nanometer

phi_min, phi_max = 0.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Returns a sample with cylinders of two different sizes on a substrate.
    The cylinder positions are modelled in Local Monodisperse Approximation.
    """
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # cylindrical particle 1
    radius1 = 5*nanometer
    height1 = radius1
    cylinder_ff1 = ba.FormFactorCylinder(radius1, height1)
    cylinder1 = ba.Particle(m_particle, cylinder_ff1)

    # cylindrical particle 2
    radius2 = 8*nanometer
    height2 = radius2
    cylinder_ff2 = ba.FormFactorCylinder(radius2, height2)
    cylinder2 = ba.Particle(m_particle, cylinder_ff2)

    # interference function1
    interference1 = ba.InterferenceFunctionRadialParaCrystal(
        16.8*nanometer, 1e3*nanometer)
    pdf = ba.FTDistribution1DGauss(3 * nanometer)
    interference1.setProbabilityDistribution(pdf)

    # interference function2
    interference2 = ba.InterferenceFunctionRadialParaCrystal(
        22.8*nanometer, 1e3*nanometer)
    interference2.setProbabilityDistribution(pdf)

     # assembling the sample
    particle_layout1 = ba.ParticleLayout()
    particle_layout1.addParticle(cylinder1, 0.8)
    particle_layout1.addInterferenceFunction(interference1)

    particle_layout2 = ba.ParticleLayout()
    particle_layout2.addParticle(cylinder2, 0.2)
    particle_layout2.addInterferenceFunction(interference2)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout1)
    air_layer.addLayout(particle_layout2)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree,
                                     200, alpha_min*degree, alpha_max*degree)
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
    im = plt.imshow(
        result.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
        extent=[result.getXmin()/degree, result.getXmax()/degree,
                result.getYmin()/degree, result.getYmax()/degree],
        aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    run_simulation()

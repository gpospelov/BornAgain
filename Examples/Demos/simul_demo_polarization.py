'''
Simulation demo: Cylinder and/or sphere on substrate
'''

import numpy
import matplotlib
import math
from bornagain import *

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    magnetic_field_layer = kvector_t(0.0, 6.0, 0.0)
    magnetic_field_particle = kvector_t(1.7, 1.7, 1.7)
    mAir = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mLayer = HomogeneousMagneticMaterial("Layer", 3e-6, 2e-8, magnetic_field_layer)
    mParticle = HomogeneousMagneticMaterial("Particle", 6e-4, 2e-8, magnetic_field_particle)

    # collection of particles
    cylinder_ff = FormFactorCylinder(2 * nanometer, 5 * nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
#    sphere_ff = FormFactorFullSphere(4 * nanometer)
#    sphere = Particle(mParticle, sphere_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder)
#    particle_layout.addParticle(sphere)
#    interference = InterferenceFunctionRadialParaCrystal(20 * nanometer, 2 * nanometer)
#    pdf = FTDistribution1DGauss(2 * nanometer)
#    interference.setProbabilityDistribution(pdf)
#    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAir)
    intermediate_layer = Layer(mLayer)
    intermediate_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(intermediate_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -4.0 * degree, 4.0 * degree, 100, 0.0 * degree, 8.0 * degree)
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data components

    intensity_pp = simulation.getPolarizedIntensityData(0, 0).getArray()
    intensity_pm = simulation.getPolarizedIntensityData(0, 1).getArray()
    intensity_mp = simulation.getPolarizedIntensityData(1, 0).getArray()
    intensity_mm = simulation.getPolarizedIntensityData(1, 1).getArray()

    return intensity_pp, intensity_pm, intensity_mp, intensity_mm


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    intensity_pp, intensity_pm, intensity_mp, intensity_mm = RunSimulation()
    plt.subplot(2, 2, 1)
    plt.title('Intensity ++')
    im = plt.imshow(intensity_pp+1,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    plt.colorbar(im)
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    plt.subplot(2, 2, 2)
    plt.title('Intensity +-')
    im = plt.imshow(intensity_pm+1,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    plt.colorbar(im)
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    plt.subplot(2, 2, 3)
    plt.title('Intensity -+')
    im = plt.imshow(intensity_mp+1,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    plt.colorbar(im)
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    plt.subplot(2, 2, 4)
    plt.title('Intensity --')
    im = plt.imshow(intensity_mm+1,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    plt.colorbar(im)
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    plt.show()

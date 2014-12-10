"""
All formfactors available in BornAgain in Born Approximation
"""
import numpy
import matplotlib
import pylab
from bornagain import *

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


formfactors = [
    FormFactorAnisoPyramid(20.0, 16.0, 13.0, 60.0*degree),
    FormFactorBox(20.0, 16.0, 13.0),
    FormFactorCone(10.0, 13.0, 60.0*degree),
    FormFactorCone6(10.0, 13.0, 60.0*degree),
    FormFactorCuboctahedron(20.0, 13.0, 0.7, 60.0*degree),
    FormFactorCylinder(8.0, 16.0),
    FormFactorEllipsoidalCylinder(8.0, 13.0, 16.0),
    FormFactorFullSphere(8.0),
    FormFactorFullSpheroid(10.0, 13.0),
    FormFactorHemiEllipsoid(10.0, 6.0, 8.0),
    FormFactorPrism3(10.0, 13.0),
    FormFactorPrism6(5.0, 11.0),
    FormFactorPyramid(18.0, 13.0, 60.0*degree),
    FormFactorRipple1(27.0, 20.0, 14.0),
    FormFactorRipple2(36.0, 25.0, 14.0, 3.0),
    FormFactorTetrahedron(15.0, 6.0, 60.0*degree),
    FormFactorTruncatedSphere(5.0, 7.0),
    FormFactorTruncatedSpheroid(7.5, 9.0, 1.2)
]


def get_sample(formfactor):
    """
    Build and return the sample to calculate cylinder formfactor in Born approximation.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    particle = Particle(m_particle, formfactor)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(particle, 0.0, 1.0)

    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_simulation():
    """
    Run simulation one by one for every formfactor from the list and plot results on single canvas
    """

    dpi = 72.
    xinch = 1024 / dpi
    yinch = 768 / dpi
    fig = pylab.figure(figsize=(xinch, yinch))

    nplot = 1
    for ff in formfactors:
        name = ff.__class__.__name__
        name = name.replace("FormFactor", "")
        print "Generating intensity map in BA for '{0}'".format(name)

        sample = get_sample(ff)
        simulation = get_simulation()
        simulation.setSample(sample)
        simulation.runSimulation()
        result = simulation.getIntensityData().getArray() + 1  # for log scale

        # showing the result
        pylab.subplot(4, 5, nplot)
        pylab.subplots_adjust(wspace=0.3, hspace=0.3)
        nplot = nplot + 1

        im = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                 extent=[phi_min, phi_max, alpha_min, alpha_max], aspect='auto')
        pylab.tick_params(axis='both', which='major', labelsize=8)
        pylab.tick_params(axis='both', which='minor', labelsize=6)
        pylab.xticks(numpy.arange(phi_min, phi_max+0.0001, 1.0))
        pylab.text(-0.1, 2.17, name, horizontalalignment='center', verticalalignment='center', fontsize=11)

    pylab.show()


if __name__ == '__main__':
    run_simulation()

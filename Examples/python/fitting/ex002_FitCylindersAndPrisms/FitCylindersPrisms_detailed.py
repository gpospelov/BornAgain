"""
Fitting example
(This is more detailed version of FitCylindersPrisms.py with graphics and generated "real" data)

In this example we use a simple geometry: cylinders and prisms in
air layer, deposited on a substrate layer, with no interference.
There are 4 fitting parameters:
1) radius of cylinders
2) height of cylinders
3) side length of prisms
4) height of prisms

Our reference data is 2D intensity map obtained from the simulation of
the same geometry with fixed values cylinder_height = prism3_height
 = cylinder_radius = prism3_half_side = 5nm.

Then we run our minimization consequently using default
minimization engine, with starting values cylinder_height = prism3_length = 4nm,
cylinder_radius = prism3_half_side = 6nm as initial fit parameter values.
"""


import numpy
import matplotlib
import pylab
import math
from libBornAgainCore import *
from libBornAgainFit import *


def get_sample(cylinder_height=1.0*nanometer,
               cylinder_radius=1.0*nanometer,
               prism_half_side=1.0*nanometer,
               prism_height=1.0*nanometer):
    """
    Build the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_air = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(cylinder_height, cylinder_radius)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(prism_half_side, prism_height)
    prism = Particle(m_particle, prism_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder, 0.0, 0.5)
    particle_decoration.addParticle(prism, 0.0, 0.5)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    This function has been used once to generate Refdata_fitcylinderprisms.txt
    """
    # creating sample with set of parameters we will later try to find during the fit
    sample = get_sample(5.0*nanometer, 5.0*nanometer, 5.0*nanometer, 5.0*nanometer)
    simulation = get_simulation()
    simulation.setSample(sample)

    simulation.runSimulation()
    real_data = simulation.getIntensityData()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    for i in range(0, real_data.getAllocatedSize()):
        amplitude = real_data[i]
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = GenerateNormalRandom(amplitude, sigma)
        if noisy_amplitude < 0.0:
            noisy_amplitude = 0.0
        real_data[i] = noisy_amplitude
    OutputDataIOFactory.writeIntensityData(real_data, 'Refdata_fitcylinderprisms.txt')



def get_simulation():
    """
    Create GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def draw_results(real_data, simulated_data):
    """
    Draw results of several simulations on canvas
    """
    pylab.figure(1)
    pylab.subplot(2, 2, 1)
    im = pylab.imshow(numpy.rot90(real_data + 1, 1),norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
    pylab.colorbar(im)

    pylab.title('\"Real\" data')
    pylab.subplot(2, 2, 2)
    im = pylab.imshow(numpy.rot90(simulated_data + 1, 1),norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
    pylab.colorbar(im)
    pylab.title('Simulated data')

    diff_map = (real_data - simulated_data)/(real_data + 1)
    pylab.subplot(2, 2, 3)
    im = pylab.imshow(numpy.rot90(diff_map, 1),norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
    pylab.colorbar(im)
    pylab.title('Difference map')

    pylab.show()


class DrawObserver(IObserver):
    """
    class which draws fit progress every nth iteration
    """
    def __init__(self, draw_every=10):
        IObserver.__init__(self)
        print "MySampleBuilder ctor"
        self.draw_every_nth = draw_every
    def update(self, fit_suite):
        if fit_suite.getNCalls() % self.draw_every_nth == 0:
            real_data = fit_suite.getFitObjects().getRealData().getArray()
            simulated_data = fit_suite.getFitObjects().getSimulationData().getArray()
            pylab.subplot(2, 2, 1)
            im = pylab.imshow(numpy.rot90(real_data + 1, 1),norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
            pylab.colorbar(im)

            pylab.title('\"Real\" data')
            pylab.subplot(2, 2, 2)
            im = pylab.imshow(numpy.rot90(simulated_data + 1, 1),norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
            pylab.colorbar(im)
            pylab.title('Simulated data')
            print "hello"



def run_fitting():
    """
    run fitting
    """

    #create_real_data() # to generate "real" data

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = OutputDataIOFactory.readIntensityData('Refdata_fitcylinderprisms.txt')

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    pylab.figure(1)
    draw_observer = DrawObserver()
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*FormFactorCylinder/height", 4.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorCylinder/radius", 6.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorPrism3/height", 4.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorPrism3/half_side", 6.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))

    # running fit
    fit_suite.runFit()

    #draw_results(real_data.getArray(), fit_suite.getFitObjects().getSimulationData().getArray())

    print "Fitting completed."
    fit_suite.printResults()
    print "chi2:", fit_suite.getMinimizer().getMinValue()
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError()

if __name__ == '__main__':
    run_fitting()

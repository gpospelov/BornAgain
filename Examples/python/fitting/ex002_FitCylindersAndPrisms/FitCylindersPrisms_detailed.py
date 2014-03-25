"""
Fitting example
(This is more detailed version of FitCylindersPrisms.py.
We show how to generate "real" data and how to draw fit progress.
Take a note, that performance here is determined by poor performance of matplotlib drawing routines.)

In this example we use a simple geometry: cylinders and prisms in
air layer, deposited on a substrate layer, with no interference.
There are 4 fitting parameters:
1) radius of cylinders
2) height of cylinders
3) length of prisms
4) height of prisms

Our reference data is 2D intensity map obtained from the simulation of
the same geometry with fixed values cylinder_height = prism3_height
 = cylinder_radius = prism3_length/2 = 1nm.

Then we run our minimization consequently using default
minimization engine, with starting values cylinder_height = prism3_height = 4nm,
cylinder_radius = prism3_length/2 = 6nm as initial fit parameter values.
"""


import numpy
import matplotlib
import pylab
import math
from libBornAgainCore import *
from libBornAgainFit import *

pylab.ion()
fig = pylab.figure(1)
#fig.canvas.draw()


def get_sample(cylinder_height=1.0*nanometer,
               cylinder_radius=1.0*nanometer,
               prism_length=2.0*nanometer,
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
    cylinder_ff = FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(prism_length, prism_height)
    prism = Particle(m_particle, prism_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.0, 0.5)
    particle_layout.addParticle(prism, 0.0, 0.5)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.setLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    This function has been used once to generate refdata_fitcylinderprisms.txt
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
    OutputDataIOFactory.writeIntensityData(real_data, 'refdata_fitcylinderprisms.txt')



def get_simulation():
    """
    Create GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


class DrawObserver(IObserver):
    """
    class which draws fit progress every nth iteration.
    It has to be attached to fit_suite via AttachObserver command
    """
    def __init__(self, draw_every=10):
        IObserver.__init__(self)
        print "MySampleBuilder ctor"
        self.draw_every_nth = draw_every
    def update(self, fit_suite):
        if fit_suite.getNCalls() % self.draw_every_nth == 0:
            fig.clf()
            # plotting real data
            real_data = fit_suite.getFitObjects().getRealData().getArray()
            simulated_data = fit_suite.getFitObjects().getSimulationData().getArray()
            pylab.subplot(2, 2, 1)
            im = pylab.imshow(numpy.rot90(real_data + 1, 1), norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
            pylab.colorbar(im)
            pylab.title('\"Real\" data')
            # plotting real data
            pylab.subplot(2, 2, 2)
            im = pylab.imshow(numpy.rot90(simulated_data + 1, 1), norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
            pylab.colorbar(im)
            pylab.title('Simulated data')
            # plotting difference map
            diff_map = (real_data - simulated_data)/(real_data + 1)
            pylab.subplot(2, 2, 3)
            im = pylab.imshow(numpy.rot90(diff_map, 1), norm=matplotlib.colors.LogNorm(), extent=[-1.0, 1.0, 0, 2.0], vmin = 0.001, vmax = 1.0)
            pylab.colorbar(im)
            pylab.title('Difference map')
            # plotting parameters info
            pylab.subplot(2, 2, 4)
            pylab.title('Parameters')
            pylab.axis('off')
            pylab.text(0.01, 0.85, "Iteration  " + str(fit_suite.getNCalls()))
            pylab.text(0.01, 0.75, "Chi2       " + str(fit_suite.getFitObjects().getChiSquaredValue()))
            fitpars = fit_suite.getFitParameters()
            for i in range(0, fitpars.size()):
                pylab.text(0.01, 0.55 - i*0.1, str(fitpars[i].getName()) + " " + str(fitpars[i].getValue())[0:5] )

            pylab.draw()



def run_fitting():
    """
    main function to run fitting
    """

    # uncomment to regenerate "real" data
    #create_real_data()

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = OutputDataIOFactory.readIntensityData('refdata_fitcylinderprisms.txt')

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    draw_observer = DrawObserver()
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*FormFactorCylinder/height", 2.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorCylinder/radius", 2.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorPrism3/height", 2.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorPrism3/length", 4.*nanometer, 0.02*nanometer, AttLimits.lowerLimited(0.01))

    # running fit
    fit_suite.runFit()

    print "Fitting completed."
    fit_suite.printResults()
    print "chi2:", fit_suite.getMinimizer().getMinValue()
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError()



if __name__ == '__main__':
    run_fitting()
    pylab.ioff()
    pylab.show()

"""
Two parameter fit of spheres in a hex lattice.
Sample builder approach is used.
"""


import numpy
import matplotlib
import pylab
import math
import ctypes
from libBornAgainCore import *
from libBornAgainFit import *

pylab.ion()
fig = pylab.figure(1)
fig.canvas.draw()


class MySampleBuilder(ISampleBuilder):
    """
    Sample builder is used to build complex samples from set of parameters.
    Given builder produces the sample representing spheres at hex lattice using two parameters as an input:
    radius - radius of spheres
    lattice_constant - hexagonal lattice constant
    """
    def __init__(self):
        ISampleBuilder.__init__(self)
        self.sample = None
        # parameters describing the sample
        self.radius = ctypes.c_double(5.0*nanometer)
        self.lattice_constant = ctypes.c_double(10.0*nanometer)
        # register parameters
        self.registerParameter("radius", ctypes.addressof(self.radius))
        self.registerParameter("lattice_constant", ctypes.addressof(self.lattice_constant))

    # constructs the sample for current values of parameters
    def buildSample(self):
        m_air = HomogeneousMaterial("Air", 0.0, 0.0)
        m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

        sphere_ff = FormFactorFullSphere(self.radius.value)
        sphere = Particle(m_particle, sphere_ff)
        particle_layout = ParticleLayout()
        particle_layout.addParticle(sphere)

        lattice_params = Lattice2DIFParameters()
        lattice_params.m_length_1 = self.lattice_constant.value
        lattice_params.m_length_2 = self.lattice_constant.value
        lattice_params.m_angle = 2*numpy.pi/3.
        lattice_params.m_xi = 0.0*degree

        interference = InterferenceFunction2DLattice(lattice_params)
        pdf = FTDistribution2DCauchy(10*nanometer, 10*nanometer)
        interference.setProbabilityDistribution(pdf)

        particle_layout.addInterferenceFunction(interference)
        air_layer = Layer(m_air)
        air_layer.setLayout(particle_layout)
        substrate_layer = Layer(m_substrate, 0)
        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate_layer)
        self.sample = multi_layer
        return self.sample


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    sim_params = SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    simulation.setSimulationParameters(sim_params)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data. Sample parameters are set to
    radius = 10*nanometer, lattice_constant=20*nanometer
    This parameters we will try to find later during the fit
    """
    sample_builder = MySampleBuilder()
    sample_builder.setParameterValue("radius", 5.0*nanometer)
    sample_builder.setParameterValue("lattice_constant", 10.0*nanometer)

    simulation = get_simulation()
    simulation.setSampleBuilder(sample_builder)

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
    return real_data


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
    simulation = get_simulation()
    sample_builder = MySampleBuilder()
    simulation.setSampleBuilder(sample_builder)

    real_data = create_real_data()

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)
    #fit_suite.setMinimizer( MinimizerFactory.createMinimizer("Minuit2", "Fumili"))
    #fit_suite.setMinimizer( MinimizerFactory.createMinimizer("GSLLMA"))
    #fit_suite.setMinimizer( MinimizerFactory.createMinimizer("Minuit2","Scan"))
    #fit_suite.setMinimizer( MinimizerFactory.createMinimizer("GSLSimAn"))

    draw_observer = DrawObserver()
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*radius", 8.*nanometer, 0.01*nanometer, AttLimits.limited(4., 12.))
    fit_suite.addFitParameter("*lattice_constant", 8.*nanometer, 0.01*nanometer, AttLimits.limited(4., 12.))

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


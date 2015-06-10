"""
Two parameter fit of cylinders.
In this example we are trying to find cylinder's height and radius using chain of minimizers.

During the first fit round Genetic minimizer will be used. It will roughly look for possible global minimas.
After it is done, the second Minuit2 minimizer will continue to find the precise location of local minima.
"""


import numpy
import matplotlib
import pylab
import math
import ctypes
from bornagain import *

pylab.ion()
fig = pylab.figure(1)
fig.canvas.draw()


def get_sample(radius=5*nanometer, height=5*nanometer):
    """
    Build the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    cylinder_ff = FormFactorCylinder(radius, height)
    cylinder = Particle(m_particle, cylinder_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder)

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
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data. Sample parameters are set to
    radius = 10*nanometer, lattice_constant=20*nanometer
    This parameters we will try to find later during the fit
    """
    sample = get_sample(5.0*nanometer, 5.0*nanometer)

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
    return real_data


class DrawObserver(IObserver):
    """
    class which draws fit progress every nth iteration.
    It has to be attached to fit_suite via AttachObserver command
    """
    def __init__(self, draw_every=10):
        IObserver.__init__(self)
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
            pylab.pause(0.01)


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    sample = get_sample()
    sample.printParameters()
    simulation.setSample(sample)

    real_data = create_real_data()

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    draw_observer = DrawObserver()
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    # Here we select starting values being quite far from true values to puzzle our minimizer's as much as possible
    fit_suite.addFitParameter("*height", 1.*nanometer, 0.04*nanometer, AttLimits.limited(0.01, 30.))
    fit_suite.addFitParameter("*radius", 20.*nanometer, 0.06*nanometer, AttLimits.limited(0.01, 30.))

    # Now we create first fig strategy which will run first minimization round using Genetic minimizer.
    # Genetic minimizer is able to explore large parameter space without being trapped by some local minima.
    strategy1 = FitStrategyAdjustMinimizer()
    strategy1.setMinimizer(MinimizerFactory.createMinimizer("Genetic"))
    strategy1.getMinimizer().getOptions().setMaxIterations(5)
    fit_suite.addFitStrategy(strategy1)

    # Second fit strategy will use another algorithm. It will use best parameters found from previous minimization round.
    strategy2 = FitStrategyAdjustMinimizer()
    strategy2.setMinimizer(MinimizerFactory.createMinimizer("Minuit2", "Migrad"))
    fit_suite.addFitStrategy(strategy2)

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


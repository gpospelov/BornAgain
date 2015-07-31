"""
Two parameter fit of cylinders without interference.
Real data contains rectangular mask to simulate and fit only the area inside the mask.
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


def get_sample(radius=5*nanometer, height=10*nanometer):
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
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data. Sample parameters are set to
    radius = 10*nanometer, lattice_constant=20*nanometer
    This parameters we will try to find later during the fit
    """
    sample = get_sample(5.0*nanometer, 10.0*nanometer)

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
            # plotting simulation data
            pylab.subplot(2, 2, 2)
            im = pylab.imshow(numpy.rot90(simulated_data + 1, 1), norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
            pylab.colorbar(im)
            pylab.title('Simulated data')
            # plotting difference map
            #diff_map = (real_data - simulated_data)/(real_data + 1)
            diff_map= fit_suite.getFitObjects().getChiSquaredMap().getArray()
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
    simulation.setSample(sample)

    real_data = create_real_data()

    fit_suite = FitSuite()

    # masking example: two excluded rectangles on the plot
    IntensityDataFunctions.addRectangularMask(real_data, -0.1*degree, 0.1*degree, 0.1*degree, 0.2*degree)  # x1,y1,x2,y2
    IntensityDataFunctions.addRectangularMask(real_data, -0.1*degree, 1.0*degree, 0.1*degree, 1.2*degree)  # x1,y1,x2,y2

    # another mask example: one big square with two excluded areas on it
    # IntensityDataFunctions.addRectangularMask(real_data, -0.6*degree, 0.0*degree, 0.6*degree, 1.5*degree, True)
    # IntensityDataFunctions.addRectangularMask(real_data, -0.1*degree, 0.1*degree, 0.1*degree, 0.2*degree)
    # IntensityDataFunctions.addEllipticMask(real_data, 0.0*degree, 1.2*degree, 0.3*degree, 0.2*degree)

    fit_suite.addSimulationAndRealData(simulation, real_data)

    fit_suite.initPrint(10)

    draw_observer = DrawObserver()
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/FormFactorCylinder/radius", 6.*nanometer, 0.01*nanometer, AttLimits.limited(4., 8.))
    fit_suite.addFitParameter("*/FormFactorCylinder/height", 9.*nanometer, 0.01*nanometer, AttLimits.limited(8., 12.))

    # running fit
    fit_suite.runFit()

    print "Fitting completed."
    fit_suite.printResults()
    print "chi2:", fit_suite.getMinimizer().getMinValue()
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError()


if __name__ == '__main__':
    exit("This example is broken in previous release (BornAgain-1.2.0). Fitting with masks is not possible. "
         "Will be fixed in the next release (BornAgain-1.4.0) scheduled for the end of September, 2015.")
    run_fitting()
    pylab.ioff()
    pylab.show()


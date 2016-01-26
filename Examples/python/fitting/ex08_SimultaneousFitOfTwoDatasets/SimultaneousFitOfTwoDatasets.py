"""
Fitting example: demonstrates how to fit two datasets simultaneously.
"""

import matplotlib
from matplotlib import pyplot as plt
import matplotlib.gridspec as gridspec
import math
import random
from bornagain import *


def get_sample(radius_a=4.0*nanometer, radius_b=4.0*nanometer, height=4.0*nanometer):
    """
    Build the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    formFactor = FormFactorHemiEllipsoid(radius_a, radius_b, height)
    hemiEllipsoid = Particle(m_particle, formFactor)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(hemiEllipsoid)

    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)

    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(incident_alpha=0.2):
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(50, -1.5*degree, 1.5*degree, 50, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, incident_alpha, 0.0*degree)
    return simulation


def create_real_data(incident_alpha):
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample = get_sample(radius_a=5.0*nanometer, radius_b=6.0*nanometer, height=8.0*nanometer)

    simulation = get_simulation(incident_alpha)
    simulation.setSample(sample)

    simulation.runSimulation()
    real_data = simulation.getIntensityData()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 1.0
    for i in range(0, real_data.getTotalNumberOfBins()):
        amplitude = real_data.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = random.gauss(amplitude, sigma)
        if noisy_amplitude < 0.0:
            noisy_amplitude = 0.0
        real_data.setBinContent(i, noisy_amplitude)
    return real_data


class DrawObserver(IFitObserver):
    """
    Draws fit progress every nth iteration. Real data, simulated data and chi2 map will be shown for both datasets.
    """
    def __init__(self, draw_every_nth=10):
        IFitObserver.__init__(self, draw_every_nth)
        self.fig = plt.figure(figsize=(12.8, 10.24))
        self.fig.canvas.draw()
        plt.ion()

    def plot_colormap(self, data, title, min=1, max=1e6):
        im = plt.imshow(data.getArray(),
                        norm=matplotlib.colors.LogNorm(min, max),
                        extent=[data.getXmin()/deg, data.getXmax()/deg, data.getYmin()/deg, data.getYmax()/deg],
                        aspect='auto')
        plt.colorbar(im)
        plt.title(title)

    def plot_datasets(self, fit_suite, canvas):
        for i_dataset in range(0, fit_suite.getNumberOfFitObjects()):
            real_data = fit_suite.getRealData(i_dataset)
            simul_data = fit_suite.getSimulationData(i_dataset)
            chi2_map = fit_suite.getChiSquaredMap(i_dataset)

            plt.subplot(canvas[i_dataset*3])
            self.plot_colormap(real_data, "\"Real\" data - #"+str(i_dataset+1), min=1.0, max=real_data.getMaximum())
            plt.subplot(canvas[1+i_dataset*3])
            self.plot_colormap(simul_data, "Simulated data - #"+str(i_dataset+1), min=1.0, max=real_data.getMaximum())
            plt.subplot(canvas[2+i_dataset*3])
            self.plot_colormap(chi2_map, "Chi2 map - #"+str(i_dataset+1), min=0.001, max=10.0)

    def plot_fit_parameters(self, fit_suite, canvas):
        # fit parameters
        plt.subplot(canvas[6:])
        plt.axis('off')
        plt.text(0.01, 0.95, "Iterations  " + '{:d}     {:s}'.
                 format(fit_suite.getNumberOfIterations(), fit_suite.getMinimizer().getMinimizerName()))
        plt.text(0.01, 0.70, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        fitpars = fit_suite.getFitParameters()
        for i in range(0, fitpars.size()):
            plt.text(0.01, 0.30 - i*0.3,  '{:40.40s}: {:6.3f}'.format(fitpars[i].getName(), fitpars[i].getValue()))

    def update(self, fit_suite):
        self.fig.clf()

        # we divide figure to have 3x3 subplots, with two first rows occupying most of the space
        canvas = matplotlib.gridspec.GridSpec(3, 3, width_ratios=[1, 1, 1], height_ratios=[4, 4, 1])
        canvas.update(left=0.05, right=0.95, hspace=0.4, wspace=0.2)

        self.plot_datasets(fit_suite, canvas)
        self.plot_fit_parameters(fit_suite, canvas)

        plt.draw()
        plt.pause(0.01)

        if fit_suite.isLastIteration():
            plt.ioff()


def run_fitting():
    """
    main function to run fitting
    """

    incident_alpha_angles = [0.1*degree, 0.4*degree]
    fit_suite = FitSuite()
    sample = get_sample()

    for alpha in incident_alpha_angles:
        real_data = create_real_data(incident_alpha=alpha)
        simulation = get_simulation(incident_alpha=alpha)
        simulation.setSample(sample)
        fit_suite.addSimulationAndRealData(simulation, real_data)

    fit_suite.initPrint(10)
    draw_observer = DrawObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/HemiEllipsoid/RadiusX", 4.*nanometer, AttLimits.limited(2., 10.))
    fit_suite.addFitParameter("*/HemiEllipsoid/RadiusY", 6.*nanometer, AttLimits.fixed())
    fit_suite.addFitParameter("*/HemiEllipsoid/Height", 4.*nanometer, AttLimits.limited(2., 10.))

    # running fit
    fit_suite.runFit()

    print "Fitting completed."
    print "chi2:", fit_suite.getChi2()
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError()


if __name__ == '__main__':
    run_fitting()
    plt.show()

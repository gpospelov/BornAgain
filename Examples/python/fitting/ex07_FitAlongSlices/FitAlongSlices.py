"""
Fitting example
This is more detailed version of FitCylindersPrisms.py.
We show how to generate "real" data and how to draw fit progress.

Please take a note, that performance here is determined by poor performance of matplotlib drawing routines.
"""

import matplotlib
from matplotlib import pyplot as plt
import math
from bornagain import *
import numpy

phi_slice_value = 0.0*deg  # position of vertical slice
alpha_slice_value = 0.2*deg  # position of horizontal slice


    # conditions = [
    #     {'title': "Small cylinders, analytical calculations", 'scale': 1,   'integration': False, 'max': 1e+08},
    #     {'title': "Small cylinders, Monte-Carlo integration", 'scale': 1,   'integration': True,  'max': 1e+08},
    #     {'title': "Large cylinders, analytical calculations", 'scale': 100, 'integration': False, 'max': 1e+12},
    #     {'title': "Large cylinders, Monte-Carlo integration", 'scale': 100, 'integration': True,  'max': 1e+12}
    # ]



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
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample = get_sample(5.0*nanometer, 10.0*nanometer)

    simulation = get_simulation()
    simulation.setSample(sample)

    simulation.runSimulation()
    real_data = simulation.getIntensityData()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 1.0
    for i in range(0, real_data.getTotalNumberOfBins()):
        amplitude = real_data.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = GenerateNormalRandom(amplitude, sigma)
        if noisy_amplitude < 0.0:
            noisy_amplitude = 0.0
        real_data.setBinContent(i, noisy_amplitude)
    return real_data


class DrawObserver(IFitObserver):
    """
    Draws fit progress every nth iteration. This class  has to be attached to FitSuite via attachObserver method.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    It is up to the user what to do here.
    """

    def __init__(self, draw_every_nth=10):
        IFitObserver.__init__(self, draw_every_nth)
        self.fig = plt.figure(figsize=(10.25, 7.69))
        self.fig.canvas.draw()
        plt.ion()


    def plot_colormap(self, data, title, min=1, max=1e6):
        plt.subplot(2, 2, 1)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)
        im = plt.imshow(data.getArray(),
                        norm=matplotlib.colors.LogNorm(min, max),
                        extent=[data.getXmin()/deg, data.getXmax()/deg, data.getYmin()/deg, data.getYmax()/deg])
        plt.colorbar(im)
        plt.title(title)

    def plot_horizontal_slices(self, real_data, simul_data):
        plt.subplot(2, 2, 2)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

        real_slice = real_data.projectionX(alpha_slice_value)
        simul_slice = simul_data.projectionX(alpha_slice_value)

        plt.semilogy(real_slice.getBinCenters()/deg, real_slice.getBinValues(), label="real")
        plt.semilogy(simul_slice.getBinCenters()/deg, simul_slice.getBinValues(), label="simul")
        plt.ylim(1.0, real_slice.getMaximum()*10.0)
        plt.xlim(real_slice.getXmin()/deg, real_slice.getXmax()/deg)
        plt.legend(loc='upper right')
        plt.title("Horizontal slice at alpha =" + '{:3.1f}'.format(alpha_slice_value/deg))

    def plot_vertical_slices(self, real_data, simul_data):
        plt.subplot(2, 2, 3)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

        real_slice = real_data.projectionY(phi_slice_value)
        simul_slice = simul_data.projectionY(phi_slice_value)

        plt.semilogy(real_slice.getBinCenters()/deg, real_slice.getBinValues(), label="real")
        plt.semilogy(simul_slice.getBinCenters()/deg, simul_slice.getBinValues(), label="simul")
        plt.ylim(1.0, real_slice.getMaximum()*10.0)
        plt.xlim(real_slice.getXmin()/deg, real_slice.getXmax()/deg)
        plt.legend(loc='upper right')
        plt.title("Vertical slice at phi =" + '{:3.1f}'.format(phi_slice_value/deg))


    def plot_slices(self, slices, title):
        for slice in slices:
            plt.semilogy(slice.getBinCenters()/deg, slice.getBinValues(), label="real")
            plt.xlim(slice.getXmin()/deg, slice.getXmax()/deg)
            plt.ylim(1.0, slice.getMaximum()*10.0)
        plt.legend(loc='upper right')
        plt.title(title)


    def update(self, fit_suite):
        self.fig.clf()
        real_data = fit_suite.getRealData()
        simulated_data = fit_suite.getSimulationData()
        self.plot_colormap(real_data, "\"Real\" data", min=1.0, max=real_data.getMaximum())

        self.plot_horizontal_slices(real_data, simulated_data)
        self.plot_vertical_slices(real_data, simulated_data)

        # real_hslice = real_data.projectionX(alpha_slice_value)
        # simul_hslice = simulated_data.projectionX(alpha_slice_value)

        # plt.subplot(2, 2, 2)
        # slices = []
        # slices.append(real_data.projectionX(alpha_slice_value))
        # slices.append(simulated_data.projectionX(alpha_slice_value))
        # self.plot_slices(slices, "Horizontal slice at alpha =" + '{:3.1f}'.format(alpha_slice_value/deg))

        # self.plot_horizontal_slices(real_data, simulated_data)

        # self.plot_slice(real_hslice, nplot=2, min=1.0, max=real_hslice.getMaximum())
        # self.plot_slice(simul_hslice, nplot=2, min=1.0, max=real_hslice.getMaximum())
        # plt.title("Horizontal slice")
        # plt.legend("Real", "Simulated", loc='upper right')

        # real_vslice = real_data.projectionY(phi_slice_value)
        # simul_vslice = simulated_data.projectionY(phi_slice_value)


        # self.plot(fit_suite.getSimulationData(), "Simulated data", nplot=2, min=1.0, max=real_data.getMaximum())
        # self.plot(fit_suite.getChiSquaredMap(), "Chi2 map", nplot=3, min=0.001, max=10.0)

        plt.subplot(2, 2, 4)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iteration  " + '{:d}     {:s}'.
                 format(fit_suite.getNumberOfIterations(), fit_suite.getMinimizer().getMinimizerName()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        fitpars = fit_suite.getFitParameters()
        for i in range(0, fitpars.size()):
            plt.text(0.01, 0.55 - i*0.1,  '{:30.30s}: {:6.3f}'.format(fitpars[i].getName(), fitpars[i].getValue()))

        plt.draw()
        plt.pause(0.01)

        if fit_suite.isLastIteration():
            plt.ioff()


def run_fitting():
    """
    main function to run fitting
    """

    real_data = create_real_data()

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    # At this point we mask all the detector and then unmask two areas corresponding to the vertical
    # and horizontal lines.
    simulation.maskAll()
    simulation.addMask(HorizontalLine(alpha_slice_value), False)
    simulation.addMask(VerticalLine(phi_slice_value), False)

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)
    draw_observer = DrawObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/FormFactorCylinder/radius", 6.*nanometer, AttLimits.limited(4., 8.))
    fit_suite.addFitParameter("*/FormFactorCylinder/height", 9.*nanometer, AttLimits.limited(8., 12.))

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

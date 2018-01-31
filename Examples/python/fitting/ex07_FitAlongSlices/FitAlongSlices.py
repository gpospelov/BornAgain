"""
Fitting example: fit along slices
"""

import numpy as np
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_slice_value = 0.0*deg  # position of vertical slice
alpha_slice_value = 0.2*deg  # position of horizontal slice


def get_sample(radius=5.0*nm, height=10.0*nm):
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    cylinder_ff = ba.FormFactorCylinder(radius, height)
    cylinder = ba.Particle(m_particle, cylinder_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)

    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample = get_sample(5.0*nm, 10.0*nm)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


class DrawObserver(ba.IFitObserver):
    """
    Draws fit progress every nth iteration. Here we plot slices along real
    and simulated images to see fit progress.
    """

    def __init__(self, draw_every_nth=10):
        ba.IFitObserver.__init__(self, draw_every_nth)
        self.fig = plt.figure(figsize=(10.25, 7.69))
        self.fig.canvas.draw()
        plt.ion()

    def plot_real_data(self, data, nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)
        im = plt.imshow(
            data.getArray(),
            norm=matplotlib.colors.LogNorm(1.0, data.getMaximum()),
            extent=[data.getXmin()/deg, data.getXmax()/deg,
                    data.getYmin()/deg, data.getYmax()/deg])
        plt.colorbar(im)
        plt.title("\"Real\" data")
        plt.xlabel(r'$\phi_f$', fontsize=12)
        plt.ylabel(r'$\alpha_f$', fontsize=12)
        # line representing vertical slice
        plt.plot([phi_slice_value / deg, phi_slice_value / deg],
                 [data.getYmin() / deg, data.getYmax() / deg],
                 color='gray', linestyle='-', linewidth=1)
        # line representing horizontal slice
        plt.plot([data.getXmin() / deg, data.getXmax() / deg],
                 [alpha_slice_value / deg, alpha_slice_value / deg],
                 color='gray', linestyle='-', linewidth=1)

    def plot_slices(self, slices, title, nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.3)
        for label, slice in slices:
            plt.semilogy(slice.getBinCenters()/deg,
                         slice.getBinValues(), label=label)
            plt.xlim(slice.getXmin()/deg, slice.getXmax()/deg)
            plt.ylim(1.0, slice.getMaximum()*10.0)
        plt.legend(loc='upper right')
        plt.title(title)

    def display_fit_parameters(self, fit_suite, nplot):
        plt.subplot(2, 2, nplot)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iteration  " + '{:d}     {:s}'.
                 format(fit_suite.numberOfIterations(),
                        fit_suite.minimizer().minimizerName()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        for index, fitPar in enumerate(fit_suite.fitParameters()):
            plt.text(0.01, 0.55 - index*0.1,
                     '{:30.30s}: {:6.3f}'.format(fitPar.name(), fitPar.value()))

        plt.draw()
        plt.pause(0.01)

    def update(self, fit_suite):
        self.fig.clf()

        real_data = fit_suite.getRealData()
        simul_data = fit_suite.getSimulationData()

        # These lines add to make cast explicit, see Bug #1367
        real_data = ba.Histogram2D.dynamicCast(real_data)
        simul_data = ba.Histogram2D.dynamicCast(simul_data)

        # plot real data
        self.plot_real_data(real_data, nplot=1)

        # horizontal slices
        slices =[
            ("real", real_data.projectionX(alpha_slice_value)),
            ("simul", simul_data.projectionX(alpha_slice_value))
            ]
        title = ( "Horizontal slice at alpha =" +
                  '{:3.1f}'.format(alpha_slice_value/deg) )
        self.plot_slices(slices, title, nplot=2)

        # vertical slices
        slices =[
            ("real", real_data.projectionY(phi_slice_value)),
            ("simul", simul_data.projectionY(phi_slice_value))
            ]
        title = "Vertical slice at phi =" + '{:3.1f}'.format(phi_slice_value/deg)
        self.plot_slices(slices, title, nplot=3)

        # display fit parameters
        self.display_fit_parameters(fit_suite, nplot=4)

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

    # At this point we mask all the detector and then unmask two areas
    # corresponding to the vertical and horizontal lines. This will make
    # simulation/fitting to be performed along slices only.
    simulation.maskAll()
    simulation.addMask(ba.HorizontalLine(alpha_slice_value), False)
    simulation.addMask(ba.VerticalLine(phi_slice_value), False)

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(5)

    draw_observer = DrawObserver(draw_every_nth=5)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/Cylinder/Radius", 6.*nm).setLimited(4., 8.)
    fit_suite.addFitParameter("*/Cylinder/Height", 9.*nm).setLimited(8., 12.)

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())


if __name__ == '__main__':
    run_fitting()
    plt.show()

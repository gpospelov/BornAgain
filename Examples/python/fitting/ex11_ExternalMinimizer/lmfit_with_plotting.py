"""
Example of using external minimizer to fit typical BornAgain simulation
"""
import numpy as np
from matplotlib import colors
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm
import lmfit


def get_sample(radius=5.0*nm, lattice_length=10.0*nm):
    """
    Returns a sample with cylinders and pyramids on a substrate,
    forming a hexagonal lattice.
    """
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    sphere_ff = ba.FormFactorFullSphere(radius)
    sphere = ba.Particle(m_particle, sphere_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(sphere)

    interference = ba.InterferenceFunction2DLattice.createHexagonal(lattice_length)
    pdf = ba.FTDecayFunction2DCauchy(10*nm, 10*nm)
    interference.setDecayFunction(pdf)

    particle_layout.setInterferenceFunction(interference)

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

    # spoiling simulated data with noise to produce "real" data
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def residual(params, simulation, data):
    radius = params['radius'].value
    length = params['length'].value
    print(radius, length)
    sample = get_sample(radius=radius, lattice_length=length)
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.result().array().flatten()
    exp = data.flatten()
    res = result-exp
    return res


class Plotter:
    def __init__(self):

        self._fig = plt.figure(figsize=(10.25, 7.69))
        self._fig.canvas.draw()

    def make_subplot(self, nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

    def reset(self):
        self._fig.clf()

    def plot(self, simulation, data):
        self.reset()

        sim_data = simulation.result().histogram2d()

        real_data = simulation.result().histogram2d()
        real_data.setContent(data)

        zmax = real_data.getMaximum()
        zmin = zmax*1e-6

        self.make_subplot(1)
        ba.plot_histogram(real_data, title="Real data", zmin=zmin, zmax=zmax, zlabel='')

        self.make_subplot(2)
        ba.plot_histogram(sim_data, title="Simulated data", zmin=zmin, zmax=zmax, zlabel='')

        self.make_subplot(3)
        sim_array = sim_data.getArray()
        exp_array = real_data.getArray()

        rel_diff = 2.0 * np.abs(sim_array - exp_array) / (sim_array + exp_array)
        im = plt.imshow(rel_diff, norm=colors.LogNorm(1e-6, 1.0), aspect='auto')
        cb = plt.colorbar(im, pad=0.025)
        plt.xlabel('X, bins', fontsize=14)
        plt.ylabel('Y, bins', fontsize=14)
        plt.title("Relative difference")

        plt.tight_layout()
        plt.pause(0.03)

    def iter_cb(self, params, iter, resid, simulation, data):
        self.plot(simulation, data)


def run_fitting():
    """
    main function to run fitting
    """
    simulation = get_simulation()
    sample = get_sample()
    simulation.setSample(sample)

    real_data = create_real_data()

    params = lmfit.Parameters()
    params.add('radius', value=8*nm, min=0.01, max=12)
    params.add('length', value=8*nm, min=0.01, max=12)

    plotter = Plotter()

    result = lmfit.minimize(residual, params, iter_cb=plotter.iter_cb, args=(simulation, real_data))

    result.params.pretty_print()
    print(lmfit.fit_report(result))


if __name__ == '__main__':
    run_fitting()
    plt.show()



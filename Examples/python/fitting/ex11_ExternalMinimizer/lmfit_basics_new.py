"""
Example of using external minimizer to fit typical BornAgain simulation
"""
import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm
import lmfit


real_data = None

def get_sample(params):
    """
    Returns a sample with cylinders and pyramids on a substrate,
    forming a hexagonal lattice.
    """
    radius = params['radius'].value
    lattice_length = params['length'].value
    print(radius, lattice_length)

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


def get_simulation(params):
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    params = lmfit.Parameters()
    params.add('radius', value=5*nm)
    params.add('length', value=10*nm)
    simulation = get_simulation(params)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with noise to produce "real" data
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def residual(params):
    simulation = get_simulation(params)
    simulation.runSimulation()
    result = simulation.result().array().flatten()
    exp = real_data.flatten()
    res = result-exp
    return res


def evaluate(params, objective, real_data):
    bapars = ba.Parameters()
    print(type(params))
    for p in params:
        print(type(p), type(params[p]))
        bapars.add(p, params[p].value)

    return objective.evaluate_residuals(bapars)



def run_fitting():
    """
    main function to run fitting
    """
    global real_data
    real_data = create_real_data()
    print(real_data, real_data.shape)

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)

    params = lmfit.Parameters()
    params.add('radius', value=8*nm)
    params.add('length', value=8*nm)

    result = lmfit.minimize(evaluate, params, args=(fit_objective, real_data))

    result.params.pretty_print()
    print(lmfit.fit_report(result))
    print("Done")


if __name__ == '__main__':
    run_fitting()
    plt.show()



"""
Example demonstrates how to fit several sample parameters with one fit parameter.
Our sample represents cylindrical particles in rectangular lattice. We are going
to fit the data, assuming that cylinder radius, height and both lattice lengths
are the same.

"Real data" was generated for
cylinder_radius = cylinder_height = lattice_length1 = lattice_length2 = 8*nm

Then we create a fit setup, where one fit parameter will steer all corresponding
sample parameters, namely

/MultiLayer/Layer0/ParticleLayout/Interference2DLattice/BasicLattice/LatticeLength1
/MultiLayer/Layer0/ParticleLayout/Interference2DLattice/BasicLattice/LatticeLength2
/MultiLayer/Layer0/ParticleLayout/Particle/Cylinder/Radius
/MultiLayer/Layer0/ParticleLayout/Particle/Cylinder/Height
"""

import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Returns a sample with cylinders on a substrate,
    forming a rectangular lattice.
    """
    radius = params["custom_length"]
    height = params["custom_length"]
    lattice_constant = params["custom_length"]

    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    ff = ba.FormFactorCylinder(radius, height)
    cylinder = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder)

    interference = ba.InterferenceFunction2DLattice(
        lattice_constant, lattice_constant, 90.0*deg)
    pdf = ba.FTDecayFunction2DCauchy(50*nm, 50*nm)
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
    params = {'custom_length': 8.0*nm}

    simulation = get_simulation(params)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def run_fitting():
    """
    main function to run fitting
    """
    real_data = create_real_data()

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)
    fit_objective.initPrint(10)
    fit_objective.initPlot(10)

    params = ba.Parameters()
    params.add("custom_length", 9.0*nm, min=6.0*nm, max=10.0*nm)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)

    fit_objective.finalize(result)

    print("Fitting completed.")
    print("chi2:", result.minValue())
    for fitPar in result.parameters():
        print(fitPar.name(), fitPar.value, fitPar.error)


if __name__ == '__main__':
    run_fitting()
    plt.show()

"""
Fitting example: running same fit using various minimizer and their settings.
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(cylinder_height=5.0*nm, cylinder_radius=5.0*nm,
               prism_length=5.0*nm, prism_height=5.0*nm):
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(prism_length, prism_height)
    prism = ba.Particle(m_particle, prism_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    return simulation


def run_fitting():
    """
    run fitting
    """

    # prints info about available minimizers
    print(ba.MinimizerFactory().catalogueToString())

    # prints detailed info about available minimizers and their options
    print(ba.MinimizerFactory().catalogueDetailsToString())

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = ba.IntensityDataIOFactory.readIntensityData(
        'refdata_fitcylinderprisms.int.gz')

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*Cylinder/Height", 4.*nm).setLowerLimited(0.01)
    fit_suite.addFitParameter("*Cylinder/Radius", 6.*nm).setLowerLimited(0.01)
    fit_suite.addFitParameter("*Prism3/Height", 4.*nm).setLowerLimited(0.01)
    fit_suite.addFitParameter("*Prism3/BaseEdge", 12.*nm).setLowerLimited(0.01)

    # Uncomment one of the line below to adjust minimizer settings

    # setting Minuit2 minimizer with Migrad algorithm, limiting number of iterations
    # Minimization will try to respect MaxFunctionCalls value
    # fit_suite.setMinimizer("Minuit2", "Migrad", "MaxFunctionCalls=100")

    # Setting two options at once.
    # Strategy=2 promises more accurate fit.
    # fit_suite.setMinimizer("Minuit2", "Simplex", "MaxFunctionCalls=100;Strategy=2")

    # setting Minuit2 minimizer with Fumili algorithm
    # fit_suite.setMinimizer("Minuit2", "Fumili")

    # Setting Levenberg-Marquardt algorithm
    # fit_suite.setMinimizer("GSLLMA")

    # Setting Genetic algorithm.It requires all parameters
    # to be limited, so we recreate parameters with min and max defined
    # fit_suite.fitParameters().clear()
    # fit_suite.addFitParameter("*Cylinder/Height", 4.*nm).setLimited(3.0, 8.0)
    # fit_suite.addFitParameter("*Cylinder/Radius", 6.*nm).setLimited(3.0, 8.0)
    # fit_suite.addFitParameter("*Prism3/Height", 4.*nm).setLimited(3.0, 8.0)
    # fit_suite.addFitParameter("*Prism3/BaseEdge", 4.*nm).setLimited(3.0, 8.0)
    # fit_suite.setMinimizer("Genetic", "Default",
    # "MaxIterations=2;PopSize=200;RandomSeed=1")

    # running fit with default minimizer
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for par in fit_suite.fitParameters():
        print(par.name(), par.value(), par.error())

if __name__ == '__main__':
    run_fitting()

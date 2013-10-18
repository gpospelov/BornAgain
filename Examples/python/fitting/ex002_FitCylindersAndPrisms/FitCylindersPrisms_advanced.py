"""
Fitting example
In this example we use a simple geometry: cylinders and prisms in
air layer, deposited on a substrate layer, with no interference. 
There are 4 fitting parameters: radius and height of cylinders and
 side length and height of prisms. 
 
Our reference data is 2D intensity map obtained from the simulation of
the same geometry with fixed values cylinder_height = prism3_height
 = cylinder_radius = prism3_half_side = 5nm.
 
Then we run our minimization consequently using default
minimization engine, with cylinder_height = prism3_length = 4nm,
cylinder_radius = prism3_half_side = 6nm as initial fit parameter values.
"""
import numpy
import matplotlib
import pylab
from libBornAgainCore import *
from libBornAgainFit import *


# values we want to find
cylinder_height = 5.0*nanometer
cylinder_radius = 5.0*nanometer
prism3_half_side = 5.0*nanometer
prism3_height = 5.0*nanometer

def get_sample():
    """
    Build and return the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_air = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(5*nanometer, 5*nanometer)
    prism = Particle(m_particle, prism_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder, 0.0, 0.5)
    particle_decoration.addParticle(prism, 0.0, 0.5)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def create_real_data(simulation):
    """
    Generating "real" data by adding noise to the simulated data.
    This function has been used once to generate Refdata_fitcylinderprisms.txt
    """
    simulation.runSimulation()
    real_data = simulation.getOutputDataClone()
    noise_factor = 0.1
    for i in range(0, real_data.getAllocatedSize()):
        amplitude = real_data[i]
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = GenerateNormalRandom(amplitude, sigma)
        if noisy_amplitude < 0.0:
            noisy_amplitude = 0.0
        real_data[i] = noisy_amplitude
    OutputDataIOFactory.writeOutputData(real_data, 'Refdata_fitcylinderprisms.txt')
    return real_data


def run_fitting():
    """
    run fitting
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = OutputDataIOFactory.getOutputData('Refdata_fitcylinderprisms.txt')
    
    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    # setting fitting minimizer
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2", "Migrad"))  #: default
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2", "Simplex"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2", "Combined"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2", "Scan"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2", "Fumili"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin", "ConjugateFR"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin", "ConjugatePR"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin", "BFGS"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin", "BFGS2"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin", "SteepestDescent"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiFit"))
    #fit_suite.setMinimizer(MinimizerFactory.createMinimizer("GSLSimAn"))

    # setting fitting parameters
    fit_suite.addFitParameter("*FormFactorCylinder/height", 4.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorCylinder/radius", 6.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorPrism3/height", 4.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*FormFactorPrism3/half_side", 6.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01))

    # running fit
    fit_suite.runFit()

    print "Fitting completed."
    print "chi2:", fit_suite.getMinimizer().getMinValue()
    pars = fit_suite.getMinimizer().getValueOfVariablesAtMinimum()
    errs = fit_suite.getMinimizer().getErrorOfVariables()
    print "variables at minimum:", pars[0], pars[1], pars[2], pars[3]
    print "errors at minimum:", errs[0], errs[1], errs[2], errs[3]


if __name__ == '__main__':
    run_fitting()

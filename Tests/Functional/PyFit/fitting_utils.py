import sys
import os
from __future__ import print_function

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0], '..', '..', '..', 'lib')))

from libBornAgainCore import *
from libBornAgainFit import *


CYLINDER_HEIGHT = 5.0
CYLINDER_RADIUS = 5.0

def getReferenceParameters():
    return [CYLINDER_HEIGHT, CYLINDER_RADIUS]


def get_sample():
    """
    Returns test sample
    """
    global CYLINDER_HEIGHT
    global CYLINDER_RADIUS
    cylinder_ff = FormFactorCylinder(CYLINDER_HEIGHT, CYLINDER_RADIUS)
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)
    cylinder = Particle(mParticle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder)
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Returns test simulation
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(50, 0.0*degree, 2.0*degree, 50, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setBeamIntensity(1e10)
    simulation.setSample(get_sample())
    return simulation


def get_real_data():
    """
    Returns 'real' data
    """
    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.getIntensityData()


def get_fit_suite(minimizer, algorithm):
    """
    Creates FitSuite fully ready for minimization
    """
    fit_suite = FitSuite()
    fit_suite.addFitParameter("*Height", 4.*nanometer, 0.04*nanometer, AttLimits.limited(2.0, 8.0))
    fit_suite.addFitParameter("*Radius", 6.*nanometer, 0.06*nanometer, AttLimits.limited(2.0, 8.0))
    fit_suite.addSimulationAndRealData(get_simulation(), get_real_data())
    fit_suite.setMinimizer(MinimizerFactory.createMinimizer(minimizer, algorithm))
    return fit_suite


def print_fit_results(fit_suite):
    fitpars = fit_suite.getFitParameters()
    refpars = getReferenceParameters()
    print("-"*30)
    print("RealTime  :", fit_suite.getMinimizer().getMinimizerName(),
          fit_suite.getMinimizer().getAlgorithmName())
    print("RealTime  : {0:.3f} sec".format(fit_suite.getRunTime()))
    print("NCalls    : {0:<5d}".format(fit_suite.getNCalls()))
    for i in range(0, fitpars.size()):
        print('par{0:2d}     : {1:.4f} ({2:.3g}) '.format(
            i, fitpars[0].getValue(), fitpars[i].getValue() - refpars[i]))


def run_fit_suite(minimizer, algorithm=""):
    fit_suite = get_fit_suite(minimizer, algorithm)
    fit_suite.initPrint(100 )
    fit_suite.runFit()
    print_fit_results(fit_suite)
    return fit_suite.getFitParameters().getValues(), getReferenceParameters()

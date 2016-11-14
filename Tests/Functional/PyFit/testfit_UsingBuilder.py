# functional test: fitting using sample builder
#
# This test shows how to use SampleBuilder class for constructing the sample
# and running fitting.

from __future__ import print_function
import sys
import ctypes
import math

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
from bornagain import *

# values we want to find
cylinder_height = 5.0*nanometer
cylinder_radius = 5.0*nanometer
prism3_half_side = 5.0*nanometer
prism3_height = 5.0*nanometer
cylinder_ratio = 0.2


def runTest():
    """
    run minimization using sample builder
    """

    # setting sample builder to initial values
    sample_builder = MySampleBuilder()
    sample_builder.setParameterValue("cylinder_height", cylinder_height)
    sample_builder.setParameterValue("cylinder_radius", cylinder_radius)
    sample_builder.setParameterValue("prism3_half_side", prism3_half_side)
    sample_builder.setParameterValue("prism3_height", prism3_height)
    sample_builder.setParameterValue("cylinder_ratio", cylinder_ratio)

    simulation = createSimulation()
    simulation.setSampleBuilder(sample_builder)

    real_data = createRealData(simulation)

    # setting up fitting
    fitSuite = FitSuite()
    fitSuite.setMinimizer("Minuit2", "Combined")
    fitSuite.initPrint(10)
    fitSuite.addFitParameter(
        "*SampleBuilder/cylinder_height",  4*nanometer,  AttLimits.lowerLimited(0.01))
    fitSuite.addFitParameter(
        "*SampleBuilder/cylinder_radius",  6*nanometer,  AttLimits.lowerLimited(0.01))
    fitSuite.addFitParameter(
        "*SampleBuilder/prism3_half_side", 4*nanometer,  AttLimits.lowerLimited(0.01))
    fitSuite.addFitParameter(
        "*SampleBuilder/prism3_height",    6*nanometer,  AttLimits.lowerLimited(0.01))
    fitSuite.addFitParameter(
        "*SampleBuilder/cylinder_ratio", 0.2, AttLimits.fixed())

    # chiModule = ChiSquaredModule()
    # chiModule.setChiSquaredFunction( SquaredFunctionMeanSquaredError() )

    # fitSuite.addSimulationAndRealData(simulation, real_data, chiModule)
    fitSuite.addSimulationAndRealData(simulation, real_data)
    fitSuite.runFit()

    # analysing fit results
    initialParameters = [ cylinder_height, cylinder_radius,
                          prism3_half_side, prism3_height, cylinder_ratio]
    results = fitSuite.fitParameters().values()
    threshold = 1.0e-02
    status = "OK"
    for i in range(0, len(initialParameters)):
        diff = abs(results[i] - initialParameters[i])/initialParameters[i]
        if(diff > threshold): status = "FAILED"

    return "TestFit02", "Fitting using sample builder.", status


# create simulation
def createSimulation():
    simulation = GISASSimulation()
    simulation.setDetectorParameters(50, 0.0*degree, 2.0*degree, 50, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    #simulation.setBeamIntensity(1e10);
    return simulation


# generating "real" data by adding noise to the simulated data
def createRealData(simulation):
    simulation.runSimulation()
    real_data = simulation.getIntensityData()
    noise_factor = 0.1
    for i in range(0, real_data.getTotalNumberOfBins()):
        amplitude = real_data.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = GenerateNormalRandom(amplitude, sigma)
        if noisy_amplitude < 0.0:
            noisy_amplitude = 0.0
        real_data.setBinContent(i, noisy_amplitude)
    return real_data


# ----------------------------------------------------------------------------
# Sample builder to build mixture of cylinders and prisms on top of substrate
# 5 parameters
# ----------------------------------------------------------------------------
class MySampleBuilder(IMultiLayerBuilder):
    def __init__(self):
        IMultiLayerBuilder.__init__(self)
        print("MySampleBuilder ctor")
        self.sample = None
        # parameters describing the sample
        self.cylinder_height = ctypes.c_double(5.0*nanometer)
        self.cylinder_radius = ctypes.c_double(5.0*nanometer)
        self.prism3_half_side = ctypes.c_double(5.0*nanometer)
        self.prism3_height = ctypes.c_double(5.0*nanometer)
        self.cylinder_ratio = ctypes.c_double(0.2)
        # register parameters
        self.registerParameter("cylinder_height", ctypes.addressof(self.cylinder_height)).\
            setUnit("nm").setNonnegative()
        self.registerParameter("cylinder_radius", ctypes.addressof(self.cylinder_radius)).\
            setUnit("nm").setNonnegative()
        self.registerParameter("prism3_half_side", ctypes.addressof(self.prism3_half_side)).\
            setUnit("nm").setNonnegative()
        self.registerParameter("prism3_height", ctypes.addressof(self.prism3_height)).\
            setUnit("nm").setNonnegative()
        self.registerParameter("cylinder_ratio", ctypes.addressof(self.cylinder_ratio)).\
            setNonnegative()

    # constructs the sample for current values of parameters
    def buildSample(self):
        multi_layer = MultiLayer()
        air_material = HomogeneousMaterial("Air", 0.0, 0.0)
        substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)
        air_layer = Layer(air_material)
        substrate_layer = Layer(substrate_material)

        cylinder_ff = FormFactorCylinder(self.cylinder_height.value, self.cylinder_radius.value)
        prism_ff = FormFactorPrism3(self.prism3_height.value, self.prism3_half_side.value)
        cylinder = Particle(mParticle, cylinder_ff)
        prism = Particle(mParticle, prism_ff)
        interference = InterferenceFunctionNone()

        particle_layout = ParticleLayout()
        particle_layout.addParticle(cylinder, self.cylinder_ratio.value)
        particle_layout.addParticle(prism, 1.0 - self.cylinder_ratio.value)
        particle_layout.addInterferenceFunction(interference)

        air_layer.addLayout(particle_layout)
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate_layer)
        return multi_layer


if __name__ == '__main__':
    name, description, status = runTest()
    print(name, description, status)
    if "FAILED" in status:
        exit(1)

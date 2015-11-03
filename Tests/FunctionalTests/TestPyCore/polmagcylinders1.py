# Functional test: Magnetic cylinders in DWBA with zero magnetic field
import sys
import os
import numpy
import gzip
from utils import get_difference
from utils import get_reference_data

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))


from libBornAgainCore import *


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)

    magnetic_field = kvector_t(0, 0, 0)

    magParticle = HomogeneousMagneticMaterial("magParticle", 6e-4, 2e-8, magnetic_field )
    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(magParticle, cylinder_ff)
    
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, 0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def run_test():
    result = RunSimulation()
    # IntensityDataIOFactory.writeIntensityData(result, 'polmagcylinders1_reference.int')

    reference = get_reference_data('polmagcylinders1_reference.int.gz')

    diff = get_difference(result.getArray(), reference.getArray())

    status = "OK"
    if diff > 2e-10:
        status = "FAILED"
    return "PolarizedDWBAZeroMag", "Polarized DWBA with zero magnetic field", diff, status


if __name__ == '__main__':
    name, description, diff, status = run_test()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)

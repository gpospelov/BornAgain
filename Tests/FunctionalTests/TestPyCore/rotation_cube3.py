import sys
import os
import utils
from bornagain import *



def get_sample(formfactor, rot, pos, layout_rot, layout_pos):
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)

    particle = Particle(mParticle, formfactor)
    if pos:
        particle.setPosition(pos)
    if rot:
        particle.setRotation(rot)

    layout = ParticleLayout()
    if layout_rot:
        layout.addParticle(particle, layout_rot)
    else:
        layout.addParticle(particle)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(layout)
    substrate = Layer(mSubstrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate)
    return multi_layer


def get_simulation(sample):
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(sample)
    return simulation


def get_intensity_data(data):
    ff = data[0]
    rot = data[1]
    pos = data[2]
    layout_rot = data[3]
    layout_pos = data[4]
    sample = get_sample(ff, rot, pos, layout_rot, layout_pos)
    simulation = get_simulation(sample)
    simulation.runSimulation()
    return simulation.getIntensityData()


def get_difference(reference_data, test_data):
    intensity = get_intensity_data(test_data)
    return IntensityDataFunctions.getRelativeDifference(reference_data, intensity)
  

def testRotationZ():

    box = FormFactorBox(10, 10, 10)

    data_to_test = [
        # ff  rot                     pos                    layout_rot              layout_pos
        (box, None,                   None,                  None,                   None),  # reference
        (box, RotationZ(90.*degree),  None,                  None,                   None),  # rotating particle
        (box, RotationZ(-90.*degree), None,                  None,                   None),
        (box, RotationZ(180.*degree), None,                  None,                   None),
        (box, None,                   None,                  RotationZ(90.*degree),  None),  # rotating through layout
        (box, RotationZ(45.*degree),  None,                  RotationZ(45.*degree),  None),  # cumulative rotation
    ]

    reference_data = get_intensity_data(data_to_test[0])

    for i in range(1, len(data_to_test)):
        diff = get_difference(reference_data, data_to_test[i])
        print i, diff


def runTests():
    testRotationZ()





if __name__ == '__main__':
    runTests()


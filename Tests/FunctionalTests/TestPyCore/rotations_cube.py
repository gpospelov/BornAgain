# Rotation functional test
import sys
import os
import utils
import unittest
from bornagain import *


class TestAssistant:
    def __init__(self):
        self.reference_data = self.create_reference_data()

    def get_cube_formfactor(self):
        """
        Creates formfactor of the cube
        """
        length = 10*nanometer
        width = 10*nanometer
        height = 10.*nanometer
        box_ff = FormFactorBox(length, width, height)
        return box_ff

    def get_air_layer(self):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        return Layer(mAmbience)

    def get_substrate_layer(self):
        mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        return Layer(mSubstrate)

    def get_particle(self, rotation=None, position=None):
        mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)
        particle = Particle(mParticle, self.get_cube_formfactor())
        if rotation:
            particle.setRotation(rotation)
        if position:
            particle.setPosition(position)
        return particle

    def get_particle_layout(self, particle, rotation=None):
        particle_layout = ParticleLayout()
        if rotation:
            particle_layout.addParticle(particle, rotation)
        else:
            particle_layout.addParticle(particle)
        return particle_layout

    def get_sample(self, particle_layout):
        air_layer = self.get_air_layer()
        air_layer.addLayout(particle_layout)
        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(self.get_substrate_layer())
        return multi_layer

    def get_simulation(self, sample):
        simulation = GISASSimulation()
        simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
        simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
        simulation.setSample(sample)
        return simulation

    def get_intensity_data(self, sample):
        simulation = self.get_simulation(sample)
        simulation.setSample(sample)
        simulation.runSimulation()
        return simulation.getIntensityData()

    def create_reference_data(self):
        particle = self.get_particle()
        layout = self.get_particle_layout(particle)
        sample = self.get_sample(layout)
        return self.get_intensity_data(sample)

    # def get_difference(self, intensity):
    #     return IntensityDataFunctions.getRelativeDifference(self.reference_data, intensity)

    def get_result(self, layout):
        sample = self.get_sample(layout)
        intensity = self.get_intensity_data(sample)
        return IntensityDataFunctions.getRelativeDifference(self.reference_data, intensity)


assistant = TestAssistant()

class RotationsCubeTest(unittest.TestCase):
    """
    Test of rotations of cubic particles in two layer system
    """
    def test_RotationZ(self):
        angles = [90, 180, 270, 360., -90.]
        for angle in angles:
            particle = assistant.get_particle(RotationZ(angle*degree))
            layout = assistant.get_particle_layout(particle)
            self.assertLess(assistant.get_result(layout), 1e-10)
        print "In method", self._testMethodName

    def test_RotationZAccum(self):
        particle = assistant.get_particle(RotationZ(45.0*degree))
        # particle = assistant.get_particle()
        layout = assistant.get_particle_layout(particle, RotationZ(45.0*degree))
        self.assertLess(assistant.get_result(layout), 1e-10)


    def test_RotationY(self):
        particle = assistant.get_particle(RotationY(90*degree), kvector_t(0.0, 0.0, 5.0))
        layout = assistant.get_particle_layout(particle)
        diff = assistant.get_result(layout)
        self.assertLess(diff, 1e-10)
        print "In method", self._testMethodName


if __name__ == '__main__':
    # run_test()
    # unittest.main()
    # tt = RotationsCubeTest()
    # tt.test_MyTest()

    box = FormFactorBox(10, 10, 10)
    conditions = [
        {'ff': box, 'rot': None,                    'pos': None, 'lrot': None, 'lpos': None},
        {'ff': box, 'rot': RotationZ(-90.*degree),  'pos': None, 'lrot': None, 'lpos': None},
        {'ff': box, 'rot': RotationZ(90.*degree),   'pos': None, 'lrot': None, 'lpos': None},
        {'ff': box, 'rot': RotationZ(180.*degree),  'pos': None, 'lrot': None, 'lpos': None},

        {'ff': box, 'rot': None,                    'pos': None, 'lrot': RotationZ(90.*degree), 'lpos': None},

        {'ff': box, 'rot': RotationZ(180.*degree),  'pos': kvector_t(0,0,0), 'lrot': RotationZ(90.*degree), 'lpos': kvector_t(0,0,0)},
    ]

    cc = [
        # ff  rot                     pos                    layout_rot              layout_pos
        (box, None,                   None,                  None,                   None),  # reference
        (box, RotationZ(90.*degree),  None,                  None,                   None),  # rotating particle
        (box, RotationZ(-90.*degree), None,                  None,                   None),
        (box, RotationZ(180.*degree), None,                  None,                   None),
        (box, None,                   None,                  RotationZ(90.*degree),  None),  # rotating through layout
        (box, RotationZ(45.*degree),  None,                  RotationZ(45.*degree),  None),  # accumulative rotation
    ]
    print cc[1][1]


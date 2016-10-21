"""
Test of rotation/position of box in the middle layer of 3 layers system.

FormFactorBox(50, 20, 10), is rotated around Z, then around Y, then shifted up and then
compared with FormFactorBox(10, 50, 20)
"""
from __future__ import print_function
import unittest
import utils
import sys
import os

from libBornAgainCore import *

layer_thickness = 100

class BoxTransformationsTest(unittest.TestCase):

    def get_sample(self, particle):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        mMiddle= HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9)
        mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)

        layout = ParticleLayout()
        layout.addParticle(particle)

        air_layer = Layer(mAmbience)
        middle_layer = Layer(mMiddle, layer_thickness)
        middle_layer.addLayout(layout)
        substrate = Layer(mSubstrate)

        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(middle_layer)
        multi_layer.addLayer(substrate)
        return multi_layer

    def get_intensity_data(self, particle):
        sample = self.get_sample(particle)
        simulation = utils.get_simulation_MiniGISAS(sample)
        simulation.runSimulation()
        return simulation.getIntensityData()

    def testBoxTransform(self):
        """
        Reference box of (10,50,20) size is compared against the box (50,20,10) with two rotations applied to get
        reference one
        """
        mParticle = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

        # reference box
        length = 10
        width = 50
        height = 20

        box = Particle(mParticle, FormFactorBox(length, width, height))
        box.setPosition(kvector_t(0, 0, -layer_thickness/2 - height/2))
        reference_data = self.get_intensity_data(box)
        #utils.plot_intensity_data(reference_data)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_TransformBox.int")

        # second box
        length = 50
        width = 20
        height = 10
        box = Particle(mParticle, FormFactorBox(length, width, height))
        box.setRotation(RotationZ(90.*degree))
        box.applyRotation(RotationY(90.*degree))
        box.setPosition(kvector_t(0, 0, -layer_thickness/2))

        data = self.get_intensity_data(box)

        diff = getRelativeDifference(data, reference_data)
        print(diff)
        self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()

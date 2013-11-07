# tests of IntensityData object

import sys
import os
import unittest
import numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


class IntensityDataTest(unittest.TestCase):
    """
    Test creation of IntensityData object and different ways of accessing its data
    """
    def test_empty_data(self):
        data = IntensityData()
        self.assertEqual(1, data.getAllocatedSize())
        self.assertEqual(0, data.getRank())
        self.assertEqual(0, data.totalSum())

    def test_create_1d_object(self):
        axis0 = AxisDouble("angle", 20, 0.0, 20.)
        self.assertEqual(20, axis0.getSize())
        self.assertEqual(0.0, axis0.getMin())
        self.assertEqual(20.0, axis0.getMax())
        data = IntensityData()
        data.addAxis(axis0)
        self.assertEqual(20, data.getAllocatedSize())
        self.assertEqual(1, data.getRank())
        self.assertEqual(0, data.totalSum())

    def test_create_2d_object(self):
        data = IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        self.assertEqual(200, data.getAllocatedSize())
        self.assertEqual(2, data.getRank())
        self.assertEqual(0, data.totalSum())
        data.setAllTo(1.0)
        self.assertEqual(200.0, data.totalSum())
        for i in range(0, data.getAllocatedSize()):
            data[i] = data[i]*-1.0
        self.assertEqual(-200.0, data.totalSum())

    def test_access_simulation_intensity(self):
        simulation = Simulation()
        simulation.setDetectorParameters(10, -1.0, 1.0, 100, 0.0, 2.0)
        data = simulation.getIntensityData()
        self.assertEqual(1000, data.getAllocatedSize())
        self.assertEqual(2, data.getRank())
        self.assertEqual(0, data.totalSum())
        self.assertEqual(10, data.getAxis(0).getSize())
        self.assertEqual(-1.0, data.getAxis(0).getMin())
        self.assertEqual(1.0, data.getAxis(0).getMax())
        self.assertEqual(100, data.getAxis(1).getSize())
        self.assertEqual(0.0, data.getAxis(1).getMin())
        self.assertEqual(2.0, data.getAxis(1).getMax())

        self.assertEqual(11, len(data.getAxis(0).getVector()))

    def test_numpy_array(self):
        data = IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        data.setAllTo(1)
        arr = data.getArray()
        self.assertEqual( (10,20), data.getArray().shape)
        self.assertEqual( (data.totalSum()), numpy.sum(data.getArray()) )


if __name__ == '__main__':
    unittest.main()

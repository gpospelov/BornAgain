# Functional test: tests of IntensityData object

import sys
import os
import unittest
import numpy

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
from libBornAgainCore import *

def get_axis():
    simulation = GISASSimulation()
    simulation.setDetectorParameters(10, -1.0, 1.0, 100, 0.0, 2.0)
    data = simulation.getIntensityData()
    axis = data.getXaxis()
    return axis


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
        axis0 = FixedBinAxis("angle", 20, 0.0, 20.)
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
        simulation = GISASSimulation()
        simulation.setDetectorParameters(10, -1.0, 1.0, 100, 0.0, 2.0)
        data = simulation.getIntensityData()
        self.assertEqual(1000, data.getTotalNumberOfBins())
        self.assertEqual(2, data.getRank())
        self.assertEqual(0, data.integral())
        self.assertEqual(10, data.getXaxis().getSize())
        #self.assertEqual(-1.0, data.getAxis(0).getMin())
        #self.assertEqual(1.0, data.getAxis(0).getMax())
        #self.assertEqual(100, data.getAxis(1).getSize())
        #self.assertEqual(0.0, data.getAxis(1).getMin())
        #self.assertEqual(2.0, data.getAxis(1).getMax())
        #self.assertEqual(11, len(data.getAxis(0).getVector()))

    def test_axis_ownership(self):
        axis0 = get_axis()
        self.assertEqual(10, axis0.getSize())

    def test_numpy_array(self):
        data = IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        data.setAllTo(1)
        self.assertEqual( (20,10), data.getArray().shape)
        self.assertEqual( (data.totalSum()), numpy.sum(data.getArray()) )

    #def test_data_axisbin(self):
    #    data = IntensityData()
    #    data.addAxis(AxisDouble("axis0", 11, -5.0, 5.0))
    #    data.addAxis(AxisDouble("axis1", 6, 0.0, 5.))
    #    for i in range(0, data.getAllocatedSize()):
    #        print i, "axis0", data.getIndexOfAxis("axis0",i), data.getValueOfAxis("axis0",i), "axis1", data.getIndexOfAxis("axis1",i), data.getValueOfAxis("axis1",i)

    # def test_getarray_masked(self):
    #     data = IntensityData()
    #     data.addAxis("x", 10, 0., 9.)
    #     data.addAxis("y", 5, 0., 4.)
    #     for i in range(0, data.getAllocatedSize()):
    #         data[i] = i
    #     IntensityDataFunctions.setRectangularMask(data, 1.99, 0.99, 7.01, 3.01)
    #
    #     nparr = data.getArray()
    #     value=0
    #     for ix in range(0, 10):
    #         for iy in range(0, 5):
    #             self.assertEqual(value, nparr[iy][ix])
    #             value = value+1



if __name__ == '__main__':
    unittest.main()

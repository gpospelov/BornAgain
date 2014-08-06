# tests of IO operations with the IntensityData object

import sys
import os
import unittest
import numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


def fill_data(data):
    """
    Fills intensity data with some numbers
    """
    for i in range(0, data.getAllocatedSize()):
        data[i] = i


def is_the_same(data1, data2):
    """
    Checks if two data are identical
    """
    if data1.getAllocatedSize() != data2.getAllocatedSize():
        return False
    if data1.getRank() != data2.getRank():
        return False
    for i in range(0, data1.getRank()):
        if data1.getAxis(i) != data2.getAxis(i):
            return False
    for i in range(0, data1.getAllocatedSize()):
        if data1[i] != data2[i]:
            return False

    return True


class OutputDataIOTest(unittest.TestCase):
    """
    Test serialization of IntensityData
    """
    def test_1D_FixedBinAxis(self):
        data = IntensityData()
        data.addAxis(FixedBinAxis("axis0", 10, -1.00000001, 1.0))
        fill_data(data)
        OutputDataIOFactory.writeIntensityData(data, "tmp.baint")
        newdata = OutputDataIOFactory.readIntensityData("tmp.baint")
        self.assertTrue(is_the_same(data, newdata))

    def test_2D_FixedBinAxis(self):
        data = IntensityData()
        data.addAxis(FixedBinAxis("axis0", 9, -1.00000001, 1.0))
        data.addAxis(FixedBinAxis("axis1", 3, -4.0, 5.0))
        fill_data(data)
        OutputDataIOFactory.writeIntensityData(data, "tmp.baint")
        newdata = OutputDataIOFactory.readIntensityData("tmp.baint")
        self.assertTrue(is_the_same(data, newdata))

    def test_3D_FixedBinAxis(self):
        data = IntensityData()
        data.addAxis(FixedBinAxis("axis0", 9, -1.00000001, 1.0))
        data.addAxis(FixedBinAxis("axis1", 1, -4.0, 5.0))
        data.addAxis(FixedBinAxis("axis2", 3, 0.0, 1.0))
        fill_data(data)
        OutputDataIOFactory.writeIntensityData(data, "tmp.baint")
        newdata = OutputDataIOFactory.readIntensityData("tmp.baint")
        self.assertTrue(is_the_same(data, newdata))


if __name__ == '__main__':
    unittest.main()

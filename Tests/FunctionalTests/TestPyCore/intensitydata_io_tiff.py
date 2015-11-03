# Functional test: tests of IO operations with the IntensityData object

import sys
import os
import unittest
import numpy
import math
import time

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


def is_the_same_data(data1, data2):
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


class OutputDataIOTiffTest(unittest.TestCase):
    """
    Test serialization of IntensityData into TIFF format
    """
    def test_SaveToTiff(self):
        data = IntensityData()
        data.addAxis(FixedBinAxis("x", 10, 0.0, 10.0))
        data.addAxis(FixedBinAxis("y", 5, 0.0, 5.0))
        fill_data(data)

        IntensityDataIOFactory.writeOutputData(data, "tmp.tif")
        newdata = IntensityDataIOFactory.readOutputData("tmp.tif")
        self.assertTrue(is_the_same_data(data, newdata))

        IntensityDataIOFactory.writeOutputData(data, "tmp.tif.gz")
        newdata = IntensityDataIOFactory.readOutputData("tmp.tif.gz")
        self.assertTrue(is_the_same_data(data, newdata))

        IntensityDataIOFactory.writeOutputData(data, "tmp.tif.bz2")
        newdata = IntensityDataIOFactory.readOutputData("tmp.tif.bz2")
        self.assertTrue(is_the_same_data(data, newdata))


if __name__ == '__main__':
    unittest.main()

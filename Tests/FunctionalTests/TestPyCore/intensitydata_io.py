# tests of IntensityData object

import sys
import os
import unittest
import numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


def fill_data(data):
    """Fills intensity data with some numbers"""
    for i in range(0, data.getAllocatedSize()):
        data[i] = i


def is_the_same(data1, data2):
    if data1.getAllocatedSize() != data2.getAllocatedSize():
        return False
    if data1.getRank() != data2.getRank():
        return False
    for i in range(0, data1.getRank()):
        if data1.getAxis(i) == data2.getAxis(i):
            print "xxx"
        else:
            print "yyy"

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

if __name__ == '__main__':
    unittest.main()

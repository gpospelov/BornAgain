
import sys
import os
import unittest
import numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


class AxesTest(unittest.TestCase):
    """
    Test creation of IntensityData object and different ways of accessing its data
    """
    def test_FixedBinAxis_access(self):
        axis = FixedBinAxis("length", 100, 0.0, 10.0)
        self.assertEqual("length", axis.getName())
        self.assertEqual(100, axis.getSize())
        self.assertEqual(0.0, axis.getMin())
        self.assertEqual(10.0, axis.getMax())
        self.assertAlmostEqual(0.05, axis[0])
        self.assertAlmostEqual(0.15, axis[1])
        self.assertAlmostEqual(6.55, axis[65])
        self.assertAlmostEqual(9.95, axis[99])

    def test_FixedBinAxis_equality(self):
        b1 = FixedBinAxis("axis", 99, -1.01, 3.3)
        b2 = FixedBinAxis("axis", 99, -1.01, 3.3)

        self.assertTrue( b1 == b2)


if __name__ == '__main__':
    unittest.main()

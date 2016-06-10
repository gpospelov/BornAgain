
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
        b3 = FixedBinAxis("axissss", 99, -1.01, 3.3)
        b4 = FixedBinAxis("axis", 99, -1.0, 3.3)
        b5 = FixedBinAxis("axis", 99, -1.01, 3.29)
        b6 = FixedBinAxis("axiss", 98, -1.01, 3.3)
        self.assertFalse( b1 == b3)
        self.assertFalse( b1 == b4)
        self.assertFalse( b1 == b5)
        self.assertFalse( b1 == b6)

    def test_FixedBinAxis_boundaries(self):
        axis = FixedBinAxis("name", 3, -1.5, 1.5)
        centers = axis.getBinCenters()
        self.assertEqual(3, len(centers))
        self.assertAlmostEqual(-1.0, centers[0])
        self.assertAlmostEqual(0.0, centers[1])
        self.assertAlmostEqual(1.0, centers[2])
        boundaries = axis.getBinBoundaries()
        self.assertEqual(4, len(boundaries))
        self.assertAlmostEqual(-1.5, boundaries[0])
        self.assertAlmostEqual(-0.5, boundaries[1])
        self.assertAlmostEqual(0.5, boundaries[2])
        self.assertAlmostEqual(1.5, boundaries[3])

    def test_VariableBinAxis_access(self):
        values = [-1.5, -0.5, 0.5, 1.5]
        axis = VariableBinAxis("name", 3, values)
        self.assertEqual("name", axis.getName())
        self.assertEqual(3, axis.getSize())
        self.assertAlmostEqual(-1.0, axis[0])
        self.assertAlmostEqual(0.0, axis[1])
        self.assertAlmostEqual(1.0, axis[2])

    def test_VariableBinAxis_equality(self):
        values1 = [-1.0, -0.5, 0.5, 1.0, 2.0]
        a1 = VariableBinAxis("name", 4, values1)
        a2 = VariableBinAxis("name", 4, values1)
        a3 = VariableBinAxis("nameX", 4, values1)
        self.assertTrue( a1 == a2)
        self.assertFalse( a1 == a3)
        values2 = [-1.0, -0.5, 0.5, 1.1, 2.0]
        a4 = VariableBinAxis("nameX", 4, values2)
        self.assertFalse(a1 == a4)

    def test_VariableBinAxis_boundaries(self):
        values = [-1.0, -0.5, 0.5, 1.0, 2.0]
        axis = VariableBinAxis("name", 4, values)
        centers = axis.getBinCenters()
        self.assertEqual(4, len(centers))
        self.assertAlmostEqual(-0.75, centers[0])
        self.assertAlmostEqual(0.0, centers[1])
        self.assertAlmostEqual(0.75, centers[2])
        self.assertAlmostEqual(1.5, centers[3])
        boundaries = axis.getBinBoundaries()
        self.assertEqual(5, len(boundaries))
        self.assertAlmostEqual(-1.0, boundaries[0])
        self.assertAlmostEqual(-0.5, boundaries[1])
        self.assertAlmostEqual(0.5, boundaries[2])
        self.assertAlmostEqual(1.0, boundaries[3])
        self.assertAlmostEqual(2.0, boundaries[4])



if __name__ == '__main__':
    unittest.main()

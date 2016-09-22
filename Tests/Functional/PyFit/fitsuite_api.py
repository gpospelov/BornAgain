"""
Testing of python specific FitSuite API.
"""
import sys
import os
import unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba

class FitSuiteAPITest(unittest.TestCase):

    def test_FitParameterSetIterator(self):
        """
        Testing of python iterator over defined fit parameters.
        """
        fitSuite = ba.FitSuite()
        names = ["par1", "par2", "par3"]
        values = [1.0, 2.0, 3.0]
        for name, value in zip(names, values):
            fitSuite.addFitParameter(name, value)

        nn = 0
        for par in fitSuite.fitParameters():
            self.assertTrue(par.name() == names[nn])
            self.assertTrue(par.value() == values[nn])
            nn = nn+1

        self.assertTrue(nn == 3)

    def test_addFitParameter(self):
        fitSuite = ba.FitSuite()
        fitSuite.addFitParameter("par1", 1.0)
        fitSuite.addFitParameter("par2", 2.0, ba.AttLimits.limited(10.0, 20.0), 0.02)
        fitSuite.addFitParameter("par3", 3.0).setLowerLimited(30.0).setStep(0.03)
        fitSuite.addFitParameter("par4", 4.0).setStep(0.04).setUpperLimited(40.0)
        fitSuite.addFitParameter("par5", 5.0).setFixed()

        par = fitSuite.fitParameters()[0]
        self.assertEqual(par.name(), "par1")
        self.assertEqual(par.value(), 1.0)
        self.assertEqual(par.step(), 0.01)  # default step is 1% in FitSuite
        self.assertTrue(par.limits().isLimitless())

        par = fitSuite.fitParameters()[1]
        self.assertEqual(par.name(), "par2")
        self.assertEqual(par.value(), 2.0)
        self.assertEqual(par.step(), 0.02)
        self.assertTrue(par.limits().isLimited())
        self.assertEqual(par.limits().lowerLimit(), 10.0)
        self.assertEqual(par.limits().upperLimit(), 20.0)

        par = fitSuite.fitParameters()[2]
        self.assertEqual(par.name(), "par3")
        self.assertEqual(par.value(), 3.0)
        self.assertEqual(par.step(), 0.03)
        self.assertTrue(par.limits().isLowerLimited())
        self.assertEqual(par.limits().lowerLimit(), 30.0)

        par = fitSuite.fitParameters()[3]
        self.assertEqual(par.name(), "par4")
        self.assertEqual(par.value(), 4.0)
        self.assertEqual(par.step(), 0.04)
        self.assertTrue(par.limits().isUpperLimited())
        self.assertEqual(par.limits().upperLimit(), 40.0)

        par = fitSuite.fitParameters()[4]
        self.assertEqual(par.name(), "par5")
        self.assertEqual(par.value(), 5.0)
        self.assertTrue(par.limits().isFixed())

if __name__ == '__main__':
    unittest.main()

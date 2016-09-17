"""
Testing of python specific FitSuite API.
"""
import sys
import os
import unittest
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
            self.assertTrue(par.getName() == names[nn])
            self.assertTrue(par.getValue() == values[nn])
            nn = nn+1

        self.assertTrue(nn == 3)

if __name__ == '__main__':
    unittest.main()

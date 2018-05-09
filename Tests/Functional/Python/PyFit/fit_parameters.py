"""
Testing python specific FitSuite API.
"""
import sys
import os
import unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba


def some_callable(pars):
    print("here", pars)
    return 42.0


class FitParametersAPITest(unittest.TestCase):

    def test_ParametersSetIterator(self):
        """
        Testing of python iterator over defined fit parameters.
        """

        pars = ba.Parameters()
        self.assertEqual(pars.size(), 0)

        pars.add(ba.Parameter("par0", 1.0, ba.AttLimits.limitless()))
        pars.add(ba.Parameter("par1", 2.0, ba.AttLimits.limitless()))
        expected_names = ["par0", "par1"]
        for index, p in enumerate(pars):
            self.assertEqual(p.name(), expected_names[index])

    def test_Callback(self):
        minimizer = ba.Minimizer()
        minimizer.test_callback(some_callable)



if __name__ == '__main__':
    unittest.main()

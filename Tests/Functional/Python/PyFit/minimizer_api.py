"""
Testing python specific API for Minimizer related classes.
"""
import sys
import os
import unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba


class TestMinimizerHelper:
    def __init__(self):
        self.m_ncalls = 0
        self.m_pars = None

    def objective_function(self, pars):
        self.m_ncalls += 1
        self.m_pars = pars
        return 42.0


class MinimizerAPITest(unittest.TestCase):

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

    def test_SimpleMinimizer(self):
        minimizer = ba.Minimizer()
        minimizer.setMinimizer("Test")

        pars = ba.Parameters()
        pars.add(ba.Parameter("par0", 0.0))
        pars.add(ba.Parameter("par1", 1.0))
        pars.add(ba.Parameter("par2", 2.0))

        helper = TestMinimizerHelper()
        result = minimizer.minimize(helper.objective_function, pars)

        # return value of objective function was propagated to MinimizerResult
        self.assertEqual(result.minValue(), 42.0)

        # objective function was called once
        self.assertEqual(helper.m_ncalls, 1)

        # starting values of fit parameters were correctly send to objective func
        self.assertEqual(list(helper.m_pars.values()), [0.0, 1.0, 2.0])

if __name__ == '__main__':
    unittest.main()

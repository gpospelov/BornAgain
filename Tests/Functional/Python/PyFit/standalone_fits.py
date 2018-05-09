"""
Fitting scalar and residual based objective functions
"""
import sys
import os
import unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba
import numpy as np


class Rosenbrock:
    def __init__(self):
        self.m_expected_minimum = 0.0
        self.m_expected_params = [1.0, 1.0]
        pass

    def objective_function(self, params):
        """
        Returns the value of Rosenbrock function
        """
        x = params["x"].value()
        y = params["y"].value()
        tmp1 = y - x * x
        tmp2 = 1 - x
        return 100 * tmp1 * tmp1 + tmp2 * tmp2


class StandaloneFitTest(unittest.TestCase):

    def test_RosenbrockFit(self):
        """
        Testing fit of rosenbrock function
        """
        pars = ba.Parameters()
        pars.add(ba.Parameter("x", -1.2, ba.AttLimits.limited(-5.0, 5.0), 0.01))
        pars.add(ba.Parameter("y", 1.0, ba.AttLimits.limited(-5.0, 5.0), 0.01))

        rosenbrock = Rosenbrock()
        minimizer = ba.Minimizer()
        result = minimizer.minimize(rosenbrock.objective_function, pars)

        print(result.toString())

        # check found parameter values
        np.testing.assert_almost_equal(result.parameters().values(),
                                       rosenbrock.m_expected_params, 3)

        # check found minimum
        np.testing.assert_almost_equal(result.minValue(),
                                       rosenbrock.m_expected_minimum, 3)




if __name__ == '__main__':
    unittest.main()

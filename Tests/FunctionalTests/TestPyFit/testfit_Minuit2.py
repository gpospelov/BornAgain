import sys
import os
import fitting_utils
import unittest

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *
from libBornAgainFit import *


class MinimizersTest_Minuit2(unittest.TestCase):

    def test_minuit2_migrad(self):
        fitpars, refpars = fitting_utils.run_fit_suite("Minuit2", "Migrad")
        for i in range(0, len(fitpars)):
            self.assertAlmostEqual(fitpars[i], refpars[i], delta=1e-3)

    def test_minuit2_fumili(self):
        fitpars, refpars = fitting_utils.run_fit_suite("Minuit2", "Fumili")
        for i in range(0, len(fitpars)):
            self.assertAlmostEqual(fitpars[i], refpars[i], delta=1e-3)


if __name__ == '__main__':
    unittest.main()

import sys
import os
import fitting_utils
import unittest

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *
from libBornAgainFit import *


class MinimizersTest_GSLSimAn(unittest.TestCase):

    def test_GSLSimAn(self):
        fitpars, refpars = fitting_utils.run_fit_suite("GSLSimAn")
        for i in range(0, len(fitpars)):
            self.assertAlmostEqual(fitpars[i], refpars[i], delta=0.2)


if __name__ == '__main__':
    unittest.main()

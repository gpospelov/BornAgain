import sys
import os
import fitting_utils
import unittest

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *
from libBornAgainFit import *



class MinimizersTest_Genetic(unittest.TestCase):

    def test_Genetic(self):
        fit_suite = fitting_utils.get_fit_suite("Genetic","")
        fit_suite.getMinimizer().getOptions().setMaxIterations(5)

        fit_suite.initPrint(100 )
        fit_suite.runFit()
        fitting_utils.print_fit_results(fit_suite)

        fitpars = fit_suite.getFitParameters().getValues()
        refpars = fitting_utils.getReferenceParameters()

        for i in range(0, len(fitpars)):
            self.assertAlmostEqual(fitpars[i], refpars[i], delta=0.1)


if __name__ == '__main__':
    unittest.main()
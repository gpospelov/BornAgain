import unittest
import numpy as np
import sys

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba

from bornagain import deg


class FitObjectTest(unittest.TestCase):

    def test_constructFromOutputData(self):
        """
        Check construction from OutputData
        """
        nx, ny = 4, 3
        xmin, xmax = -1.0*deg, 3.0*deg
        ymin, ymax = 0.0*deg, 3.0*deg

        # preparing simulation and OutputData
        simulation = ba.GISASSimulation()
        simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax)

        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("phi", nx, xmin, xmax))
        data.addAxis(ba.FixedBinAxis("alpha", ny, ymin, ymax))
        buff = np.linspace(0, 12, num=12, endpoint=False, dtype=np.float64)
        data.setRawDataVector(buff)

        # constructing FitObject
        fit_object = ba.FitObject(simulation, data)

        # accessing experimental data as flat array
        self.assertEqual(list(fit_object.experimental_array()), buff.tolist())

        # accessing experimental data via SimulationResult mechanism
        expected = np.array([[2.0,  5.0,  8.0, 11.0],
                             [1.0,  4.0,  7.0, 10.0],
                             [0.0,  3.0,  6.0,  9.0]], dtype=np.float64)

        for (x, y), element in np.ndenumerate(expected):
            self.assertEqual(element, fit_object.experimentalData().array()[x][y])


    def test_constructFromNumpyDouble(self):
        """
        Check construction from OutputData
        """
        nx, ny = 4, 3
        xmin, xmax = -1.0*deg, 3.0*deg
        ymin, ymax = 0.0*deg, 3.0*deg

        # preparing simulation and experimental data as numpy array

        simulation = ba.GISASSimulation()
        simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax)

        exp_data = np.array([[0,  1,  2,  3],
                             [4,  5,  6,  7],
                             [8,  9, 10, 11]], np.float64)

        # constructing FitObject
        fit_object = ba.FitObject(simulation, exp_data)

        # accessing experimental data as flat array
        expected = [8.0, 4.0,  0.0, 9.0, 5.0, 1.0, 10.0, 6.0, 2.0, 11.0, 7.0, 3.0]
        self.assertEqual(list(fit_object.experimental_array()), expected)

        # accessing experimental data via SimulationResult mechanism
        for (x, y), element in np.ndenumerate(exp_data):
            self.assertEqual(element, fit_object.experimentalData().array()[x][y])


if __name__ == '__main__':
    unittest.main()

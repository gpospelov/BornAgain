"""
Turns a Python example into a functional persistence test via CMake machinery.
"""

import bornagain as ba
from bornagain import deg, angstrom, nm
import sys
import os

example_dir = "@EXAMPLE_DIR@"
example_name = "@EXAMPLE_NAME@"
output_dir = "@OUTPUT_DIR@"

sys.path.append(example_dir)
example = __import__(example_name)


def test_simulation():
    """
    Returns a GISAXS simulation.
    """
    simulation = ba.GISASSimulation()
    simulation.setSample(example.get_sample())
    simulation.setDetectorParameters(5, -1*deg, +1*deg, 6, 0*deg, +2*deg)
    simulation.setBeamParameters(1.5*angstrom, 0.15*deg, 0.0*deg)
    return simulation


if __name__ == '__main__':
    simulation = test_simulation()
    simulation.runSimulation()
    result = simulation.getIntensityData()

    filename = os.path.join(output_dir, example_name+".ref.int.gz")
    print("example_template.py -> Writing results in '{0}'".format(filename))
    ba.IntensityDataIOFactory.writeIntensityData(result, filename)

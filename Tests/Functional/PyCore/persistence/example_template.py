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


def get_default_simulation():
    """
    Returns a GISAXS simulation.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(5, -1*deg, +1*deg, 6, 0*deg, +2*deg)
    simulation.setBeamParameters(1.5*angstrom, 0.15*deg, 0.0*deg)
    return simulation


def get_minified_simulation():
    """
    Returns a GISAXS simulation constructed from example simulation with smaller detector
    """
    simulation = example.get_simulation()
    detector = simulation.getInstrument().getDetector()

    # preserving axes range, making less bins
    ax = detector.getAxis(0)
    ay = detector.getAxis(1)
    xmin, xmax = ax.getMin(), ax.getMax()
    ymin, ymax = ay.getMin(), ay.getMax()

    simulation.setDetectorParameters(5, xmin, xmax, 6, ymin, ymax)
    return simulation


def get_simulation():

    if "CustomFormFactor" in example_name:
        return get_minified_simulation()
    else:
        return get_default_simulation()


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(example.get_sample())
    simulation.runSimulation()
    return simulation.getIntensityData()


if __name__ == '__main__':
    result = run_simulation()

    filename = os.path.join(output_dir, example_name+".ref.int.gz")
    print("example_template.py -> Writing results in '{0}'".format(filename))
    ba.IntensityDataIOFactory.writeIntensityData(result, filename)

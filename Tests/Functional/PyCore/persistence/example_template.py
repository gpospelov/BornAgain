"""
Turns a Python example into a functional persistence test via CMake machinery.
"""

import sys
import os

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba

example_dir = "@EXAMPLE_DIR@"
example_name = "@EXAMPLE_NAME@"
output_dir = "@OUTPUT_DIR@"

sys.path.append(example_dir)
example = __import__(example_name)

simulationObject = None


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
    """
    Returns minified simulation to be used in example
    """
    global simulationObject
    return simulationObject


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """
    global simulationObject
    simulationObject = get_minified_simulation()
    # replacing get_simulation() method of example with templated
    example.get_simulation = get_simulation
    return example.run_simulation()


if __name__ == '__main__':
    result = run_simulation()

    filename = os.path.join(output_dir, example_name+".ref.int.gz")
    print("example_template.py -> Writing results in '{0}'".format(filename))
    ba.IntensityDataIOFactory.writeIntensityData(result, filename)

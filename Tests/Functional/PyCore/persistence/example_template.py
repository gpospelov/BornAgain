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

    # temporary hack for SpecularSimulation
    if "SpecularSimulation" == example_name:
        return simulation

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

    # create minified simulation object
    global simulationObject
    simulationObject = get_minified_simulation()

    # replacing get_simulation() method of example with local method
    example.get_simulation = get_simulation
    return example.run_simulation()


def save(data, filename):

    if "SpecularSimulation" == example_name:
        filename += ".ref"
        R, T = example.coefficientsRT(data)
        ba.yamlDump(filename, { "coeff_R": ba.FlowSeq(R[0]), "coeff_T": ba.FlowSeq(T[0])})
    else:
        filename += ".ref.int.gz"
        ba.IntensityDataIOFactory.writeIntensityData(data, filename)

    print("example_template.py -> Writing results in '{0}'".format(filename))


if __name__ == '__main__':
    results = run_simulation()

    if type(results) is dict:
        for name, subresult in results.items():
            filename = os.path.join(output_dir, example_name+"."+str(name))
            save(subresult, filename)
    else:
        filename = os.path.join(output_dir, example_name)
        save(results, filename)




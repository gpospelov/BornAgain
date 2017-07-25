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


def get_simulation_SpecularSimulation():
    """
    Returns custom simulation for SpecularSimulation.py.
    Minification is not yet implemented.
    """
    return example.get_simulation()


def get_simulation_RectangularGrating():
    """
    Returns custom simulation for RectangularGrating.py.
    Contains smaller detector to make MC integration happy on all platforms
    """
    simulation = example.get_simulation()
    simulation.setDetectorParameters(5, -0.01*ba.deg, 0.01*ba.deg, 6, 0.0, 0.02*ba.deg)
    return simulation


def get_simulation_GenericExample():
    """
    Returns minified simulation for majority of examples. Detector size is adjusted.
    The idea is that all other example's setting related to the simulation (MC integration flags,
    threads settings etc) remains intact.
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


def get_minified_simulation():
    """
    Returns a GISAXS simulation constructed from example simulation with smaller detector.
    """
    if example_name == "SpecularSimulation":
        return get_simulation_SpecularSimulation()

    elif example_name == "RectangularGrating":
        return get_simulation_RectangularGrating()

    else:
        return get_simulation_GenericExample();


def adjusted_simulation():
    """
    Returns pre-calculated minified simulation. Function is intended for
    injection into python example file.
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

    # INJECTION HERE: replacing get_simulation() method of example with local method
    example.get_simulation = adjusted_simulation
    return example.run_simulation()


def save(data, filename):

    if "SpecularSimulation" == example_name:
        filename += ".ref"
        R, T = example.rt_coefficients(data)
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




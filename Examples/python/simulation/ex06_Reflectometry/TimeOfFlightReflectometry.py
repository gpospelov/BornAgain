"""
An example of defining reflectometry instrument
for time of flight experiment. In this example
two approaches are used: first, we define
beam parameters through a range of wavelengths and
an incident angle; second, we will use purely
qz-defined beam, without explicitly specifying
incident angle or a wavelength.
Note that these approaches work with SLD-based
materials only.
"""
import numpy as np
import bornagain as ba
from matplotlib import pyplot as plt
from bornagain import deg, angstrom

inc_angle = 2.0 * deg  # inclination angle
qzs = np.linspace(0.01, 1.0, 500, dtype=float)  # qz-values

# factor to convert qz values to wavelengths
norm_factor = 4.0 * np.pi * np.sin(inc_angle)
wls = np.asarray([norm_factor / qz for qz in qzs])  # wavelength values


def get_sample():
    """
    Defines sample and returns it. Note that SLD-based materials are used.
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0.0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0.0)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30 * angstrom)
    ni_layer = ba.Layer(m_ni, 70 * angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    for i in range(10):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation_q():
    """
    Defines and returns specular simulation
    with a qz-defined beam
    """
    simulation = ba.SpecularSimulation()
    simulation.setBeamParameters(qzs)
    return simulation


def get_simulation_wl():
    """
    Defines and returns specular simulation
    with a time-of-flight beam
    """
    simulation = ba.SpecularSimulation()
    simulation.setBeamParameters(wls, inc_angle)
    return simulation


def run_simulation(simulation):
    """
    Runs simulation and returns its result.
    """
    sample = get_sample()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


def plot(result_wl, result_qz):
    """
    Plots data for several selected layers
    """

    ba.plot_simulation_result(result_qz, postpone_show=True)

    plt.semilogy(result_wl.axis(), result_wl.array(), 'ko', markevery=10)
    plt.legend([r'$q_z$-defined beam',
                r'$\lambda$-defined beam'],
               loc='upper right')

    plt.show()


if __name__ == '__main__':
    result_tof = run_simulation(get_simulation_wl())
    result_q = run_simulation(get_simulation_q())
    plot(result_tof, result_q)

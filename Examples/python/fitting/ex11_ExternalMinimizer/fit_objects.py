"""
Prototype of new FitObject
"""
import bornagain as ba
import numpy as np


class FitObject:
    def __init__(self):
        self.m_simulation_builder = None
        self.m_experimental_data = None
        self.m_fit_object = None
        pass

    def set_data(self, simulation_builder, real_data):
        self.m_simulation_builder = simulation_builder
        self.m_experimental_data = real_data

    def evaluate(self, params):
        simulation = self.m_simulation_builder.build_simulation(params)

        self.m_fit_object = ba.FitObject(simulation, self.m_experimental_data)
        self.m_fit_object.runSimulation()

        result = np.asarray(self.m_fit_object.simulation_array())
        exp = np.asarray(self.m_fit_object.experimental_array())

        res = result-exp
        return res

    def simulationResult(self):
        return self.m_fit_object.simulationResult()

    def experimentalData(self):
        return self.m_fit_object.experimentalData()

    def relativeDifference(self):
        return self.m_fit_object.relativeDifference()
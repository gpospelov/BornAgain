"""
BornAgain functional test.
Test of rotation/translation of particle composition made of truncated spheres.
"""
import unittest
import utils
from bornagain import *

layer_thickness = 100
comp_length = 50
comp_width = 20
comp_height = 10
particle_material = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

class TransformBoxCompositionTest(unittest.TestCase):

    def get_sample(self, particle):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        mMiddle= HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9)
        mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)

        layout = ParticleLayout()
        layout.addParticle(particle)

        air_layer = Layer(mAmbience)
        middle_layer = Layer(mMiddle, layer_thickness)
        # air_layer.addLayout(layout)
        middle_layer.addLayout(layout)
        substrate = Layer(mSubstrate)

        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(middle_layer)
        multi_layer.addLayer(substrate)
        return multi_layer

    def get_intensity_data(self, particle):
        sample = self.get_sample(particle)
        simulation = utils.get_simulation_MiniGISAS(sample)
        simulation.runSimulation()
        return simulation.getIntensityData()

    def test_BoxComposition(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size
        """
        # reference box
        length = 50
        width = 20
        height = 10
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0, 0, -layer_thickness/2 - height/2))

        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxComposition.int")

        # composition
        box = Particle(particle_material, FormFactorBox(comp_length/2, comp_width, comp_height))
        composition = ParticleComposition()
        # composition = ParticleComposition(box, positions)
        composition.addParticle(box, kvector_t(0, 0, 0))
        composition.addParticle(box, kvector_t(comp_length/2, 0, 0))
        composition.setPosition(kvector_t(0, 0, -layer_thickness/2 - comp_height/2))

        data = self.get_intensity_data(composition)

        diff = IntensityDataFunctions.getRelativeDifference(data, reference_data)
        print "test_BoxComposition:", diff
        self.assertLess(diff, 1e-10)
        # utils.plot_intensity_data(reference_data)

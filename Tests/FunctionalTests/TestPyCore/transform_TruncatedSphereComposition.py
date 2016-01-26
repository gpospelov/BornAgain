"""
BornAgain functional test.
Test of rotation/translation of particle composition made of truncated spheres.
"""
import unittest
import utils
import sys
import os

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))


from libBornAgainCore import *

layer_thickness = 100.0
sphere_radius = 10.0
particle_material = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

class TransformTruncatedSphereCompositionTest(unittest.TestCase):

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
        simulation = utils.get_simulation_BasicGISAS(sample)
        simulation.runSimulation()
        return simulation.getIntensityData()

    def test_TruncatedSphere(self):
        """
        Full sphere is compared against truncated sphere (height=2*radius)
        """
        # reference sphere
        particle = Particle(particle_material, FormFactorFullSphere(sphere_radius))
        particle.setPosition(kvector_t(0, 0, -layer_thickness/2.0 - sphere_radius))

        reference_data = self.get_intensity_data(particle)

        # composition
        sphere = Particle(particle_material, FormFactorTruncatedSphere(sphere_radius, 2.*sphere_radius))
        sphere.setPosition(kvector_t(0, 0, -layer_thickness/2.0 - sphere_radius))

        data = self.get_intensity_data(sphere)
        # data -= reference_data
        # print data.getArray()
        # utils.plot_intensity_data(data)

        diff = IntensityDataFunctions.getRelativeDifference(data, reference_data)
        print "test_TruncatedSphere:", diff
        self.assertLess(diff, 1e-10)
        # utils.plot_intensity_data(reference_data)


    # def test_TruncatedSphereComposition(self):
    #     """
    #     Two half spheres (one 180.0 Y-rotated) are composed into full sphere.Composition is compared against full sphere
    #     """
    #     # reference sphere
    #     particle = Particle(particle_material, FormFactorFullSphere(sphere_radius))
    #     particle.setPosition(kvector_t(0, 0, -layer_thickness/2.0 - sphere_radius))
    #
    #     reference_data = self.get_intensity_data(particle)
    #     #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxComposition.int")
    #
    #     # composition
    #     half1 = Particle(particle_material, FormFactorTruncatedSphere(sphere_radius, sphere_radius))
    #     half2 = Particle(particle_material, FormFactorTruncatedSphere(sphere_radius, sphere_radius))
    #     half2.setRotation(RotationY(180.0*degree))
    #
    #     composition = ParticleComposition()
    #     composition.addParticle(half1, kvector_t(0, 0, 0))
    #     composition.addParticle(half2, kvector_t(0, 0, 0))
    #     composition.setPosition(kvector_t(0, 0, -layer_thickness/2.0))
    #
    #     data = self.get_intensity_data(composition)
    #
    #     data -= reference_data
    #     utils.plot_intensity_data(data)
    #
    #     diff = IntensityDataFunctions.getRelativeDifference(data, reference_data)
    #     print "test_TruncatedSphereComposition:", diff
    #     self.assertLess(diff, 1e-10)
    #     # utils.plot_intensity_data(reference_data)


if __name__ == '__main__':
    unittest.main()

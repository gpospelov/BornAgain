"""
Test of rotation/position of particle composition

"""
import unittest
import utils
from bornagain import *

class ParticleCompositionTransformationsTest(unittest.TestCase):

    def get_sample(self, particle):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        mMiddle= HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9)
        mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)

        layout = ParticleLayout()
        layout.addParticle(particle)

        air_layer = Layer(mAmbience)
        middle_layer = Layer(mMiddle, 100.0)
        air_layer.addLayout(layout)
        # middle_layer.addLayout(layout)
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

    def testSameMaterialComposition(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size
        """
        mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

        particle = Particle(mCore, FormFactorBox(50, 20, 10))
        particle.setPosition(kvector_t(0, 0, 10))

        reference_data = self.get_intensity_data(particle)

        box = Particle(mCore, FormFactorBox(25, 20, 10))
        positions = [kvector_t(0, 0, 0), kvector_t(25, 0, 0)]

        composition = ParticleComposition()
        # composition = ParticleComposition(box, positions)
        composition.addParticle(box, kvector_t(0,0,0))
        composition.addParticle(box, kvector_t(25,0,0))
        composition.setPosition(kvector_t(0, 0, 10))

        data = self.get_intensity_data(composition)

        diff = IntensityDataFunctions.getRelativeDifference(data, reference_data)
        print diff
#        self.assertLess(diff, 1e-10)
        utils.plot_intensity_data(reference_data)



    # def testCoreShellTransform(self):
    #     mCore = HomogeneousMaterial("Core", 1e-4, 2e-8)
    #     mShell = HomogeneousMaterial("Shell", 5e-4, 2e-8)
    #
    #     core_ref = Particle(mCore, FormFactorBox(10, 50, 20))
    #     shell_ref = Particle(mShell, FormFactorBox(5, 25, 10))
    #     coreshell_ref = ParticleCoreShell(core_ref, shell_ref, kvector_t(0, 0, 5.0))
    #     coreshell_ref.setPosition(kvector_t(0, 0, -60))  # center of coreshell in center of the layer
    #
    #     reference_data = self.get_intensity_data(coreshell_ref)
    #
    #     core = Particle(mCore, FormFactorBox(50, 20, 10))
    #     shell = Particle(mShell, FormFactorBox(25, 10, 5))
    #     coreshell = ParticleCoreShell(core, shell, kvector_t(0, 0, 2.5))
    #     coreshell.setRotation(RotationZ(90.*degree))
    #     coreshell.applyRotation(RotationY(90.*degree))
    #     coreshell.setPosition(kvector_t(0, 0, -50))
    #
    #     data = self.get_intensity_data(coreshell)
    #
    #     diff = IntensityDataFunctions.getRelativeDifference(data, reference_data)
    #     print diff
    #     self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()

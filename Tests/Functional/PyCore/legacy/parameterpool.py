import numpy, os, sys, unittest
import bornagain as ba
from bornagain import nm

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")


class ParameterPoolTest(unittest.TestCase):

    def test_parameterPoolAccess(self):
        """
        Checks values in particle's parameter pool
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Air", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        pool = particle.getParameterPool()
        self.assertEqual(pool.size(), 4)
        self.assertEqual(pool.parameterNames(), ('Abundance', 'PositionX', 'PositionY', 'PositionZ'))

        expected = {'Abundance': 1.0, 'PositionX': 2.0, 'PositionY': 3.0, 'PositionZ': 4.0}
        for par in pool:
            print(par.getValue(), par.getName(), par.getLimits().toString())
            self.assertEqual(par.getValue(), expected[par.getName()])

    def test_parameterPoolModify(self):
        """
        Modification of particle parameters via parameter pool
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Air", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        pool = particle.getParameterPool()
        pool.setParameterValue('Abundance', 10.0)
        pool[1].setValue(20.0)  # PositionX
        pool.getParameter('PositionY').setValue(30.0)

        expected = {'Abundance': 10.0, 'PositionX': 20.0, 'PositionY': 30.0, 'PositionZ': 4.0}

        for par in pool:
            self.assertEqual(par.getValue(), expected[par.getName()])

    def test_parameterTreeAccess(self):
        """
        Checks values in particle's parameter tree. Parameter tree is a pool with parameters of
        particle and its children (in given case, formfactor of cylinder)
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Air", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        # print(particle.parametersToString())
        # print(particle.treeToString())

        pool = particle.createParameterTree()

        expected = {'/Particle/Abundance': 1.0, '/Particle/PositionX': 2.0,
                    '/Particle/PositionY': 3.0, '/Particle/PositionZ': 4.0,
                    '/Particle/Cylinder/Radius': 5.0, '/Particle/Cylinder/Height': 6.0}

        for par in pool:
            self.assertEqual(par.getValue(), expected[par.getName()])

    def test_parameterTreeModify(self):
        """
        Checks values in particle's parameter tree. Parameter tree is a pool with parameters of
        particle and its children (in given case, formfactor of cylinder)
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Air", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        # print(particle.parametersToString())
        # print(particle.treeToString())

        pool = particle.createParameterTree()
        pool.setParameterValue('/Particle/Abundance', 10.0)
        pool[1].setValue(20.0)  # PositionX
        pool.getParameter('/Particle/PositionY').setValue(30.0)
        pool.setMatchedParametersValue('*Cylinder*', 50.0)

        expected = {'/Particle/Abundance': 10.0, '/Particle/PositionX': 20.0,
                    '/Particle/PositionY': 30.0, '/Particle/PositionZ': 4.0,
                    '/Particle/Cylinder/Radius': 50.0, '/Particle/Cylinder/Height': 50.0}

        for par in pool:
            self.assertEqual(par.getValue(), expected[par.getName()])


if __name__ == '__main__':
    unittest.main()

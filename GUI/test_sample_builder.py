#
# extending C++ ISampleBuilder class in python
#
# The idea is following. We derive python's MySampleBuilder class from C++ ISampleBuilder.
# MySampleBuilder has set of registered parameters and redefined method 'buildSample' which
# build and return some complicated sample
#
# MySampleBuilder is passed to the GISASFWExperiment instance (i.e. inside C++) and then experiment (C++) can
# call MySampleBuilder (python) for new sample.
import sys, os

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


#-----------------------------------------------------------
# Cylinders with interference
# Function constructs sample depending on three parameters
#-----------------------------------------------------------
def BuildSample(m_layer_thickness, m_cylinder_height, m_cylinder_radius):
    n_particle = complex(1.0-5e-5, 2e-8)
    p_air_material = MaterialManager.instance().addHomogeneousMaterial("Air", 1.0, 0.0)
    p_layer_material = MaterialManager.instance().addHomogeneousMaterial("Layer", 1.0-2e-6, 2e-8)
    p_substrate_material = MaterialManager.instance().addHomogeneousMaterial("Substrate", 1.0-2e-6, 2e-8)

    air_layer = Layer(p_air_material)
    middle_layer = Layer(p_layer_material, m_layer_thickness)
    substrate_layer = Layer(p_substrate_material)

    interference_funtion = InterferenceFunctionRadialParaCrystal(20.0*nanometer, 7*nanometer, 1e7*nanometer)
    ff_cylinder = FormFactorCylinder(m_cylinder_radius, m_cylinder_height)
    nano_particle = Particle(n_particle, ff_cylinder )
    particle_collection = ParticleDecoration()
    particle_collection.addParticle(nano_particle)
    particle_collection.addInterferenceFunction(interference_funtion)
    layer_with_particles = LayerDecorator(air_layer, particle_collection)

    p_multi_layer = MultiLayer()
    p_multi_layer.addLayer(layer_with_particles)
    p_multi_layer.addLayer(middle_layer)
    p_multi_layer.addLayer(substrate_layer)
    return p_multi_layer


# ---------------------------------------------------------------
# defining SampleBuilder class which will build samples for us
# 
# ---------------------------------------------------------------
class PythonSampleBuilder(ISampleBuilder):
    def __init__(self):
        ISampleBuilder.__init__(self)
        print "MySampleBuilder ctor"
        self.sample = ISample() # this should be the  class variable to increment reference counter and hold object created in buildSample while C++ processes it


    def buildSample(self):
        self.sample = BuildSample(10, 5, 5)
        return self.sample





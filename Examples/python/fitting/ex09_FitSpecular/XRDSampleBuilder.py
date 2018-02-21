import bornagain as ba
import ctypes


class SiAgNPSampleBuilder(ba.IMultiLayerBuilder):
    """
    Builder for constructing a three layer sample:

    * Silicon substrate
    * A layer of SiO2
    * Ag nano-particles

    Roughness of all layers is assumed to be the same.
    The Builder allows to fit 5 parameters:

    * Roughness of the layers
    * Thickness of SiO2 layer
    * Density of SiO2
    * Thickness of nano-particles' layer
    * Density of nano-particles

    """
    def __init__(self):
        ba.IMultiLayerBuilder.__init__(self)
        self.sample = None

        self.roughness = ctypes.c_double(0.1 * ba.nm)
        self.oxide_thickness = ctypes.c_double(1 * ba.nm)
        self.oxide_concentration = ctypes.c_double(1.0)
        self.np_thickness = ctypes.c_double(1 * ba.nm)
        self.np_concentration = ctypes.c_double(1.0)

        self.registerParameter("roughness", ctypes.addressof(self.roughness))
        self.registerParameter("oxide_thickness",
                               ctypes.addressof(self.oxide_thickness))
        self.registerParameter("oxide_concentration",
                               ctypes.addressof(self.oxide_concentration))
        self.registerParameter("np_thickness", ctypes.addressof(self.np_thickness))
        self.registerParameter("np_concentration",
                               ctypes.addressof(self.np_concentration))

    # constructs the sample for current values of parameters
    def buildSample(self):
        # defining materials
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_np = ba.HomogeneousMaterial("Ag_np",
                                      2.93856228e-05 * self.np_concentration.value,
                                      2.65567132e-06 * self.np_concentration.value)
        m_si_o2 = ba.HomogeneousMaterial("SiO2",
            8.57040868e-06 * self.oxide_concentration.value,
            1.11016654e-07 * self.oxide_concentration.value)
        m_si = ba.HomogeneousMaterial("Si", 7.57211137e-06, 1.72728178e-07)

        # roughness
        r_si = ba.LayerRoughness(self.roughness.value, 0, 0)

        # layers
        air_layer = ba.Layer(m_air)
        np_layer = ba.Layer(m_np, self.np_thickness.value)
        oxide_layer = ba.Layer(m_si_o2, self.oxide_thickness.value)
        substrate_layer = ba.Layer(m_si)

        # assembling multilayer
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayerWithTopRoughness(np_layer, r_si)
        multi_layer.addLayerWithTopRoughness(oxide_layer, r_si)
        multi_layer.addLayerWithTopRoughness(substrate_layer, r_si)

        return multi_layer

"""
3 layers system (substrate, teflon, air).
Air layer is populated with spheres with some size distribution.
"""
import bornagain as ba
import ctypes


class MySampleBuilder(ba.IMultiLayerBuilder):
    """

    """
    def __init__(self):
        ba.IMultiLayerBuilder.__init__(self)
        self.sample = None

        # parameters describing the sample
        self.radius = ctypes.c_double(5.75*ba.nm)
        self.sigma = ctypes.c_double(0.4)
        self.distance = ctypes.c_double(53.6*ba.nm)
        self.disorder = ctypes.c_double(10.5*ba.nm)
        self.kappa = ctypes.c_double(17.5)
        self.ptfe_thickness = ctypes.c_double(22.1*ba.nm)
        self.hmdso_thickness = ctypes.c_double(18.5*ba.nm)

        # register parameters
        self.registerParameter("radius", ctypes.addressof(self.radius))
        self.registerParameter("sigma", ctypes.addressof(self.sigma))
        self.registerParameter("distance", ctypes.addressof(self.distance))
        self.registerParameter("disorder", ctypes.addressof(self.disorder))
        self.registerParameter("kappa", ctypes.addressof(self.kappa))
        self.registerParameter("tptfe", ctypes.addressof(self.ptfe_thickness))
        self.registerParameter("thmdso", ctypes.addressof(self.hmdso_thickness))

    # constructs the sample for current values of parameters
    def buildSample(self):
        # defining materials
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_Si = ba.HomogeneousMaterial("Si", 5.78164736e-6, 1.02294578e-7)
        m_Ag = ba.HomogeneousMaterial("Ag", 2.24749529E-5, 1.61528396E-6)
        m_PTFE = ba.HomogeneousMaterial("PTFE", 5.20508729E-6, 1.96944292E-8)
        m_HMDSO = ba.HomogeneousMaterial("HMDSO", 2.0888308E-6, 1.32605651E-8)

        # collection of particles with size distribution
        nparticles = 20
        nfwhm = 2.0
        sphere_ff = ba.FormFactorFullSphere(self.radius.value)
        # sphere_ff = ba.FormFactorTruncatedSphere(
        #    self.radius.value, self.radius.value*1.5)

        sphere = ba.Particle(m_Ag, sphere_ff)
        position = ba.kvector_t(0*ba.nm, 0*ba.nm,
                                -1.0*self.hmdso_thickness.value)
        sphere.setPosition(position)
        ln_distr = ba.DistributionLogNormal(self.radius.value, self.sigma.value)
        par_distr = ba.ParameterDistribution(
            "/Particle/FullSphere/Radius", ln_distr, nparticles, nfwhm,
            ba.RealLimits.limited(0.0, self.hmdso_thickness.value/2.0))
        # par_distr = ba.ParameterDistribution(
        #    "/Particle/TruncatedSphere/Radius", ln_distr, nparticles, nfwhm)
        # par_distr.linkParameter("/Particle/TruncatedSphere/Height")
        part_coll = ba.ParticleDistribution(sphere, par_distr)

        # interference function
        interference = ba.InterferenceFunctionRadialParaCrystal(
            self.distance.value, 1e6*ba.nm)
        interference.setKappa(self.kappa.value)
        interference.setDomainSize(20000.0)
        pdf = ba.FTDistribution1DGauss(self.disorder.value)
        interference.setProbabilityDistribution(pdf)

        # assembling particle layout
        particle_layout = ba.ParticleLayout()
        particle_layout.addParticle(part_coll, 1.0)
        particle_layout.setInterferenceFunction(interference)
        particle_layout.setApproximation(ba.ILayout.SSCA)
        particle_layout.setTotalParticleSurfaceDensity(1)

        # roughness
        r_ptfe = ba.LayerRoughness(2.3*ba.nm, 0.3, 5.0*ba.nm)
        r_hmdso = ba.LayerRoughness(1.1*ba.nm, 0.3, 5.0*ba.nm)

        # layers
        air_layer = ba.Layer(m_air)
        hmdso_layer = ba.Layer(m_HMDSO, self.hmdso_thickness.value)
        hmdso_layer.addLayout(particle_layout)
        ptfe_layer = ba.Layer(m_PTFE, self.ptfe_thickness.value)
        substrate_layer = ba.Layer(m_Si)

        # assembling multilayer
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayerWithTopRoughness(hmdso_layer, r_hmdso)
        multi_layer.addLayerWithTopRoughness(ptfe_layer, r_ptfe)
        multi_layer.addLayer(substrate_layer)

        return multi_layer

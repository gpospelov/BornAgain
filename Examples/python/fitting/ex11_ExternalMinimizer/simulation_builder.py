import bornagain as ba
from bornagain import nm, deg, angstrom


class SimulationBuilder:
    def __init__(self):
        self.radius = 5.0*nm
        self.lattice_length = 10.0*nm

    def build_simulation(self, params=None):
        if params:
            self.radius = params["radius"].value
            self.lattice_length = params["length"].value

        print("radius: {:6.3f} length:{:6.3f}".format(
            self.radius, self.lattice_length))

        simulation = ba.GISASSimulation()
        simulation.setDetectorParameters(100, -1.0 * deg, 1.0 * deg,
                                         100, 0.0 * deg, 2.0 * deg)
        simulation.setBeamParameters(1.0 * angstrom, 0.2 * deg, 0.0 * deg)
        simulation.setBeamIntensity(1e+08)
        simulation.setSample(self.build_sample())
        return simulation

    def build_sample(self):
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

        sphere_ff = ba.FormFactorFullSphere(self.radius)
        sphere = ba.Particle(m_particle, sphere_ff)
        particle_layout = ba.ParticleLayout()
        particle_layout.addParticle(sphere)

        interference = ba.InterferenceFunction2DLattice.createHexagonal(
            self.lattice_length)
        pdf = ba.FTDecayFunction2DCauchy(10 * nm, 10 * nm)
        interference.setDecayFunction(pdf)

        particle_layout.setInterferenceFunction(interference)

        air_layer = ba.Layer(m_air)
        air_layer.addLayout(particle_layout)
        substrate_layer = ba.Layer(m_substrate, 0)
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate_layer)
        return multi_layer


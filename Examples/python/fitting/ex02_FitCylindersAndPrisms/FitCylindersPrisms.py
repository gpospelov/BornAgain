"""
Fitting example: 4 parameters fit with simple output
"""
import bornagain as ba
from bornagain import degree, angstrom, nanometer


def get_sample():
    """
    Build the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(1.0*nanometer, 1.0*nanometer)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(1.0*nanometer, 1.0*nanometer)
    prism = ba.Particle(m_particle, prism_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_fitting():
    """
    run fitting
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = IntensityDataIOFactory.readIntensityData('refdata_fitcylinderprisms.int.gz')

    fit_suite = ba.FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*Cylinder/Height", 4.*nanometer, ba.AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*Cylinder/Radius", 6.*nanometer, ba.AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*Prism3/Height", 4.*nanometer, ba.AttLimits.lowerLimited(0.01))
    fit_suite.addFitParameter("*Prism3/Length", 12.*nanometer, ba.AttLimits.lowerLimited(0.01))

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print(fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError())

if __name__ == '__main__':
    run_fitting()

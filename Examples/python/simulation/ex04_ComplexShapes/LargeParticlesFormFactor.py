"""
Large cylinders in DWBA.

This example demonstrates that for large particles (~1000nm) the formfactor
oscillates rapidly within one detector bin and analytical calculations
(performed for the bin center) give completely wrong intensity pattern.
In this case Monte-Carlo integration over detector bin should be used.
"""
import numpy, sys
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0
default_cylinder_radius = 10*nm
default_cylinder_height = 20*nm


def get_sample(cylinder_radius, cylinder_height):
    """
    Returns a sample with cylindrical particles on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(integration_flag):
    """
    Returns a GISAXS simulation with defined beam and detector.
    If integration_flag=True, the simulation will integrate over detector bins.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(
        200, phi_min*deg, phi_max*deg, 200, alpha_min*deg, alpha_max*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.getOptions().setMonteCarloIntegration(integration_flag, 50)

    return simulation


def simulate(condi):
    """
    Runs simulation and returns result.
    """
    scale = condi['scale']
    integration_flag = condi['integration']
    sample = get_sample(default_cylinder_radius*scale,
                        default_cylinder_height*scale)
    simulation = get_simulation(integration_flag)
    simulation.setSample(sample)
    simulation.setTerminalProgressMonitor()
    simulation.runSimulation()
    return simulation.getIntensityData()


def plot(result, nframe, title):
    plt.subplot(2, 2, nframe+1)
    plt.subplots_adjust(wspace=0.3, hspace=0.3)
    im = plt.imshow(
        result.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
        extent=[result.getXmin()/deg, result.getXmax()/deg,
                result.getYmin()/deg, result.getYmax()/deg],
        aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.text(0.0, 2.1, title, horizontalalignment='center',
             verticalalignment='center',  fontsize=13)


if __name__ == '__main__':
    """
    Runs one simulation for each condition, and plots results on a single canvas.
    Conditions are small and large cylinders, with and without integration.
    """
    arg = ba.getFilenameOrPlotflag()

    # conditions to define cylinders scale factor and Monte-Carlo integration flag
    conditions = [
        {'name': "SmallAn",
         'title': "Small cylinders, analytical calculations", 'scale': 1,
         'integration': False, 'max': 1e+08},
        {'name': "SmallMC",
         'title': "Small cylinders, Monte-Carlo integration", 'scale': 1,
         'integration': True,  'max': 1e+08},
        {'name': "LargeAn",
         'title': "Large cylinders, analytical calculations", 'scale': 100,
         'integration': False, 'max': 1e+12},
        {'name': "LargeMC",
         'title': "Large cylinders, Monte-Carlo integration", 'scale': 100,
         'integration': True,  'max': 1e+12}
    ]

    if arg == "-p":
        import matplotlib
        from matplotlib import pyplot as plt
        from matplotlib import rc
        rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
        rc('text', usetex=True)
        plt.figure(figsize=(12.80, 10.24))
        for nplot in range(len(conditions)):
            condi = conditions[nplot]
            title = condi['title']
            print("Generating intensity map for " + title)
            intensities = simulate(condi)
            plot(intensities, nplot, title)
        plt.show()
    else:
        for condi in conditions:
            intensities = simulate(condi)
            fname = "%s.%s.int" % (arg, condi['name'])
            ba.IntensityDataIOFactory.writeIntensityData(intensities, fname)
            print("Stored intensity map in " + fname)

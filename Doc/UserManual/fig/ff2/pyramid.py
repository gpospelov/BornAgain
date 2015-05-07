"""
Rotated pyramid
"""
import numpy
import matplotlib as mpl
import matplotlib.pyplot as plt
from bornagain import *

phi_min, phi_max     = -2.0, 2.0
alpha_min, alpha_max = -2.0, 2.0
phi_min, phi_max     = 0, 6.0
alpha_min, alpha_max = 0, 6.0

def get_sample(omega):
    """
    Build and return the sample representing rotated pyramids on top of substrate
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = HomogeneousMaterial("Particle", 1e-3, 0)

    # collection of particles
    pyramid_ff = FormFactorPyramid(10*nanometer, 5*nanometer, deg2rad(54.73))
    pyramid = Particle(m_particle, pyramid_ff)
    transform = RotationZ(omega*degree)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(pyramid, transform)

    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    m = 1000
    simulation.setDetectorParameters(m, (phi_min)*degree, (phi_max)*degree,
                                     m, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0, 0)
    return simulation


def run_simulation(omega):
    """
    Run simulation and plot results
    """
    sample = get_sample(omega)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.getIntensityData().getArray() + 1  # for log scale



if __name__ == '__main__':
    mpl.rcParams['image.interpolation'] = 'none'
    n    = 4
    nrow = 1
    ncol = 1+(n-1)//nrow
    result = []
    vmin = None
    vmax = None
    for i in range(n):
        omega=45*i/(n-1)
        data = run_simulation(omega)
        result.append([omega, data])
        vmin = vmin and min(vmin,data.min()) or data.min()
        vmax = vmax and max(vmin,data.max()) or data.max()
        
    norm = mpl.colors.LogNorm(vmin,vmax)
    
    fig,axes = plt.subplots(nrow, ncol, figsize=(5*ncol+2, 5*nrow+1))
    
    plt.subplots_adjust(wspace=0.1, hspace=0.1,
                        left=0.04, right=0.96, bottom=0.04, top=.96 )
                        
    for i in range(n):
        omega,data = result[i]
        # showing the result
        ax = (axes.flat)[i]
        im = ax.imshow(numpy.rot90(data, 1),
                  norm=norm,
                  extent=[phi_min, phi_max, alpha_min, alpha_max],
                  aspect=1)
        ax.set_xlabel(r'$\phi_{\rm f} (^{\circ})$', fontsize=24)
        if i==0:
            ax.set_ylabel(r'$\alpha_{\rm f} (^{\circ})$', fontsize=24)
        ax.set_title(r'$\omega=%d^\circ$' % omega, fontsize=24)
    fig.subplots_adjust(right=0.8)
    cbar_ax = fig.add_axes([0.825, 0.19, 0.014, 0.62])
    cb = fig.colorbar(im, cax=cbar_ax)
    cb.set_label(r'Intensity (arb. units)', fontsize=24)
    plt.savefig("test.png", format="png", bbox_inches = 'tight')
#    plt.show()

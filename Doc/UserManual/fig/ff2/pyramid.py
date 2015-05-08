"""
Rotated pyramid
"""
import numpy
import matplotlib as mpl
import matplotlib.pyplot as plt
import bornagain as ba

class Detector:
    def __init__(self, bins_per_dimension, phi_min, phi_max, alpha_min, alpha_max):
        self.m = bins_per_dimension
        self.p_min = phi_min
        self.p_max = phi_max
        self.a_min = alpha_min
        self.a_max = alpha_max
    def rectangle:
        return [p_min, p_max, a_min, a_max],

class Result:
    def __init__(self, idx, pars, data, title ):
        self.idx = idx
        self.pars = pars
        self.data = data
        self.title = title
        
def make_plot( results ):
    for res in results:
        data = res.data
        ax = (axes.flat)[res.idx]
        im = ax.imshow(numpy.rot90(data, 1),
                       norm=norm,
                       extent=det.rectangle()
                       aspect=1)
        ax.set_xlabel(r'$\phi_{\rm f} (^{\circ})$', fontsize=24)
        if i==0:
            ax.set_ylabel(r'$\alpha_{\rm f} (^{\circ})$', fontsize=24)
        ax.set_title(res.title, fontsize=24)
    fig.subplots_adjust(right=0.8)
    cbar_ax = fig.add_axes([0.825, 0.19, 0.014, 0.62])
    cb = fig.colorbar(im, cax=cbar_ax)
    cb.set_label(r'Intensity (arb. units)', fontsize=24)

def get_sample(omega):
    """
    Build and return the sample representing rotated pyramids on top of substrate
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = ba.HomogeneousMaterial("Particle", 1e-3, 0)

    # collection of particles
    pyramid_ff = ba.FormFactorPyramid(10*nanometer, 5*nanometer, deg2rad(54.73))
    pyramid = ba.Particle(m_particle, pyramid_ff)
    transform = ba.RotationZ(omega*degree)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(pyramid, transform)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation(det):
    """
    Create and return GISAXS simulation with beam and det defined
    """
    simulation = ba.Simulation()
    simulation.setDetParameters(
        det.m, det.p_min*degree, det.p_max*degree,
        det.m, det.a_min*degree, det.a_max*degree )
    simulation.setBeamParameters(1.0*angstrom, 0, 0)
    return simulation


def run_simulation(det,omega):
    """
    Run simulation and plot results
    """
    sample = get_sample(omega)
    simulation = get_simulation(det)
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.getIntensityData().getArray() + 1  # for log scale


if __name__ == '__main__':
    det = Detector( 200, 0, 5, 0, 5 )
    mpl.rcParams['image.interpolation'] = 'none'
    n    = 4
    nrow = 1
    ncol = 1+(n-1)//nrow
    results = []
    vmin = None
    vmax = None
    for i in range(n):
        omega=45*i/(n-1)
        pars = [omega]
        title = r'$\omega=%d^\circ$' % omega
        data = run_simulation(det,pars)
        results.append( Result(i, pars, data, title) )
        vmin = vmin and min(vmin,data.min()) or data.min()
        vmax = vmax and max(vmin,data.max()) or data.max()
        
    norm = mpl.colors.LogNorm(vmin,vmax)
    
    fig,axes = plt.subplots(nrow, ncol, figsize=(5*ncol+2, 5*nrow+1))
    
    plt.subplots_adjust(wspace=0.1, hspace=0.1,
                        left=0.04, right=0.96, bottom=0.04, top=.96 )

    make_plot( results )
#    plt.savefig("test.pdf", format="pdf", bbox_inches = 'tight')
    plt.show()

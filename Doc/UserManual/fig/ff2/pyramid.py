"""
Rotated pyramid
"""
import numpy
import matplotlib as mpl
import matplotlib.pyplot as plt
import bornagain as ba
from bornagain import nanometer, degree, angstrom, deg2rad

class Detector:
    def __init__(self, bins_per_dimension, phi_min, phi_max, alpha_min, alpha_max):
        self.m = bins_per_dimension
        self.p_min = phi_min
        self.p_max = phi_max
        self.a_min = alpha_min
        self.a_max = alpha_max
    def rectangle(self):
        return (self.p_min, self.p_max, self.a_min, self.a_max)

class Result:
    def __init__(self, idx, data, title ):
        self.idx = idx
        self.data = data
        self.title = title
        
def make_plot( results, nrow ):
    mpl.rcParams['image.interpolation'] = 'none'
    n = len(results)
    ncol = 1+(n-1)//nrow
    # parameters as fraction of subfig size
    yskip      = 0.2 #+ncol*0.02
    bottomskip = yskip
    topskip    = yskip/2
    xskip      = 0.18
    leftskip   = xskip
    rightskip  = 0.28+ncol*0.03
    xtot = ncol*1.0 + (ncol-1)*xskip + leftskip + rightskip
    ytot = nrow*1.0 + (nrow-1)*yskip + bottomskip + topskip
    # we need parameters as fraction of total fig size
    xskip      /= xtot
    leftskip   /= xtot
    rightskip  /= xtot
    yskip      /= ytot
    bottomskip /= ytot
    topskip    /= ytot
    # set total figure dimensions
    ftot = 5
    fontsize = 18+36.0/(ncol+2)
    fig,tmp = plt.subplots(nrow, ncol, figsize=(ftot*xtot, ftot*ytot))
    if n>1:
        axes = tmp.flat
    else:
        axes = [tmp]
    vmin = None
    vmax = None
    for res in results:
        vmin = vmin and min(vmin,res.data.min()) or res.data.min()
        vmax = vmax and max(vmin,res.data.max()) or res.data.max()
    norm = mpl.colors.LogNorm(vmin,vmax)
    for res in results:
        data = res.data
        ax = axes[res.idx]
        im = ax.imshow(numpy.rot90(data, 1),
                       norm=norm,
                       extent=det.rectangle(),
                       aspect=1)
        ax.set_xlabel(r'$\phi_{\rm f} (^{\circ})$', fontsize=fontsize)
        if res.idx%ncol==0:
            ax.set_ylabel(r'$\alpha_{\rm f} (^{\circ})$', fontsize=fontsize)
        ax.set_title(res.title, fontsize=fontsize)
        ax.tick_params(axis='both', which='major', labelsize=fontsize*21/24)
    plt.subplots_adjust(wspace=xskip, hspace=yskip,
                        left=leftskip, right=1-rightskip,
                        bottom=bottomskip, top=1-topskip )
    cbar_ax = fig.add_axes([1-rightskip+0.4*xskip, bottomskip,
                            0.25*xskip, 1-bottomskip-topskip])
    cb = fig.colorbar(im, cax=cbar_ax)
    cb.set_label(r'Intensity (arb. units)', fontsize=fontsize)

def get_sample(ff,trafo):
    """
    Build and return a sample consisting of uncorrelated particles with given
    form factor and transformation operator
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = ba.HomogeneousMaterial("Particle", 1e-5, 0)

    # collection of particles
    particle = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(particle, trafo)

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
    simulation.setDetectorParameters(
        det.m, det.p_min*degree, det.p_max*degree,
        det.m, det.a_min*degree, det.a_max*degree )
    simulation.setBeamParameters(1.0*angstrom, 0, 0)
    return simulation


def run_simulation(det,ff,trafo):
    """
    Run simulation and plot results
    """
    sample = get_sample(ff,trafo)
    simulation = get_simulation(det)
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.getIntensityData().getArray() + 1e-80  # for log scale


if __name__ == '__main__':
    det = Detector( 200, 0, 5, 0, 5 )
    n    = 5
    nrow = 1
    results = []
    for i in range(n):
        omega=0 #45*i/(n-1)
        title = r'$\omega=%d^\circ$' % omega
        ff = ba.FormFactorPyramid(10*nanometer, 5*nanometer, deg2rad(54.73))
        trafo = ba.RotationZ(omega*degree)
        data = run_simulation(det,ff,trafo)
        results.append( Result(i, data, title) )
    
    make_plot( results, nrow )
#    plt.savefig("test.pdf", format="pdf", bbox_inches = 'tight')
    plt.show()

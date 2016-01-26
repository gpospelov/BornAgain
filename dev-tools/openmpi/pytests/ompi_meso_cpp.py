from mpi4py import MPI # this line has to be first
import numpy
import matplotlib
matplotlib.use('Agg')
import pylab
from math import degrees
import math
from time import time
import ctypes
from libBornAgainCore import *
from libBornAgainFit import *

comm = MPI.COMM_WORLD
world_size = comm.Get_size()
world_rank = comm.Get_rank()

class MesoSampleBuilder(ISampleBuilder):
    """
    Meso crystal sample builder
    """
    def __init__(self):
        ISampleBuilder.__init__(self)
        self.sample = None
        # parameters describing the sample

        self.m_lattice_length_a = ctypes.c_double(1.246708e+01*nanometer)
        self.m_lattice_length_c = ctypes.c_double(1.338787e+01*nanometer)
        self.m_nanoparticle_radius = ctypes.c_double(4.848528e+00*nanometer)
        self.m_sigma_nanoparticle_radius = ctypes.c_double(3.6720e-01*nanometer)
        self.m_meso_height = ctypes.c_double(1.1221e+02*nanometer)
        self.m_meso_radius = ctypes.c_double(9.4567e+02*nanometer)
        self.m_sigma_meso_height = ctypes.c_double(5.0*nanometer)
        self.m_sigma_meso_radius = ctypes.c_double(5.0*nanometer)
        self.m_sigma_lattice_length_a = ctypes.c_double(1.1601e+00*nanometer)
        self.m_surface_filling_ratio = ctypes.c_double(1.7286e-01)
        self.m_roughness = ctypes.c_double(10.0*nanometer)
        self.m_scale_param = math.sqrt(math.log((self.m_sigma_nanoparticle_radius.value/self.m_nanoparticle_radius.value)**2+1.0))

        # register parameters
        self.registerParameter("meso_radius", ctypes.addressof(self.m_meso_radius))
        self.registerParameter("surface_filling_ratio", ctypes.addressof(self.m_surface_filling_ratio))
        self.registerParameter("meso_height", ctypes.addressof(self.m_meso_height))
        self.registerParameter("sigma_meso_height", ctypes.addressof(self.m_sigma_meso_height))
        self.registerParameter("sigma_meso_radius", ctypes.addressof(self.m_sigma_meso_radius))
        self.registerParameter("lattice_length_a", ctypes.addressof(self.m_lattice_length_a))
        self.registerParameter("lattice_length_c", ctypes.addressof(self.m_lattice_length_c))
        self.registerParameter("nanoparticle_radius", ctypes.addressof(self.m_nanoparticle_radius))
        self.registerParameter("sigma_nanoparticle_radius", ctypes.addressof(self.m_sigma_nanoparticle_radius))
        self.registerParameter("sigma_lattice_length_a", ctypes.addressof(self.m_sigma_lattice_length_a))
        self.registerParameter("roughness", ctypes.addressof(self.m_roughness))

    def CreateMeso(self, a, c, material, radius, sigma_radius, meso_form_factor):
        lattice = self.CreateLattice(a, c)
        bas_a = lattice.getBasisVectorA()
        bas_b = lattice.getBasisVectorB()
        bas_c = lattice.getBasisVectorC()
        #particle = Particle(material, FormFactorSphereGaussianRadius(radius, sigma_radius))
        particle = Particle(material, FormFactorSphereLogNormalRadius(radius, self.m_scale_param, 10))
        position_0 = kvector_t(0.0, 0.0, 0.0)
        position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c)
        position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c)
        pos_vector = [position_0, position_1, position_2]
        basis = ParticleComposition()
        basis.addParticles(particle, pos_vector)
        npc = Crystal(basis, lattice)
        dw_factor = self.m_sigma_lattice_length_a.value*self.m_sigma_lattice_length_a.value/6.0
        npc.setDWFactor(dw_factor)
        result = MesoCrystal(npc, meso_form_factor)
        return result

    def CreateLattice(self, a, c):
        result = Lattice.createTrigonalLattice(a, c*2.3)
        result.setSelectionRule(SimpleSelectionRule(-1, 1, 1, 3))
        return result

    # constructs the sample for current values of parameters
    def buildSample(self):
        # create materials
        surface_density = self.m_surface_filling_ratio.value/numpy.pi/self.m_meso_radius.value/self.m_meso_radius.value
        n_particle = complex(1.0-2.84e-5, 4.7e-7)
        avg_n_squared_meso = 0.7886*n_particle**2 + 0.2114
        n_avg = numpy.sqrt(self.m_surface_filling_ratio.value*avg_n_squared_meso + 1.0 - self.m_surface_filling_ratio.value)
        n_particle_adapted = numpy.sqrt(n_avg**2 + n_particle**2 - 1.0)
        particle_material = HomogeneousMaterial("nanoparticle", n_particle_adapted)

        ff_cyl = FormFactorCylinder(self.m_meso_radius.value, self.m_meso_height.value)
        ff_meso = FormFactorDecoratorDebyeWaller(ff_cyl, self.m_sigma_meso_height.value**2/2.0,
                                             self.m_sigma_meso_radius.value**2/2.0)

        # Create multilayer
        multi_layer = MultiLayer()

        air_material = HomogeneousMaterial("Air", 0.0, 0.0)
        substrate_material = HomogeneousMaterial("Substrate", 7.57e-6, 1.73e-7)
        average_layer_material = HomogeneousMaterial("AverageLayer", n_avg)
        air_layer = Layer()
        air_layer.setMaterial(air_material)
        avg_layer = Layer()
        avg_layer.setMaterial(average_layer_material)
        avg_layer.setThickness(self.m_meso_height.value)
        substrate_layer = Layer()
        substrate_layer.setMaterial(substrate_material)
        particle_decoration = ParticleLayout()

        max_phi_rotation_steps = 180
        max_tilt_rotation_steps = 1

        phi_step = 2.0*numpy.pi/3.0/max_phi_rotation_steps
        phi_start = 0.0
        #zeta_step = 0.5*degree
        #zeta_start = -zeta_step*(max_tilt_rotation_steps/2)
        for i in range(0, max_phi_rotation_steps):
            for j in range(0, max_tilt_rotation_steps):
                #trafo_y = Transform3D.createRotateY(zeta_start + j*zeta_step)
                trafo_z = Transform3D.createRotateZ(phi_start + i*phi_step)
                #trafo = trafo_z*trafo_y
                trafo = trafo_z
                particle_decoration.addParticle(
                    self.CreateMeso(self.m_lattice_length_a.value, self.m_lattice_length_c.value,
                            particle_material, self.m_nanoparticle_radius.value,
                            self.m_sigma_nanoparticle_radius.value, ff_meso), trafo,
                            self.m_meso_height.value)

        particle_decoration.setTotalParticleSurfaceDensity(surface_density)

        avg_layer.addLayout(particle_decoration)

        roughness = LayerRoughness(self.m_roughness.value, 0.3, 500.0 * nanometer)

        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(avg_layer)
        multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)
        self.sample = multi_layer
        return self.sample


def get_real_data():
    return OutputDataIOFactory.readIntensityData("001_150_P109_cut_phitheta.txt.gz")


def get_simulation():
    # build and run experiment
    simulation = GISASSimulation()
    simulation.setBeamParameters(1.77*angstrom, 0.4*degree, 0.0*degree)
    simulation.setBeamIntensity(4.942287e+12)

    #sim_params = SimulationParameters()
    #sim_params.m_mc_integration = True
    #sim_params.m_mc_points = 20
    #simulation.setSimulationParameters(sim_params)

    #simulation.setDetectorResolutionFunction(ResolutionFunction2DGaussian(0.00025, 0.00025))

    #wavelength_distr = DistributionLogNormal(1.77*angstrom, 0.01)
    #wavelength_distr = DistributionGaussian(1.77*angstrom, 0.02*angstrom)
    #alpha_distr = DistributionGaussian(-0.4*degree, 0.02*degree)
    #phi_distr = DistributionGaussian(0.0*degree, 0.02*degree)
    #simulation.addParameterDistribution("*/Beam/wavelength", wavelength_distr, 5)
    #simulation.addParameterDistribution("*/Beam/alpha", alpha_distr, 5)
    #simulation.addParameterDistribution("*/Beam/phi", phi_distr, 5)

    sample_builder = MesoSampleBuilder()
    simulation.setSampleBuilder(sample_builder)
    real_data = get_real_data()
    simulation.setDetectorParameters(real_data)

    return simulation


def run_simulation():
    """
    main function to run fitting
    """
    simulation = get_simulation()


    #if(world_size == 1):
    #    print "Not an OpenMPI environment, run with 'mpirun -np 12 python ompi_sim_example.py'"
    #    exit(0)

    SetMessageLevel("DEBUG")

    thread_info = ThreadInfo()
    thread_info.n_threads = 4
    simulation.setThreadInfo(thread_info)
    simulation.runOMPISimulation()

    if(world_rank == 0):
        simulation.normalize()
        result = simulation.getIntensityData()
        print result.getArray()
        axis_phi = result.getAxis(0)
        axis_alpha = result.getAxis(1)
        im = pylab.imshow(result.getArray()+1, norm=matplotlib.colors.LogNorm(),
                 extent=[axis_phi.getMin(), axis_phi.getMax(), axis_alpha.getMin(), axis_alpha.getMax()])
        pylab.colorbar(im)
        pylab.xlabel(r'$\phi_f$', fontsize=20)
        pylab.ylabel(r'$\alpha_f$', fontsize=20)
        pylab.show()
        pylab.savefig("result.png")
        OutputDataIOFactory.writeIntensityData(result, 'result.txt')




if __name__ == '__main__':
    run_simulation()


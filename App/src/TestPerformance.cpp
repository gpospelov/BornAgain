#include "TestPerformance.h"
#include "Types.h"
#include "Units.h"
#include "Utils.h"
#include "Exceptions.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "OpticalFresnel.h"

#include "InterferenceFunctionNone.h"
#include "NanoParticleDecoration.h"
#include "NanoParticle.h"
#include "LayerDecorator.h"
#include "GISASExperiment.h"
#include "FormFactors.h"
#include "BasicVector3D.h"
#include "Transform3D.h"
#include "MesoCrystal.h"
#include "NanoParticleCrystal.h"
#include "LatticeBasis.h"
#include "MathFunctions.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"


#include "TSystem.h"
#include "TDatime.h"
#include "TBenchmark.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>




TestPerformance::TestPerformance()
{
    // preparing performance tests to run
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_FresnelCoeff(), 200000) );
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_Pyramid(), 20) );
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_RotatedPyramid(), 20) );
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_MesoCrystal(), 2) );

    std::cout << "TestPerformance::TestPerformance() -> Info. Preparing to run " << m_tests.size() << " performance tests."  << std::endl;

}


TestPerformance::~TestPerformance()
{
    for(performance_tests_t::iterator it=m_tests.begin(); it!= m_tests.end(); it++) {
        delete (*it);
    }

}

/* ************************************************************************* */
// running performance tests
/* ************************************************************************* */
void TestPerformance::execute()
{
    // getting system information
    get_sysinfo();

    // run tests
    TBenchmark mb;
    for(performance_tests_t::iterator it=m_tests.begin(); it!= m_tests.end(); it++) {
        PerformanceTestInfo *test_info = (*it);
        std::string test_name = test_info->m_test->getName();

        std::cout << "Running test: " << std::setw(20) << std::left << test_name << " ... ";
        std::cout.flush();
        test_info->m_test->initialise();
        mb.Start( test_name.c_str() );
        for(int i=0; i<test_info->m_nrepetitions; i++){
            test_info->m_test->execute();
        }
        mb.Stop( test_name.c_str() );

        // printing results
        double result = mb.GetCpuTime( test_name.c_str() );
        double fhz = double(test_info->m_nrepetitions)/result;
        std::cout << std::setw(6) << std::left << result << " sec, "
                  << std::setw(8) << std::left << fhz << " Hz ("
                  << std::setw(4) << std::left << test_info->m_nrepetitions << " repetitions )"<< std::endl;
        // saving results
        std::ostringstream os;
        os << std::setprecision(6)  << fhz;
        m_performance_info[test_name] = os.str();
    }

    write_performance();

}


/* ************************************************************************* */
// save performance information
/* ************************************************************************* */
void TestPerformance::write_performance()
{
    // appending performance information to the file
    std::string filename("perf_history.txt");
    filename = std::string(Utils::FileSystem::GetHomePath())+std::string("./Examples/Performance/") + filename;

    std::ofstream file;
    file.open(filename.c_str(), std::ios_base::app);
    if( !file.is_open() ) {
        throw FileNotIsOpenException("TestPerformance::execute() -> Error. Can't open file '"+filename+"' for writing.");
    }

    file << m_performance_info["datime"] << get_delimeter();
    file << std::left << adjust_string_length(m_performance_info["hostname"],10) << get_delimeter();
    file << std::left << adjust_string_length(m_performance_info["sysinfo"],23) << get_delimeter();
    for(performance_tests_t::iterator it=m_tests.begin(); it!= m_tests.end(); it++) {
        std::string test_name = (*it)->m_test->getName();
        file << std::left << adjust_string_length(m_performance_info[test_name],7) << get_delimeter();
    }
    file<<std::endl;

    file.close();

    std::cout << "TestPerformance::write_performance() -> Info. File '" << filename << "' is updated." << std::endl;
}


/* ************************************************************************* */
// adjust length of string
/* ************************************************************************* */
std::string TestPerformance::adjust_string_length(std::string name, int length)
{
    std::string newstring = name;
    newstring.resize(length,' ');
    return newstring;
}



/* ************************************************************************* */
// fill system information
/* ************************************************************************* */
void TestPerformance::get_sysinfo()
{
    // saving date and time
    TDatime td;
    m_performance_info["datime"] = std::string(td.AsSQLString());

    // saving host name
    std::string hostname(gSystem->HostName());
    // stripping host name after first '.' (somehost.jcns.frm2 -> somehost)
    std::string::size_type pos = hostname.find_first_of('.');
    if(pos != std::string::npos) {
        hostname.erase(pos,hostname.size()-pos);
    }
    m_performance_info["hostname"] = hostname;

    // saving hardware information
    std::string sysinfo;
    SysInfo_t sys_info;
    int status = gSystem->GetSysInfo(&sys_info);
    if( status == -1) {
        std::cout << "TestPerformance::get_sysinfo() -> Warning! Can't get system info." << std::endl;
        m_performance_info["sysinfo"] = std::string("failed");
    }else{
        std::ostringstream os;
        os << std::string(gSystem->GetBuildArch()) << ", "<< sys_info.fCpuSpeed << " MHz";
        //os << ", " << 	sys_info.fL2Cache << " Kb";
        m_performance_info["sysinfo"] = os.str();
    }
}


/* ************************************************************************* */
// our test starts here:  PerfTest_FresnelCoeff
/* ************************************************************************* */
void PerfTest_FresnelCoeff::initialise()
{
    if(m_sample) delete m_sample;
    m_sample = 0;

    // materials
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience", complex_t(1.0, 0.0) );
    const IMaterial *mAg1 = matManager.addHomogeneousMaterial("ag1", complex_t(1.0-5e-6, 0.0) );
    const IMaterial *mCr1 = matManager.addHomogeneousMaterial("cr1", complex_t(1.0-10e-6, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0.0) );

    Layer lAmbience; lAmbience.setMaterial(mAmbience, 0);
    Layer lAg1; lAg1.setMaterial(mAg1, 150.0*Units::nanometer);
    Layer lCr1; lCr1.setMaterial(mCr1, 120.0*Units::nanometer);
    Layer lSubstrate; lSubstrate.setMaterial(mSubstrate, 0);

    // multi layer
    MultiLayer *multi_layer = new MultiLayer;
    multi_layer->addLayer(lAmbience);
    LayerRoughness roughness;
    roughness.setSigma(0.0*Units::nanometer);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(5000*Units::nanometer);
    const unsigned nrepetitions = 2;
    for(unsigned i=0; i<nrepetitions; ++i) {
        multi_layer->addLayerWithTopRoughness(lAg1, roughness);
        multi_layer->addLayerWithTopRoughness(lCr1, roughness);
    }
    multi_layer->addLayerWithTopRoughness(lSubstrate, roughness);
    m_sample = multi_layer;
}

void PerfTest_FresnelCoeff::execute()
{
    static double alpha_i = -0.3;
    kvector_t kvec;
    kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
    OpticalFresnel::MultiLayerCoeff_t coeffs;
    OpticalFresnel fresnelCalculator;
    MultiLayer *ml = (MultiLayer *) m_sample;
    fresnelCalculator.execute(*ml, kvec, coeffs);
}


/* ************************************************************************* */
// our test starts here:  PerfTest_Pyramid
/* ************************************************************************* */
void PerfTest_Pyramid::initialise()
{
    // sample
    if(m_sample) delete m_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    m_sample = p_multi_layer;
    // experiment
    if(m_experiment) delete m_experiment;
    m_experiment = new GISASExperiment;
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    m_experiment->setSample(m_sample);
}

void PerfTest_Pyramid::execute()
{
    m_experiment->runSimulation();
}


/* ************************************************************************* */
// our test starts here:  PerfTest_RotatedPyramid
/* ************************************************************************* */
void PerfTest_RotatedPyramid::initialise()
{
    // sample
    if(m_sample) delete m_sample;
    m_sample = 0;
    const double angle_around_z = 45.*Units::degree;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    NanoParticle *pyramid = new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73)) );

    Geometry::Transform3D *transform = new Geometry::Transform3D();
    *transform = Geometry::RotateZ3D(angle_around_z);

    NanoParticleDecoration particle_decoration;

    particle_decoration.addNanoParticle(pyramid, transform);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    m_sample = p_multi_layer;
    // experiment
    if(m_experiment) delete m_experiment;
    m_experiment = new GISASExperiment;
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    m_experiment->setSample(m_sample);
}

void PerfTest_RotatedPyramid::execute()
{
    m_experiment->runSimulation();

}


/* ************************************************************************* */
// our test starts here:  PerfTest_MesoCrystal
/* ************************************************************************* */
void PerfTest_MesoCrystal::initialise()
{
    // sample
    if(m_sample) delete m_sample;
    m_sample = 0;

    // create mesocrystal
    double R = 6.1*Units::nanometer;
    Lattice lat = Lattice::createTrigonalLattice(R*2.0, R*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    complex_t n_particle(1.0-1.5e-5, 1.3e-6);
    NanoParticle particle(n_particle, new FormFactorFullSphere(R));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    NanoParticleCrystal npc(basis, lat);
    MesoCrystal meso(npc.clone(), new FormFactorCylinder(0.2*Units::micrometer, 300*Units::nanometer));
    MesoCrystal meso2(npc.clone(), new FormFactorPyramid(0.2*Units::micrometer, 300*Units::nanometer, 84*Units::degree));

    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-3.5e-6, 7.8e-8);

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air2", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate2", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
//    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(800.0*Units::nanometer,
            50*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(meso.clone(), 0.0, 0.5);
    particle_decoration.addNanoParticle(meso2.clone(), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    m_sample = p_multi_layer;
    // experiment
    m_experiment = new GISASExperiment;
    m_experiment->setSample(m_sample);
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(0.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);

}


void PerfTest_MesoCrystal::execute()
{
    m_experiment->runSimulation();
}

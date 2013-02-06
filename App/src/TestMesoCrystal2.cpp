#include "TestMesoCrystal2.h"
#include "AttLimits.h"
#include "Crystal.h"
#include "DrawHelper.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactors.h"
#include "GISASExperiment.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSTools.h"
#include "LatticeBasis.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MathFunctions.h"
#include "MesoCrystal.h"
#include "MinimizerFactory.h"
#include "MultiLayer.h"
#include "OutputDataIOFactory.h"
#include "OutputDataReader.h"
#include "OutputDataFunctions.h"
#include "ParticleDecoration.h"
#include "ProgramOptions.h"
#include "ResolutionFunction2DSimple.h"
#include "SampleFactory.h"
#include "TRange.h"
#include "Types.h"
#include "Units.h"
#include "Utils.h"

#include "TCanvas.h"
#include "TH2D.h"
#include <boost/assign/list_of.hpp>


/* ************************************************************************* */
// TestMesoCrystal2 member definitions
/* ************************************************************************* */
TestMesoCrystal2::TestMesoCrystal2()
    : m_real_data(0)
    , m_sample_builder(0)
    , m_experiment(0)
    , m_fitSuite(0)
{
    m_sample_builder = new SampleBuilder;
}


TestMesoCrystal2::~TestMesoCrystal2()
{
    delete m_real_data;
    delete m_sample_builder;
    delete m_experiment;
    delete m_fitSuite;
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::execute()
{
    initializeRealData();

    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("c1_test_meso_crystal", "mesocrystal");
    c1->cd(); gPad->SetLogz();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    IsGISAXSTools::setMinimum(100.);
    IsGISAXSTools::setMaximum(1e7);
    IsGISAXSTools::drawOutputDataInPad(*m_real_data, "CONT4 Z", "experiment");
    c1->Update();

    // initializing experiment using real data
    initializeExperiment(m_real_data);

    // setting fitSuite
    m_fitSuite = new FitSuite();
    m_fitSuite->getFitObjects()->setExperimentNormalize(true);

    int fitconfig = (*mp_options)["fitconfig"].as<int>();
    fitsuite_setup(fitconfig);

    m_fitSuite->addExperimentAndRealData(*m_experiment, *m_real_data);

    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createTreeObserver() );

    m_fitSuite->runFit();

    for(FitSuiteParameters::iterator it = m_fitSuite->getFitParameters()->begin(); it!=m_fitSuite->getFitParameters()->end(); ++it) {
        std::cout << (*it) << std::endl;
    }
}


// ----------------------------------------------------------------------------
// initialize real data
// ----------------------------------------------------------------------------
void TestMesoCrystal2::initializeRealData()
{
    delete m_real_data;
    // reading data file
    //std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_qyqz.txt.gz";
    std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_phitheta.txt.gz";

    m_real_data = OutputDataIOFactory::getOutputData(file_name);

    //    OutputData<double > *real_data_half = doubleBinSize(*real_data);
    //    OutputData<double > *real_data_quarter = doubleBinSize(*real_data_half);
    //    OutputData<double > *real_data_eighth = doubleBinSize(*real_data_quarter);
}


// ----------------------------------------------------------------------------
// run appropriate FitSuite configuration
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_setup(int nconfig)
{
    switch(nconfig) {
    case 1:
        fitsuite_config1();
        break;
    case 2:
        fitsuite_config2();
        break;
    case 3:
        fitsuite_config3();
        break;
    default:
        throw LogicErrorException("TestMesoCrystal2::fitsuite_setup() -> Error! Can't setup FitSuite");
        break;
    }
}


// ----------------------------------------------------------------------------
// FitSuite configuration #3
// * Mask on fit data
// * Several fit iterations with different set of fixed released parameters
// * ChiSquaredModule with normalizer
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config3()
{
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );

    m_fitSuite->getAttributes().setStepFactor(0.01);
    m_fitSuite->addFitParameter("*/lattice_length_a",          6.2*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/nanoparticle_radius",       5.7*Units::nanometer,    AttLimits::limited(2.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_height",               500.0*Units::nanometer,  AttLimits::limited(100.0*Units::nanometer, 2000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_radius",               1000.0*Units::nanometer, AttLimits::limited(100.0*Units::nanometer, 5000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_height",         5.0*Units::nanometer,    AttLimits::limited(10.0*Units::nanometer, 200.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_radius",         50.0*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 500.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_lattice_length_a",    1.5*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/surface_filling_ratio",     0.25,                    AttLimits::limited(0.1, 0.4) );
    m_fitSuite->addFitParameter("*/roughness",                 1.0*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*Beam/intensity",             8e12,                    AttLimits::limited(8e11, 8e13) );

    fixplan_t fixplan;
    fixplan.resize(7);
    fixplan[0] = boost::assign::list_of("*/lattice_length_a")("*/nanoparticle_radius");
    fixplan[1] = boost::assign::list_of("*/meso_height")("*/meso_radius");
    fixplan[2] = boost::assign::list_of("*Beam/intensity");
    fixplan[3] = boost::assign::list_of("*/surface_filling_ratio");
    fixplan[4] = boost::assign::list_of("*/roughness");
    fixplan[5] = boost::assign::list_of("*/sigma_lattice_length_a")("*/sigma_nanoparticle_radius");
    fixplan[6] = boost::assign::list_of("*/sigma_meso_height")("*/sigma_meso_radius");

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitSuiteStrategyAdjustParameters *strategy = new FitSuiteStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        strategy->setPreserveOriginalValues(true); // initial values of parameters will be restored after each fit
        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        m_fitSuite->addFitStrategy(strategy);
    }
    FitSuiteStrategyAdjustParameters *strategy_all = new FitSuiteStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    m_fitSuite->addFitStrategy(strategy_all);

//    const double minima[]={0.042, 0.004};
//    const double maxima[]={0.052, 0.03};
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.041, 0.003, 0.051, 0.03);
    m_real_data->setMask(*mask1);


}


// ----------------------------------------------------------------------------
// FitSuite configuration #2
// Same as configuration #1, except that evey concequent fit uses optimal parameters
// from previous fit
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config2()
{
    fitsuite_config1();
    for(FitSuiteStrategies::iterator it = m_fitSuite->getFitStrategies()->begin(); it!= m_fitSuite->getFitStrategies()->end(); ++it) {
        FitSuiteStrategyAdjustParameters *strategy = dynamic_cast<FitSuiteStrategyAdjustParameters *>( (*it) );
        assert(strategy);
        strategy->setPreserveOriginalValues(false);
    }
}


// ----------------------------------------------------------------------------
// FitSuite configuration #1
// 7 fit iterations with different sets of fixed/release parameters
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config1()
{

    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );

    m_fitSuite->addFitParameter("*/lattice_length_a",          6.2*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/nanoparticle_radius",       5.7*Units::nanometer,    1.0*Units::nanometer,   AttLimits::limited(2.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer,    0.05*Units::nanometer,  AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_height",               500.0*Units::nanometer,  100.0*Units::nanometer, AttLimits::limited(100.0*Units::nanometer, 2000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_radius",               1000.0*Units::nanometer, 100.0*Units::nanometer, AttLimits::limited(100.0*Units::nanometer, 5000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_height",         5.0*Units::nanometer,    1.0*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 200.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_radius",         50.0*Units::nanometer,   10.0*Units::nanometer,  AttLimits::limited(10.0*Units::nanometer, 500.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_lattice_length_a",    1.5*Units::nanometer,    0.5*Units::nanometer,   AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/surface_filling_ratio",     0.25,                    0.1,                    AttLimits::limited(0.1, 0.4) );
    m_fitSuite->addFitParameter("*/roughness",                 1.0*Units::nanometer,    0.1*Units::nanometer,   AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*Beam/intensity",             8e12,                    100,                    AttLimits::limited(8e11, 8e13) );

    fixplan_t fixplan;
    fixplan.resize(7);
    fixplan[0] = boost::assign::list_of("*/lattice_length_a")("*/nanoparticle_radius");
    fixplan[1] = boost::assign::list_of("*/meso_height")("*/meso_radius");
    fixplan[2] = boost::assign::list_of("*Beam/intensity");
    fixplan[3] = boost::assign::list_of("*/surface_filling_ratio");
    fixplan[4] = boost::assign::list_of("*/roughness");
    fixplan[5] = boost::assign::list_of("*/sigma_lattice_length_a")("*/sigma_nanoparticle_radius");
    fixplan[6] = boost::assign::list_of("*/sigma_meso_height")("*/sigma_meso_radius");

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitSuiteStrategyAdjustParameters *strategy = new FitSuiteStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        strategy->setPreserveOriginalValues(true); // initial values of parameters will be restored after each fit
        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        m_fitSuite->addFitStrategy(strategy);
    }
    FitSuiteStrategyAdjustParameters *strategy_all = new FitSuiteStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    m_fitSuite->addFitStrategy(strategy_all);

}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::initializeExperiment(const OutputData<double> *output_data)
{
    delete m_experiment;

    m_experiment = new GISASExperiment(mp_options);
    m_experiment->setSampleBuilder( m_sample_builder );
    m_experiment->setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    m_experiment->setBeamIntensity(8e12);
    m_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));

    if( !output_data ) {
        // initialize default detector
        m_experiment->setDetectorParameters(200, 0.3*Units::degree, 0.073, 200, -0.4*Units::degree, 0.066);
    } else {
        // if there is output_data as input parameter, build detector using output_data axises
        const IAxis *axis0 = output_data->getAxis(0);
        const IAxis *axis1 = output_data->getAxis(1);
        //std::cout << axis0->getSize() << " " << axis0->getMin() << " " << axis0->getMax() << " " << axis1->getSize() << " " << axis1->getMin() << " " << axis1->getMax() << std::endl;
        m_experiment->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());
    }
    m_experiment->printParameters();
}


/* ************************************************************************* */
// MesoCrystalBuilder member definitions
/* ************************************************************************* */
TestMesoCrystal2::SampleBuilder::SampleBuilder()
: m_meso_radius(1000.0*Units::nanometer)
, m_surface_filling_ratio(0.25)
, m_meso_height(200.0*Units::nanometer)
, m_sigma_meso_height(20.0*Units::nanometer)
, m_sigma_meso_radius(50.0*Units::nanometer)
, m_lattice_length_a(6.15*Units::nanometer)
, m_nanoparticle_radius(4.3*Units::nanometer)
, m_sigma_nanoparticle_radius(0.14*Units::nanometer)
, m_sigma_lattice_length_a(1.5*Units::nanometer)
, m_roughness(0.0*Units::nanometer)
{
    init_parameters();
}


ISample* TestMesoCrystal2::SampleBuilder::buildSample() const
{
    // create mesocrystal
    double surface_density = m_surface_filling_ratio/M_PI/m_meso_radius/m_meso_radius;
//    complex_t n_particle(1.0-1.55e-5, 1.37e-6); // data from Artur
    complex_t n_particle(1.0-2.84e-5, 4.7e-7); // data from http://henke.lbl.gov/optical_constants/getdb2.html
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(m_surface_filling_ratio*avg_n_squared_meso + 1.0 - m_surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    FormFactorCylinder ff_cyl(m_meso_height, m_meso_radius);
    FormFactorDecoratorDebyeWaller ff_meso(ff_cyl.clone(), m_sigma_meso_height*m_sigma_meso_height/2.0,
            m_sigma_meso_radius*m_sigma_meso_radius/2.0);

    // Create multilayer
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-7.57e-6, 1.73e-7);

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_average_layer_material = MaterialManager::instance().addHomogeneousMaterial("Averagelayer", n_avg);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer avg_layer;
    avg_layer.setMaterial(p_average_layer_material);
    avg_layer.setThickness(m_meso_height);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
    ParticleDecoration particle_decoration;
    size_t n_max_phi_rotation_steps = 180;
    size_t n_alpha_rotation_steps = 1;

    double alpha_step = 5.0*Units::degree/n_alpha_rotation_steps;
    double alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step;

    double phi_step = 2.0*M_PI/3.0/n_max_phi_rotation_steps;
    double phi_start = 0.0;
    for (size_t i=0; i<n_max_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
            Geometry::RotateZ3D transform1(phi_start + (double)i*phi_step);
            Geometry::RotateY3D transform2(alpha_start + j*alpha_step);
            Geometry::Transform3D *p_total_transform = new Geometry::Transform3D(transform1);
            particle_decoration.addParticle(createMesoCrystal(m_lattice_length_a,
                    n_particle_adapted, &ff_meso), p_total_transform, m_meso_height);
        }
    }

    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator avg_layer_decorator(avg_layer, particle_decoration);

    LayerRoughness roughness(m_roughness, 0.3, 500.0*Units::nanometer);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer_decorator);
    p_multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

//    std::cout << "Average layer index: " << n_avg << std::endl;
//    std::cout << "Adapted particle index: " << n_particle_adapted << std::endl;
//    std::cout << "Substrate layer index: " << n_substrate << std::endl;

    return p_multi_layer;
}

void TestMesoCrystal2::SampleBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("meso_radius", &m_meso_radius);
    getParameterPool()->registerParameter("surface_filling_ratio", &m_surface_filling_ratio);
    getParameterPool()->registerParameter("meso_height", &m_meso_height);
    getParameterPool()->registerParameter("sigma_meso_height", &m_sigma_meso_height);
    getParameterPool()->registerParameter("sigma_meso_radius", &m_sigma_meso_radius);
    getParameterPool()->registerParameter("lattice_length_a", &m_lattice_length_a);
    getParameterPool()->registerParameter("nanoparticle_radius", &m_nanoparticle_radius);
    getParameterPool()->registerParameter("sigma_nanoparticle_radius", &m_sigma_nanoparticle_radius);
    getParameterPool()->registerParameter("sigma_lattice_length_a", &m_sigma_lattice_length_a);
    getParameterPool()->registerParameter("roughness", &m_roughness);
}

MesoCrystal* TestMesoCrystal2::SampleBuilder::createMesoCrystal(double stacking_radius, complex_t n_particle,
        const IFormFactor* p_meso_form_factor) const
{
    const Lattice *p_lat = createLattice(stacking_radius);
    kvector_t bas_a = p_lat->getBasisVectorA();
    kvector_t bas_b = p_lat->getBasisVectorB();
    kvector_t bas_c = p_lat->getBasisVectorC();
    Particle particle(n_particle, new FormFactorSphereGaussianRadius(m_nanoparticle_radius, m_sigma_nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);

    Crystal npc(basis, *p_lat);
    delete p_lat;
    double dw_factor = m_sigma_lattice_length_a*m_sigma_lattice_length_a/6.0;
    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}

const Lattice *TestMesoCrystal2::SampleBuilder::createLattice(double stacking_radius) const
{
    Lattice *p_result = new Lattice(Lattice::createTrigonalLattice(stacking_radius*2.0, stacking_radius*2.0*2.3));
    p_result->setSelectionRule(SimpleSelectionRule(-1, 1, 1, 3));
    return p_result;
}



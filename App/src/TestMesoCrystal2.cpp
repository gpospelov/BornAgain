#include "TestMesoCrystal2.h"
#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "MesoCrystal.h"
#include "Crystal.h"
#include "FormFactors.h"
#include "LatticeBasis.h"
#include "MathFunctions.h"
#include "Utils.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "DrawHelper.h"
#include "OutputDataReader.h"
#include "OutputDataIOFactory.h"
#include "FitSuite.h"
#include "ROOTMinimizer.h"
#include "SampleFactory.h"
#include "FitMultiParameter.h"
#include "TRange.h"
#include "FittingHelper.h"

#include "TCanvas.h"
#include "TH2D.h"



TestMesoCrystal2::TestMesoCrystal2() : m_sample(0), m_experiment(0)
{

}


TestMesoCrystal2::~TestMesoCrystal2()
{
    delete m_sample;
    delete m_experiment;
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::execute()
{
    std::string canvas_name("TestMesoCrystal2_c1");
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas(canvas_name.c_str(), canvas_name.c_str(), 768, 1024);
    c1->Divide(2,3);

    // reading data file
    //std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_qyqz.txt.gz";
    std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_phitheta.txt.gz";
    OutputDataReader *reader = OutputDataIOFactory::instance().getReader(file_name);
    OutputData<double > *real_data = reader->getOutputData();
    delete reader;
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*real_data, "CONT4 Z", "experiment");
    c1->Update();



//    m_experiment->runSimulation();
//    m_experiment->normalize();
//    OutputData<double > *m_real_data = m_experiment->getOutputDataClone();

    // initializing experiment using real data to have detector axises like in real_data
    initializeExperiment(real_data);
    m_sample->walk_and_print();
    ParameterPool *pool = m_sample->createParameterTree();
    std::cout << *pool << std::endl;


    // setting fitSuite
    FitSuite *fitSuite = new FitSuite();
    fitSuite->setExperiment(m_experiment);
    fitSuite->setRealData(*real_data);
    fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    fitSuite->addFitParameter("/MultiLayer/LayerInterface1/roughness/sigma", 0.1, 0.05, TRange<double>(0.0, 10.0) );

    FittingHelper::ObserveAndDraw *observer = new FittingHelper::ObserveAndDraw(canvas_name);
    fitSuite->attachObserver(observer);

    fitSuite->runFit();

    for(FitSuite::fitparameters_t::iterator it = fitSuite->fitparams_begin(); it!=fitSuite->fitparams_end(); ++it) {
        std::cout << (*it) << std::endl;

    }

}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::initializeExperiment(const OutputData<double> *output_data)
{
    delete m_experiment;
    initializeSample();

    m_experiment = new GISASExperiment();
    m_experiment->setSample( m_sample );
    m_experiment->setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    m_experiment->setBeamIntensity(1e10);

    if( !output_data ) {
        // initialize default detector
        m_experiment->setDetectorParameters(200, 0.3*Units::degree, 0.073, 200, -0.4*Units::degree, 0.066);
    } else {
        // if there is output_data as input parameter, build detector using output_data axises
        const NamedVector<double> *axis0 = reinterpret_cast<const NamedVector<double>*>(output_data->getAxes()[0]);
        const NamedVector<double> *axis1 = reinterpret_cast<const NamedVector<double>*>(output_data->getAxes()[1]);

        m_experiment->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());
    }
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::initializeSample()
{
    delete m_sample;
    // create mesocrystal
    double meso_width = 1000*Units::nanometer;
    double surface_filling_ratio = 0.25;
    double surface_density = surface_filling_ratio/M_PI/meso_width/meso_width;
//    complex_t n_particle(1.0-1.55e-5, 1.37e-6); // data from Artur
    complex_t n_particle(1.0-2.84e-5, 4.7e-7); // data from http://henke.lbl.gov/optical_constants/getdb2.html
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(surface_filling_ratio*avg_n_squared_meso + 1.0 - surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    FormFactorCylinder ff_cyl(0.5*Units::micrometer, meso_width);
    double sigma_h = 4*Units::nanometer;
    double sigma_r = 50*Units::nanometer;
    FormFactorDecoratorDebyeWaller ff_meso(ff_cyl.clone(), sigma_h*sigma_h/2.0, sigma_r*sigma_r/2.0);

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
    avg_layer.setThickness(0.5*Units::micrometer);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
    ParticleDecoration particle_decoration;
    size_t n_max_phi_rotation_steps = 180;
    size_t n_alpha_rotation_steps = 1;

    double alpha_step = 5.0*Units::degree/n_alpha_rotation_steps;
    double alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step;

    // with optimization
//    TRange<double> phi_range(0.0, 2.0*M_PI/3.0);
//    TRange<double> z_range(0.0, 2.6);
//    double max_rho = 2.6;
//    std::vector<double> phi_angles = createLattice(6.1*Units::nanometer)->collectBraggAngles(n_max_phi_rotation_steps, max_rho, phi_range, z_range);
//    for (size_t i=0; i<phi_angles.size(); ++i) {
//        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
//            Geometry::RotateZ3D transform1(phi_angles[i]);
//            Geometry::RotateY3D transform2(alpha_start + j*alpha_step);
//            Geometry::Transform3D *p_total_transform = new Geometry::Transform3D(transform1*transform2);
//            particle_decoration.addParticle(createMesoCrystal(6.1*Units::nanometer,
//                    n_particle_adapted, &ff_meso), p_total_transform, 0.2*Units::micrometer);
//        }
//    }
    // without
    double phi_step = 2.0*M_PI/3.0/n_max_phi_rotation_steps;
    double phi_start = 0.0;
    for (size_t i=0; i<n_max_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
            Geometry::RotateZ3D transform1(phi_start + (double)i*phi_step);
            Geometry::RotateY3D transform2(alpha_start + j*alpha_step);
            Geometry::Transform3D *p_total_transform = new Geometry::Transform3D(transform1);
            particle_decoration.addParticle(createMesoCrystal(4.7*Units::nanometer,
                    n_particle_adapted, &ff_meso), p_total_transform, 0.5*Units::micrometer);
        }
    }

    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator avg_layer_decorator(avg_layer, particle_decoration);

    LayerRoughness roughness(2.0*Units::nanometer, 0.3, 500.0*Units::nanometer);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer_decorator);
    p_multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

//    LayerDecorator air_decorator(air_layer, particle_decoration);
//    p_multi_layer->addLayer(air_decorator);
//    p_multi_layer->addLayer(substrate_layer);


    m_sample = p_multi_layer;

    std::cout << "Average layer index: " << n_avg << std::endl;
    std::cout << "Adapted particle index: " << n_particle_adapted << std::endl;
    std::cout << "Substrate layer index: " << n_substrate << std::endl;
}

MesoCrystal* TestMesoCrystal2::createMesoCrystal(double stacking_radius, complex_t n_particle, const IFormFactor* p_meso_form_factor)
{
    const Lattice *p_lat = createLattice(stacking_radius);
    kvector_t bas_a = p_lat->getBasisVectorA();
    kvector_t bas_b = p_lat->getBasisVectorB();
    kvector_t bas_c = p_lat->getBasisVectorC();
    double sigma = 0.2*Units::nanometer;
    Particle particle(n_particle, new FormFactorSphereGaussianRadius(stacking_radius-0.5*Units::nanometer, sigma));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);

    Crystal npc(basis, *p_lat);
//    double relative_sigma_np_radius = 0.3;
//    double dw_factor = relative_sigma_np_radius*relative_sigma_np_radius*stacking_radius*stacking_radius/6.0;
//    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}

const Lattice *TestMesoCrystal2::createLattice(double stacking_radius) {
    Lattice *p_result = new Lattice(Lattice::createTrigonalLattice(stacking_radius*2.0, stacking_radius*2.0*2.3));
    p_result->setSelectionRule(new SimpleSelectionRule(-1, 1, 1, 3));
    return p_result;
}





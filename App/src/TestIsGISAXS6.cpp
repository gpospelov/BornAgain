#include "TestIsGISAXS6.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "Simulation.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"
#include "StochasticDoubleGate.h"
#include "StochasticSampledParameter.h"
#include "MaterialManager.h"
#include "Lattice2DIFParameters.h"
#include "InterferenceFunction2DLattice.h"
#include "ParticleDecoration.h"
#include "FormFactorCylinder.h"
#include "PositionParticleInfo.h"
#include "LayerDecorator.h"

#include "TCanvas.h"
#include <gsl/gsl_errno.h>


TestIsGISAXS6::TestIsGISAXS6() : IFunctionalTest("TestIsGISAXS6")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-6/");
}

void TestIsGISAXS6::execute()
{
    gsl_set_error_handler_off();

    Simulation simulation(mp_options);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation.setSimulationParameters(sim_params);

    // normal lattice
    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_lattice"));
    simulation.setSample(*p_sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), m_data_path+"this_lattice.ima");
    delete p_sample;

    // centered lattice
    p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_centered"));
    simulation.setSample(*p_sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), m_data_path+"this_centered.ima");
    delete p_sample;

    // rotated lattice
    p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_rotated"));
    simulation.setSample(*p_sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), m_data_path+"this_rotated.ima");
    delete p_sample;

    // lattice variants
    OutputData<double> *p_total = simulation.getOutputDataClone();
    p_total->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticSampledParameter xi(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max);
    for (size_t i=0; i<xi.getNbins(); ++i) {
        double xi_value = xi.getBinValue(i);
        double probability = xi.getNormalizedProbability(i);
        m_builder.setXi(xi_value);
        p_sample = dynamic_cast<MultiLayer *>(m_builder.buildSample());
        simulation.setSample(*p_sample);
        simulation.runSimulation();
        delete p_sample;
        OutputData<double> *p_single_output = simulation.getOutputDataClone();
        p_single_output->scaleAll(probability);
        *p_total += *p_single_output;
        delete p_single_output;
    }
    OutputDataIOFactory::writeOutputData(*p_total, m_data_path+"this_variants.ima");
    delete p_total;
}


void TestIsGISAXS6::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgi_lattice.ima.gz",      "this_lattice.ima",      "Cylinder 2D lattice") );
    tocompare.push_back( CompareStruct("isgi_centered.ima.gz",      "this_centered.ima",      "Cylinder 2D lattice centered") );
    tocompare.push_back( CompareStruct("isgi_rotated.ima.gz",      "this_rotated.ima",      "Cylinder 2D lattice rotated") );
    tocompare.push_back( CompareStruct("isgi_variants.ima.gz",      "this_variants.ima",      "Cylinder 2D lattice variants") );

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].isginame);
        OutputData<double> *our_data = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].thisname);

        std::ostringstream os;
        os<<i;
        std::string cname = getName()+"_c"+os.str();
        TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas(cname.c_str(), tocompare[i].descr);
        c1->Divide(2,2);

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our lattice IF");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs lattice IF");

        // difference
        c1->cd(3);
        IsGISAXSTools::setMinimum(-0.0001);
        IsGISAXSTools::setMaximum(0.0001);
        IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

        // difference
        c1->cd(4);
        IsGISAXSTools::resetMinimumAndMaximum();
        //IsGISAXSTools::setMinimum(1);
        IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
        delete isgi_data;
        delete our_data;
    }
}

// IsGISAXS6 functional test sample builder for varying xi angle
ISample* TestIsGISAXS6::LatticeVariantBuilder::buildSample() const
{
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
    Lattice2DIFParameters lattice_params = {
            10.0*Units::nanometer,       // L1
            10.0*Units::nanometer,       // L2
            90.0*Units::degree,          // lattice angle
            m_xi,           // lattice orientation
            20000.0*Units::nanometer,    // domain size 1
            20000.0*Units::nanometer,    // domain size 2
            300.0*Units::nanometer/2.0/M_PI, // correlation length 1
            100.0*Units::nanometer/2.0/M_PI  // correlation length 2
    };
    InterferenceFunction2DLattice *p_interference_function = new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleDecoration particle_decoration;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info( new Particle(n_particle, ff_cyl.clone()), 0, position, 1.0);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

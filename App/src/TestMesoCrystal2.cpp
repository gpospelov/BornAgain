#include "TestMesoCrystal2.h"
#include "TestMesoCrystal1.h"
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
#include "FitSuiteHelper.h"

#include "TCanvas.h"
#include "TH2D.h"

/* ************************************************************************* */
// global functions
/* ************************************************************************* */
namespace {
    double testResolutionFunction(double u, double v)
    {
        double sigma_u = 0.0002;
        double sigma_v = 0.0002;
        return MathFunctions::IntegratedGaussian(u, 0.0, sigma_u)
                * MathFunctions::IntegratedGaussian(v, 0.0, sigma_v);
    }
}

/* ************************************************************************* */
// TestMesoCrystal2 member definitions
/* ************************************************************************* */
TestMesoCrystal2::TestMesoCrystal2()
: mp_sample_builder(0)
, mp_experiment(0)
{
    mp_sample_builder = new MesoCrystalBuilder;
}


TestMesoCrystal2::~TestMesoCrystal2()
{
    delete mp_sample_builder;
    delete mp_experiment;
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
    OutputData<double > *real_data_half = doubleBinSize(*real_data);
    OutputData<double > *real_data_quarter = doubleBinSize(*real_data_half);
    OutputData<double > *real_data_eighth = doubleBinSize(*real_data_quarter);
    delete reader;
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*real_data_quarter, "CONT4 Z", "experiment");
    c1->Update();

    // initializing experiment using real data to have detector axises like in real_data
    initializeExperiment(real_data_quarter);
    mp_experiment->printParameters();

    // setting fitSuite
    FitSuite *fitSuite = new FitSuite();
    fitSuite->setExperiment(mp_experiment);
    fitSuite->setRealData(*real_data_quarter);
    fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiMin", "ConjugateFR") );
    fitSuite->addFitParameter("*/lattice_length_a", 6.2*Units::nanometer, 1.0*Units::nanometer,
            TRange<double>(4.0*Units::nanometer, 8.0*Units::nanometer) );
    fitSuite->addFitParameter("*/nanoparticle_radius", 5.7*Units::nanometer, 1.0*Units::nanometer,
            TRange<double>(2.0*Units::nanometer, 8.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer, 0.05*Units::nanometer,
            TRange<double>(0.01*Units::nanometer, 2.0*Units::nanometer) );
    fitSuite->addFitParameter("*/meso_height", 500.0*Units::nanometer, 100.0*Units::nanometer,
            TRange<double>(100.0*Units::nanometer, 2000.0*Units::nanometer) );
    fitSuite->addFitParameter("*/meso_radius", 1000.0*Units::nanometer, 100.0*Units::nanometer,
            TRange<double>(100.0*Units::nanometer, 5000.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_meso_height", 5.0*Units::nanometer, 1.0*Units::nanometer,
            TRange<double>(10.0*Units::nanometer, 200.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_meso_radius", 50.0*Units::nanometer, 10.0*Units::nanometer,
            TRange<double>(10.0*Units::nanometer, 500.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_lattice_length_a", 1.5*Units::nanometer, 0.5*Units::nanometer,
            TRange<double>(0.01*Units::nanometer, 4.0*Units::nanometer) );
    fitSuite->addFitParameter("*/surface_filling_ratio", 0.25, 0.1,
            TRange<double>(0.1, 0.4) );
    fitSuite->addFitParameter("*/roughness", 1.0*Units::nanometer, 0.1*Units::nanometer,
            TRange<double>(0.01*Units::nanometer, 50.0*Units::nanometer) );

    IsGISAXSTools::setMinimum(1e2);
//    FitSuiteObserverWriteTree *writeTreeObserver = new FitSuiteObserverWriteTree("~/fitmeso003.tree");
//    fitSuite->attachObserver(writeTreeObserver);
    FitSuiteObserverDraw *drawObserver = new FitSuiteObserverDraw(canvas_name);
    fitSuite->attachObserver(drawObserver);

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
    delete mp_experiment;

    mp_experiment = new GISASExperiment();
    mp_experiment->setSampleBuilder( mp_sample_builder );
    mp_experiment->setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    mp_experiment->setBeamIntensity(8e12);
    mp_experiment->setDetectorResolutionFunction(&testResolutionFunction);

    if( !output_data ) {
        // initialize default detector
        mp_experiment->setDetectorParameters(200, 0.3*Units::degree, 0.073, 200, -0.4*Units::degree, 0.066);
    } else {
        // if there is output_data as input parameter, build detector using output_data axises
        const NamedVector<double> *axis0 = reinterpret_cast<const NamedVector<double>*>(output_data->getAxes()[0]);
        const NamedVector<double> *axis1 = reinterpret_cast<const NamedVector<double>*>(output_data->getAxes()[1]);

        mp_experiment->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());
    }
}

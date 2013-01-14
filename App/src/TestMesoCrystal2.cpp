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
#include "TRange.h"
#include "FitSuiteHelper.h"
#include "AttLimits.h"
#include "ProgramOptions.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "ResolutionFunction2DSimple.h"

/* ************************************************************************* */
// global functions
/* ************************************************************************* */

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
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("c1_test_meso_crystal", "mesocrystal");
    c1->cd(); gPad->SetLogz();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    IsGISAXSTools::setMinimum(100.);
    IsGISAXSTools::setMaximum(1e7);

    // reading data file
    //std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_qyqz.txt.gz";
    std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_phitheta.txt.gz";
    OutputDataReader *reader = OutputDataIOFactory::instance().getReader(file_name);
    OutputData<double > *real_data = reader->getOutputData();
    delete reader;
//    OutputData<double > *real_data_half = doubleBinSize(*real_data);
//    OutputData<double > *real_data_quarter = doubleBinSize(*real_data_half);
//    OutputData<double > *real_data_eighth = doubleBinSize(*real_data_quarter);
    IsGISAXSTools::drawOutputDataInPad(*real_data, "CONT4 Z", "experiment");
//    IsGISAXSTools::drawOutputDataInPad(*real_data_quarter, "CONT4 Z", "experiment");
    c1->Update();

    // initializing experiment using real data to have detector axises like in real_data
    initializeExperiment(real_data);
    mp_experiment->printParameters();

    // setting fitSuite
    FitSuite *fitSuite = new FitSuite();
//    fitSuite->setExperiment(mp_experiment);
//    fitSuite->setRealData(*real_data);
    fitSuite->addExperimentAndRealData(*mp_experiment, *real_data);
//    fitSuite->addExperimentAndRealData(mp_experiment, real_data_quarter);

    fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Combined") );
    ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(fitSuite->getMinimizer()))->getROOTMinimizer();
    minim->SetStrategy(2); // 0- not accurate, 1 - normal, 2 - acurate (maximum FCN calls)

    fitSuite->addFitParameter("*/lattice_length_a", 6.2*Units::nanometer, 1.0*Units::nanometer,
            AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    fitSuite->addFitParameter("*/nanoparticle_radius", 5.7*Units::nanometer, 1.0*Units::nanometer,
            AttLimits::limited(2.0*Units::nanometer, 8.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer, 0.05*Units::nanometer,
            AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    fitSuite->addFitParameter("*/meso_height", 500.0*Units::nanometer, 100.0*Units::nanometer,
            AttLimits::limited(100.0*Units::nanometer, 2000.0*Units::nanometer) );
    fitSuite->addFitParameter("*/meso_radius", 1000.0*Units::nanometer, 100.0*Units::nanometer,
            AttLimits::limited(100.0*Units::nanometer, 5000.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_meso_height", 5.0*Units::nanometer, 1.0*Units::nanometer,
            AttLimits::limited(10.0*Units::nanometer, 200.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_meso_radius", 50.0*Units::nanometer, 10.0*Units::nanometer,
            AttLimits::limited(10.0*Units::nanometer, 500.0*Units::nanometer) );
    fitSuite->addFitParameter("*/sigma_lattice_length_a", 1.5*Units::nanometer, 0.5*Units::nanometer,
            AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    fitSuite->addFitParameter("*/surface_filling_ratio", 0.25, 0.1,
            AttLimits::limited(0.1, 0.4) );
    fitSuite->addFitParameter("*/roughness", 1.0*Units::nanometer, 0.1*Units::nanometer,
            AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    fitSuite->addFitParameter("*Beam/intensity", 8e12, 100, AttLimits::limited(8e11, 8e13) );
//    fitSuite->addFitParameter("*/ResolutionFunction2D/sigma_x", 0.0002, 0.00001,
//            AttLimits::limited(0.0, 0.002) );
//    fitSuite->addFitParameter("*/ResolutionFunction2D/sigma_y", 0.0002, 0.00001,
//            AttLimits::limited(0.0, 0.002) );


//    // decrease number of bins in fit
//    FitSuiteStrategyAdjustData *strategy0 = new FitSuiteStrategyAdjustData(3);
//    strategy0->setCallMinimize(false);
//    strategy0->setPreserveOriginalData(false);
//    fitSuite->addFitStrategy(strategy0);

    typedef std::vector<std::string > parnames_t;
    std::vector<parnames_t > fixplan;

    parnames_t pars;
    pars.clear(); pars.push_back("*/lattice_length_a"); pars.push_back("*/nanoparticle_radius"); fixplan.push_back(pars);
    pars.clear(); pars.push_back("*/meso_height"); pars.push_back("*/meso_radius"); fixplan.push_back(pars);
    pars.clear(); pars.push_back("*Beam/intensity"); fixplan.push_back(pars);
    pars.clear(); pars.push_back("*/surface_filling_ratio"); fixplan.push_back(pars);
    pars.clear(); pars.push_back("*/roughness"); fixplan.push_back(pars);
    pars.clear(); pars.push_back("*/sigma_lattice_length_a"); pars.push_back("*/sigma_nanoparticle_radius"); fixplan.push_back(pars);
    pars.clear(); pars.push_back("*/sigma_meso_height"); pars.push_back("*/sigma_meso_radius"); fixplan.push_back(pars);

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitSuiteStrategyAdjustParameters *strategy = new FitSuiteStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        int fitmode  = (*mp_options)["fitmode"].as<int>();
        if(fitmode==1) {
            strategy->setPreserveOriginalValues(true); // initial values of parameters will be restored after each fit
        } else {
            strategy->setPreserveOriginalValues(false);
        }

        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        fitSuite->addFitStrategy(strategy);
    }
    FitSuiteStrategyAdjustParameters *strategy_all = new FitSuiteStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    fitSuite->addFitStrategy(strategy_all);



//    // Applying fit strategy: fixing/releasing parameters
//    FitSuiteStrategyAdjustParameters *strategy1 = new FitSuiteStrategyAdjustParameters("strategy1");
//    strategy1->fix_all().release("*/lattice_length_a").release("*/nanoparticle_radius");
//    strategy1->setPreserveOriginalValues(true);
//    fitSuite->addFitStrategy(strategy1);

//    FitSuiteStrategyAdjustParameters *strategy2 = new FitSuiteStrategyAdjustParameters("strategy2");
//    strategy2->fix_all().release("*/sigma_lattice_length_a").release("*/sigma_nanoparticle_radius");
//    fitSuite->addFitStrategy(strategy2);

//    FitSuiteStrategyAdjustParameters *strategy3 = new FitSuiteStrategyAdjustParameters("strategy3");
//    strategy3->fix_all().release("*/meso_height").release("*/meso_radius").release("*/roughness");
//    fitSuite->addFitStrategy(strategy3);

//    FitSuiteStrategyAdjustParameters *strategy4 = new FitSuiteStrategyAdjustParameters("strategy4");
//    strategy4->fix_all().release("*Beam/intensity");
//    fitSuite->addFitStrategy(strategy4);

//    FitSuiteStrategyAdjustParameters *strategy5 = new FitSuiteStrategyAdjustParameters("strategy5");
//    strategy5->fix_all().release("*/sigma_meso_height").release("*/sigma_meso_radius");
//    fitSuite->addFitStrategy(strategy5);

//    FitSuiteStrategyAdjustParameters *strategy6 = new FitSuiteStrategyAdjustParameters("strategy6");
//    strategy6->release_all();
//    fitSuite->addFitStrategy(strategy6);


//    IsGISAXSTools::setMinimum(1e2);
//    std::string tree_file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/mesofit.tree";
//    FitSuiteObserverWriteTree *writeTreeObserver = new FitSuiteObserverWriteTree(tree_file_name);
//    fitSuite->attachObserver(writeTreeObserver);
//    FitSuiteObserverDraw *drawObserver = new FitSuiteObserverDraw(canvas_name);
//    fitSuite->attachObserver(drawObserver);

    fitSuite->attachObserver( new FitSuiteObserverPrint() );
    fitSuite->attachObserver( new FitSuiteObserverDraw() );
    fitSuite->attachObserver( new FitSuiteObserverWriteTree() );

    fitSuite->runFit();

    for(FitSuiteParameters::iterator it = fitSuite->getFitParameters()->begin(); it!=fitSuite->getFitParameters()->end(); ++it) {
        std::cout << (*it) << std::endl;
    }
}

/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::initializeExperiment(const OutputData<double> *output_data)
{
    delete mp_experiment;

    mp_experiment = new GISASExperiment(mp_options);
    mp_experiment->setSampleBuilder( mp_sample_builder );
    mp_experiment->setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    mp_experiment->setBeamIntensity(8e12);
    mp_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));

    if( !output_data ) {
        // initialize default detector
        mp_experiment->setDetectorParameters(200, 0.3*Units::degree, 0.073, 200, -0.4*Units::degree, 0.066);
    } else {
        // if there is output_data as input parameter, build detector using output_data axises
        const IAxis *axis0 = output_data->getAxis(0);
        const IAxis *axis1 = output_data->getAxis(1);
        //std::cout << axis0->getSize() << " " << axis0->getMin() << " " << axis0->getMax() << " " << axis1->getSize() << " " << axis1->getMin() << " " << axis1->getMax() << std::endl;
        mp_experiment->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());
    }
}

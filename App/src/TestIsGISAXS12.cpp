#include "TestIsGISAXS12.h"
#include "Utils.h"
#include "OutputData.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "MaterialManager.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "FormFactorCylinder.h"
#include "StochasticSampledParameter.h"
#include "ParticleBuilder.h"
#include "LayerDecorator.h"
#include "Units.h"
#include "StochasticGaussian.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "GISASExperiment.h"
#include "DrawHelper.h"
#include "FitSuite.h"
#include "FitSuiteHelper.h"
#include "ResolutionFunction2DSimple.h"
#include "MathFunctions.h"
#include "ROOTMinimizer.h"
#include "OutputDataFunctions.h"
#include "NamedVector.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"



/* ************************************************************************* */
//
/* ************************************************************************* */
TestIsGISAXS12::TestIsGISAXS12() : IFunctionalTest("TestIsGISAXS12")
  , m_experiment(0)
  , m_sample_builder(0)
  , m_fitSuite(0)
  , m_isgi_fixed_alphaf(0)
  , m_isgi_fixed_phif(0)
{
    std::cout << "TestIsGISAXS12::TestIsGISAXS12() -> Info" << std::endl;
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/");
}


TestIsGISAXS12::~TestIsGISAXS12()
{
    delete m_experiment;
    delete m_sample_builder;
    delete m_fitSuite;
    for(DataScan_t::iterator it=m_isgi_scans.begin(); it!=m_isgi_scans.end(); ++it) {
        delete (*it);
    }
}


/* ************************************************************************* */
// execute
/* ************************************************************************* */
void TestIsGISAXS12::execute()
{

    // initializing experiment and sample builder
    initialiseExperiment();

    // run our standard isgisaxs comparison for given sample
    run_isgisaxs_comparison();

    // run test fit
    //run_test_fit();

    // run isgisaxs ex-12 style fit
    run_isgisaxs_fit();

}



/* ************************************************************************* */
// standard ixgisaxs comparison
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_comparison()
{
    // run simulation for default sample parameters
    m_experiment->runSimulation();
    IsGISAXSTools::writeOutputDataToFile(*(m_experiment->getOutputData()), m_data_path+"this_fitconstraints.ima");

    // plotting results of comparison we/isgisaxs for the sample with default parameters
    std::string isgi_file(m_data_path+"isgi_fitconstraints.ima");
    std::string this_file(m_data_path+"this_fitconstraints.ima");

    // -------------
    // plot results
    // -------------
    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_file);
    OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_file);

    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS12_c1", "ex-12: Mixture of cylindrical particles with different size distribution");

    c1->Divide(2,2);

    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "this");

    // isgisaxs data
    c1->cd(2); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "isgi");

    // difference
    c1->cd(3);
    IsGISAXSTools::setMinimum(-0.0001);
    IsGISAXSTools::setMaximum(0.0001);
    IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

    // difference
    c1->cd(4);
    IsGISAXSTools::resetMinimumAndMaximum();
    IsGISAXSTools::setMinimum(1);
    IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

    delete isgi_data;
    delete our_data;

}


/* ************************************************************************* */
// run test fitting
/* ************************************************************************* */
void TestIsGISAXS12::run_test_fit()
{
    // creating "real" data
    //m_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    m_experiment->setBeamIntensity(1e10);
    m_experiment->runSimulation();
    m_experiment->normalize();

    OutputData<double > *real_data = IsGISAXSTools::createNoisyData( *m_experiment->getOutputData() );

    // setting up 1d scans by making slices on real data
    DataScan_t data_scans;
    data_scans.push_back( OutputDataFunctions::selectRangeOnOneAxis(*real_data, "alpha_f", 0.012, 0.012) );
    data_scans.push_back( OutputDataFunctions::selectRangeOnOneAxis(*real_data, "phi_f", 0.011, 0.011) );

    // drawing data and scans
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,2);
    c1->cd(1); gPad->SetLogz();
    TH2D *hist1 = dynamic_cast<TH2D *>(IsGISAXSTools::getOutputDataTH123D( *real_data, "real_data"));
    hist1->Draw("COLZ");
    for(DataScan_t::const_iterator it=data_scans.begin(); it!= data_scans.end(); ++it) {
        TLine *line = IsGISAXSTools::getOutputDataScanLine(*(*it));
        line->DrawClone();
        delete line;
    }

    int npad(2);
    for(DataScan_t::iterator it=data_scans.begin(); it!= data_scans.end(); ++it, ++npad) {
        c1->cd(npad);
        TH1D *hist = IsGISAXSTools::getOutputDataScanHist(*(*it));
        hist->DrawCopy();
        delete hist;
    }
    c1->Update();

    // creating fit suite
    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );

//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.8*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.8*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  6*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability",  0.4, 0.1, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );

    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.3*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.3*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.7*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.7*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  10*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  5*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability",  0.4, 0.1, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  3*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  3*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );

    for(DataScan_t::iterator it=data_scans.begin(); it!= data_scans.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it));
    }

    m_fitSuite->runFit();

    delete real_data;
    for(DataScan_t::iterator it=data_scans.begin(); it!= data_scans.end(); ++it) delete (*it);
}


/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_fit()
{
    // reading info about two 1D scans defined in isgisaxs example
    read_isgisaxs_datfile(m_data_path+"isgi_fitconstraints.dat");

    // making some plots together with test simulation
    plot_isgisaxs_data();
//    return;

    // creating fit suite
    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiMin", "SteepestDescent") );
    m_fitSuite->attachObserver( new FitSuiteObserverPrint(10) );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw(50) );

    ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer()))->getROOTMinimizer();
    minim->SetStrategy(1);
//    minim->SetPrecision(1.);

    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 100, AttLimits::limited(1e4, 2e5));
    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 1, AttLimits::limited(1., 20.));
    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability",  0.4, 0.1, AttLimits::limited(0.01, 1.0) );

    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1., 10.) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.2, 0.1, AttLimits::limited(0.01, 1.) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.8, 0.1, AttLimits::limited(0.01, 10.) );

    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  4*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1., 10.) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.2, 0.1, AttLimits::limited(0.01, 1.) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.8, 0.1, AttLimits::limited(0.01, 10.) );

    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  12*Units::nanometer, 1*Units::nanometer, AttLimits::limited(0.01, 50.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  6*Units::nanometer, 1*Units::nanometer, AttLimits::limited(0.01, 10.) );

    // setting up fitSuite
    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
    chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift() );

    for(DataScan_t::iterator it=m_isgi_scans.begin(); it!= m_isgi_scans.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it), chiModule);
    }

    m_fitSuite->runFit();

    // drawing results
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    c2->Divide(2,2);
    for(size_t i=0; i<m_fitSuite->getFitObjects()->size(); ++i) {
        c2->cd(i+1);
        const FitObject *obj = m_fitSuite->getFitObjects()->getObject(i);
        TH1D *hreal = IsGISAXSTools::getOutputDataScanHist(*obj->getChiSquaredModule()->getRealData(),"real");
        TH1D *hsimul = IsGISAXSTools::getOutputDataScanHist(*obj->getChiSquaredModule()->getSimulationData(),"simul");
        hreal->SetLineColor(kBlue);
        gPad->SetLogy();
        hreal->DrawCopy();
        hsimul->DrawCopy("same");
        delete hreal;
        delete hsimul;
    }


}



/* ************************************************************************* */
// plot isgisaxs data together with test simulation
/* ************************************************************************* */
void TestIsGISAXS12::plot_isgisaxs_data()
{
    if(m_isgi_scans.size() != 2) throw LogicErrorException("TestIsGISAXS12::plot_isgisaxs_data() -> Load isgisaxs scans first");

    enum isgisaxs_scans {kFixedAlphaf, kFixedPhif };

    // making 2d OutputData with axes like in two isgisaxs scans
    OutputData<double > *data_as_isgisaxs = new OutputData<double>;
    const NamedVector<double > *axis_phif_scan = dynamic_cast<const NamedVector<double> *>(m_isgi_scans[kFixedAlphaf]->getAxis("phi_f"));
    const NamedVector<double > *axis_alphaf_scan = dynamic_cast<const NamedVector<double> *>(m_isgi_scans[kFixedPhif]->getAxis("alpha_f"));
    if( !axis_phif_scan || !axis_phif_scan ) throw NullPointerException("TestIsGISAXS12::plot_isgisaxs_data() -> Error. Can'get get axis");
    data_as_isgisaxs->addAxis(axis_phif_scan->clone());
    data_as_isgisaxs->addAxis(axis_alphaf_scan->clone());
    data_as_isgisaxs->setAllTo(0.0);
    std::cout << axis_phif_scan->getSize() << " " << axis_alphaf_scan->getSize() << " " << data_as_isgisaxs->getAllocatedSize() << std::endl;

    // running 2d simulation
    m_experiment->setDetectorParameters(*data_as_isgisaxs);
    delete data_as_isgisaxs;
//    m_experiment->setBeamIntensity(1e10);
    m_experiment->runSimulation();
//    m_experiment->normalize();

    // setting up 1d scans by making slices on just simulated data
    DataScan_t data_scans;
    data_scans.push_back( OutputDataFunctions::selectRangeOnOneAxis(*m_experiment->getOutputData(), "alpha_f", m_isgi_fixed_alphaf, m_isgi_fixed_alphaf  ));
    data_scans.push_back( OutputDataFunctions::selectRangeOnOneAxis(*m_experiment->getOutputData(), "phi_f", m_isgi_fixed_phif, m_isgi_fixed_phif ));

    // drawing data and scans
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,3);
    c1->cd(1); gPad->SetLogz();
    TH2D *hist1 = dynamic_cast<TH2D *>(IsGISAXSTools::getOutputDataTH123D( *m_experiment->getOutputData(), "real_data"));
    hist1->Draw("COLZ");
    for(DataScan_t::const_iterator it=data_scans.begin(); it!= data_scans.end(); ++it) {
        TLine *line = IsGISAXSTools::getOutputDataScanLine(*(*it));
        line->DrawClone();
        delete line;
    }
    int npad(3);
    for(DataScan_t::iterator it=data_scans.begin(); it!= data_scans.end(); ++it, ++npad) {
        c1->cd(npad);
        TH1D *hist = IsGISAXSTools::getOutputDataScanHist(*(*it), "sim");
        hist->DrawCopy();
        delete hist;
    }

    // drawing isgi scans
    npad=5;
    for(DataScan_t::iterator it=m_isgi_scans.begin(); it!= m_isgi_scans.end(); ++it, ++npad) {
        c1->cd(npad);
        TH1D *hist = IsGISAXSTools::getOutputDataScanHist(*(*it),"isgi");
        hist->SetLineColor(kBlue);
        hist->DrawCopy();
        delete hist;
    }
    c1->Update();

    for(DataScan_t::iterator it=data_scans.begin(); it!= data_scans.end(); ++it) delete (*it);
}


/* ************************************************************************* */
// initialize experiment
/* ************************************************************************* */
void TestIsGISAXS12::initialiseExperiment()
{
    delete m_sample_builder;
    m_sample_builder = new TestSampleBuilder();
    delete m_experiment;
    m_experiment = new GISASExperiment(mp_options);
    m_experiment->setSampleBuilder(m_sample_builder);
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
}




/* ************************************************************************* */
// read special isgisaxs *.dat file with data to fit
/* ************************************************************************* */
void TestIsGISAXS12::read_isgisaxs_datfile(const std::string &filename)
{
    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    std::vector<IsgiData > isgiScan;

    std::string sline;
    int n_dataset_line(0);
    while( std::getline(fin, sline))
    {
        //std::cout << sline << std::endl;
        std::string::size_type pos=sline.find("################################################");
        if( pos!= std::string::npos ) {
            n_dataset_line = 0; // it's a beginning of new data set ("cross-section" in isgisaxs terminology)
            if( !isgiScan.empty() ) {
                OutputData<double > *data = convert_isgi_scan(isgiScan);
                m_isgi_scans.push_back(data);
                std::cout << "YYY " << isgiScan.size() << std::endl;
                isgiScan.clear();
            }
        }
        if(n_dataset_line > 9) {
            // not a header, parsing records
            std::istringstream iss(sline.c_str());
            IsgiData isgiData;
            char ctmp;
            if ( !(iss >> ctmp >> isgiData.phif >> isgiData.alphaf >> isgiData.intensity) ) throw FormatErrorException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error!");
            iss >> isgiData.err; // column with errors can be absent in file, so no check for success here
            ctmp == 'T' ? isgiData.use_it = true : isgiData.use_it = false;
            if(isgiData.phif > .0001) {
                isgiData.phif = std::asin(isgiData.phif); // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
                isgiData.alphaf = std::asin(isgiData.alphaf);  // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
                isgiScan.push_back(isgiData);
            }
        }

        n_dataset_line++;
    }
    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

}


/* ************************************************************************* */
// convert isgisaxs 1d scan to output data 2d object
/* ************************************************************************* */
OutputData<double> *TestIsGISAXS12::convert_isgi_scan(std::vector<IsgiData > &isgi_data)
{
    if(isgi_data.size() <2 ) throw LogicErrorException("TestIsGISAXS12::convert_isgi_scan() -> Error! Too short vector.");

    // check if it is scan with fixed phi_f or with fixed alpha_f
    bool fixed_phif(true);
    bool fixed_alphaf(true);
    // if values of phif accross data points are chainging, then phif is not fixed
    for(size_t i_point=0; i_point<isgi_data.size()-1; ++i_point) {
        if( isgi_data[i_point].phif != isgi_data[i_point+1].phif ) {
            fixed_phif = false;
            break;
        }
    }
    // if values of alphaf accross data points are chainging, then alphaf is not fixed
    for(size_t i_point=0; i_point<isgi_data.size()-1; ++i_point) {
        if( isgi_data[i_point].alphaf != isgi_data[i_point+1].alphaf ) {
            fixed_alphaf = false;
            break;
        }
    }
    if(fixed_phif == fixed_alphaf) {
        throw LogicErrorException("TestIsGISAXS12::convert_isgi_scan() -> Error! Scan can't have both angle phif,alphaf fixed");
    }

    NamedVector<double> *phi_axis = new NamedVector<double>("phi_f");
    NamedVector<double> *alpha_axis = new NamedVector<double>("alpha_f");
    if( fixed_phif) {
        m_isgi_fixed_phif = isgi_data.back().phif;
        phi_axis->push_back(isgi_data.back().phif);
        std::cout << "fixed phi " << isgi_data.back().phif << std::endl;
        for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
            alpha_axis->push_back(isgi_data[i_point].alphaf);
        }
    }else {
        m_isgi_fixed_alphaf = isgi_data.back().alphaf;
        alpha_axis->push_back(isgi_data.back().alphaf);
        for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
            phi_axis->push_back(isgi_data[i_point].phif);
        }

    }
    OutputData<double > * data = new OutputData<double >;
    data->addAxis(phi_axis);
    data->addAxis(alpha_axis);
    data->setAllTo(0.0);
    OutputData<double>::iterator it = data->begin();
    int i_point(0);
    while( it!= data->end()) {
        (*it) = isgi_data[i_point].intensity;
        ++i_point;
        ++it;
    }

    return data;
}


/* ************************************************************************* */
//
/* ************************************************************************* */
TestIsGISAXS12::TestSampleBuilder::TestSampleBuilder()
    : m_particle_probability(0.4)
    , m_particle_radius1(4*Units::nanometer)
    , m_particle_radius2(4*Units::nanometer)
    , m_dispersion_radius1(0.2)
    , m_dispersion_radius2(0.2)
    , m_height_aspect_ratio1(0.8)
    , m_height_aspect_ratio2(0.8)
    , m_interf_distance(12.0*Units::nanometer)
    , m_interf_width(6*Units::nanometer)
{
    init_parameters();
}

void TestIsGISAXS12::TestSampleBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("particle_probability", &m_particle_probability);
    getParameterPool()->registerParameter("particle_radius1", &m_particle_radius1);
    getParameterPool()->registerParameter("particle_radius2", &m_particle_radius2);
    getParameterPool()->registerParameter("dispersion_radius1", &m_dispersion_radius1);
    getParameterPool()->registerParameter("dispersion_radius2", &m_dispersion_radius2);
    getParameterPool()->registerParameter("height_aspect_ratio1", &m_height_aspect_ratio1);
    getParameterPool()->registerParameter("height_aspect_ratio2", &m_height_aspect_ratio2);
    getParameterPool()->registerParameter("interf_distance", &m_interf_distance);
    getParameterPool()->registerParameter("interf_width", &m_interf_width);
}


/* ************************************************************************* */
//
/* ************************************************************************* */
ISample *TestIsGISAXS12::TestSampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);

    Layer air_layer(air_material);

    // preparing nano particles prototypes for seeding layer's particle_decoration
    double radius1 = m_particle_radius1;
    double radius2 = m_particle_radius2;
    double height1 = m_height_aspect_ratio1*radius1;
    double height2 = m_height_aspect_ratio2*radius2;
    FormFactorCylinder *p_ff_cylinder1 = new FormFactorCylinder(height1, radius1);
    Particle cylinder1(n_particle, p_ff_cylinder1 );

    FormFactorCylinder *p_ff_cylinder2 = new FormFactorCylinder(height2, radius2);
    Particle cylinder2(n_particle, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=20;
    double sigma1 = radius1*m_dispersion_radius1;
    double sigma2 = radius2*m_dispersion_radius2;
    int nfwhm(2); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    StochasticSampledParameter par1(StochasticDoubleGaussian(radius1, sigma1), nbins, nfwhm);
    StochasticSampledParameter par2(StochasticDoubleGaussian(radius2, sigma2), nbins, nfwhm);

    ParticleDecoration particle_decoration;
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(m_interf_distance, m_interf_width, 1e7*Units::nanometer); // peak_distance, width, corr_length
    particle_decoration.addInterferenceFunction(p_interference_function);

    // building nano particles
    ParticleBuilder builder;
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, m_particle_probability);
    builder.plantParticles(particle_decoration);
    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, 1-m_particle_probability);
    builder.plantParticles(particle_decoration);

    // making layer holding all whose nano particles
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);

    Layer substrate_layer;
    substrate_layer.setMaterial(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}







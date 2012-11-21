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
TestIsGISAXS12::TestIsGISAXS12() : IFunctionalTest("TestIsGISAXS12"), m_experiment(0), m_sample_builder(0), m_fitSuite(0)
{
    std::cout << "TestIsGISAXS12::TestIsGISAXS12() -> Info" << std::endl;
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/");
}


TestIsGISAXS12::~TestIsGISAXS12()
{
    delete m_experiment;
    delete m_sample_builder;
    delete m_fitSuite;
}


/* ************************************************************************* */
// execute
/* ************************************************************************* */
void TestIsGISAXS12::execute()
{
    // initializing experiment and sample builder
    initialiseExperiment();

    // run standard isgisaxs comparison for the sample we have
    //run_isgisaxs_comparison();

    // run test of our style fit
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
    m_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    m_experiment->setBeamIntensity(1e10);
    m_experiment->runSimulation();
    m_experiment->normalize();
    OutputData<double > *test_real_data = createNoisyData( *m_experiment->getOutputData() );

    // creating fit suite
    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );

    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.8*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.8*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  6*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );

    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );

    m_fitSuite->addExperimentAndRealData(m_experiment, test_real_data);

    m_fitSuite->runFit();

    delete test_real_data;
}


/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_fit()
{
    //    read_isgisaxs_datfile(m_data_path+"isgi_fitconstraints.dat");

    // run simulation for default sample parameters
    m_experiment->runSimulation();

    TCanvas *c2 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS12_c2", "ex-12: Mixture of cylindrical particles with different size distribution");

    c2->Divide(2,2);

    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c2->cd(1); gPad->SetLogz();
    TH2D *hist1 = dynamic_cast<TH2D* >(IsGISAXSTools::getOutputDataTH123D(*m_experiment->getOutputData(), "hist1"));
    hist1->SetMinimum(1.0);
    hist1->Draw("CONT4 Z");

    OutputData<double > *sliced_data = IsGISAXSTools::sliceOutputData(*m_experiment->getOutputData(), "phi_f", 0.01);
    std::cout << "XXX " << sliced_data->getAllocatedSize() << std::endl;
    c2->cd(2);
    TH1D *hist2 = dynamic_cast<TH1D* >(IsGISAXSTools::getOutputDataTH123D(*sliced_data, "hist2"));
    hist2->SetMinimum(1.0);
    hist2->Draw();

    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );

    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.8*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.8*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  6*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );

    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );

    m_fitSuite->addExperimentAndRealData(m_experiment, sliced_data);

    m_fitSuite->runFit();


}



/* ************************************************************************* */
//
/* ************************************************************************* */
void TestIsGISAXS12::finalise()
{
    return;
    // ----------------------------------------------------------
    // plotting isgisaxs "experimental data" together with projections of our output_data for default sample parameters
    TCanvas *c2 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS12_c2", "ex-12: experimental data to fit");
    c2->Divide(2,2);

    // drawing projection of output data (calculated for initial parameter values) on top of isgisaxs experimental data
    TH2D *h2_data = IsGISAXSTools::getOutputDataTH2D(*(m_experiment->getOutputData()),"h2_our_data");
    c2->cd(1);
    gPad->SetLogz();
    h2_data->SetMinimum(1.);
    h2_data->Draw("colz");
    TLine line;
    line.SetLineColor(kRed);
    line.SetLineStyle(1);
    line.SetLineWidth(2);
    for(size_t i_scan=0; i_scan<m_isgiCrossSections.size(); ++i_scan) {
        IsgiScan &scan = m_isgiCrossSections[i_scan];
        if( scan.fixed_alphaf ) {
            double x1 = h2_data->GetXaxis()->GetXmin();
            double x2 = h2_data->GetXaxis()->GetXmax();
            double y = scan.getFixedAngle();
            line.DrawLine(x1,y,x2,y);
            std::cout << "line fixed_alphaf " << x1 << " " << y << " " << x2 << " " << y << std::endl;
        }else if( scan.fixed_phif ) {
            double x = scan.getFixedAngle();
            double y1 = h2_data->GetYaxis()->GetXmin();
            double y2 = h2_data->GetYaxis()->GetXmax();
            line.DrawLine(x,y1,x,y2);
            std::cout << "line fixed_phif " << x << " " << y1 << " " << x << " " << y2 << std::endl;
        } else {
            throw LogicErrorException("TestIsGISAXS12::finalise() -> Error.");
        }

    }


    for(size_t i_scan=0; i_scan<m_isgiCrossSections.size(); ++i_scan) {
        c2->cd(3+i_scan); gPad->SetLogy();
        IsgiScan &scan = m_isgiCrossSections[i_scan];

        // drawing isgisaxs experimental data
        TGraph *gr = new TGraph(scan.size());
        for(size_t i_point=0; i_point < scan.size(); ++i_point) {

            gr->SetPoint(i_point, scan.getAngle(i_point), scan.getIntensity(i_point) );
        }
        gr->Draw("apl");
        std::ostringstream ostr;
        if(scan.fixed_phif) ostr << "fixed_phif at " << scan.getFixedAngle();
        if(scan.fixed_alphaf) ostr << "fixed_alphaf at " << scan.getFixedAngle();
        gr->SetTitle(ostr.str().c_str());

        TH1D *hprojection(0);
        if( scan.fixed_alphaf ) {
            double alphaf_fixed = scan.getFixedAngle();
            int biny = h2_data->GetYaxis()->FindBin(alphaf_fixed);
            std::cout << "fixed alphaf: " << alphaf_fixed << " biny:" << biny << std::endl;
            hprojection = h2_data->ProjectionX("fixed_alphaf",biny,biny); // along binx
        }else if( scan.fixed_phif ) {
            double phif_fixed = scan.getFixedAngle();
            int binx = h2_data->GetXaxis()->FindBin(phif_fixed);
            std::cout << "fixed phif: " << phif_fixed << " binx:" << binx << std::endl;
            hprojection = h2_data->ProjectionY("fixed_phif",binx,binx); // along binx
        } else {
            throw LogicErrorException("TestIsGISAXS12::finalise() -> Error.");

        }
        hprojection->SetLineColor(kBlue);
        hprojection->Draw("same");
    }



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
    // no resolution function defined yet, since we want to run comparison with isgisaxs fitst
}


/* ************************************************************************* */
// add noise to data
/* ************************************************************************* */
OutputData<double > *TestIsGISAXS12::createNoisyData(const OutputData<double> &exact_data, double noise_factor)
{
    OutputData<double > *real_data = exact_data.clone();

    OutputData<double>::iterator it = real_data->begin();
    while (it != real_data->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        *it = random;
        ++it;
    }

    return real_data;
}


/* ************************************************************************* */
// read special isgisaxs *.dat file with data to fit
/* ************************************************************************* */
void TestIsGISAXS12::read_isgisaxs_datfile(const std::string &filename)
{
    m_isgiCrossSections.clear();

    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    IsgiScan isgiScan; // one isgisaxs scan from *.dat file

    std::string sline;
    int n_dataset_line(0);
    while( std::getline(fin, sline))
    {
        //std::cout << sline << std::endl;
        std::string::size_type pos=sline.find("################################################");
        if( pos!= std::string::npos ) {
            n_dataset_line = 0; // it's a beginning of new data set ("cross-section" in isgisaxs terminology)
            if( !isgiScan.isgiDataVector.empty() ) {
                m_isgiCrossSections.push_back(isgiScan);
                isgiScan.isgiDataVector.clear();
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
            isgiData.phif = std::asin(isgiData.phif); // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
            isgiData.alphaf = std::asin(isgiData.alphaf);  // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
            isgiScan.isgiDataVector.push_back(isgiData);
        }

        n_dataset_line++;
    }
    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

    // let's understand which scan has which parameter fixed
    for(size_t i_scan=0; i_scan<m_isgiCrossSections.size(); ++i_scan){
        IsgiScan &scan = m_isgiCrossSections[i_scan];
        scan.fixed_phif = scan.fixed_alphaf = true;
        // if values of phif accross data points are chainging, then phif is not fixed
        for(size_t i_point=0; i_point<scan.isgiDataVector.size()-1; ++i_point) {
            if( scan.isgiDataVector[i_point].phif != scan.isgiDataVector[i_point+1].phif ) {
                scan.fixed_phif = false;
                break;
            }
        }
        // if values of alphaf accross data points are chainging, then alphaf is not fixed
        for(size_t i_point=0; i_point<scan.isgiDataVector.size()-1; ++i_point) {
            if( scan.isgiDataVector[i_point].alphaf != scan.isgiDataVector[i_point+1].alphaf ) {
                scan.fixed_alphaf = false;
                break;
            }
        }
        if(scan.fixed_phif == scan.fixed_alphaf) {
            std::cout << " scan " << i_scan << " fixed_phif " << scan.fixed_phif << " fixed_alphaf:" << scan.fixed_alphaf << std::endl;
            throw LogicErrorException("TestIsGISAXS12::read_isgisaxs_datfile -> Error. Scan can't have both angle phif,alphaf fixed");
        }
    }
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







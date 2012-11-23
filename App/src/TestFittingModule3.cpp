#include "TestFittingModule3.h"
#include "Units.h"
#include "MathFunctions.h"
#include "GISASExperiment.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "Particle.h"
#include "FormFactors.h"
#include "Exceptions.h"
#include "DrawHelper.h"
#include "FitSuiteHelper.h"
#include "ResolutionFunction2DSimple.h"
#include "AttLimits.h"
#include "OutputDataFunctions.h"
#include "TLine.h"
#include "NamedVector.h"

#include "IObserver.h"
#include "FitSuite.h"
#include "ROOTMinimizer.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TH2D.h"
#include "TPaveText.h"


TestFittingModule3::TestFittingModule3()
    : m_experiment(0)
    , m_sample(0)
    , m_fitSuite(0)
    , m_real_data(0)
{
}


TestFittingModule3::~TestFittingModule3()
{
    delete m_experiment;
    delete m_sample;
    delete m_real_data;
    for(DataScan_t::iterator it=m_data_scans.begin(); it!= m_data_scans.end(); ++it) delete (*it);
}


void TestFittingModule3::execute()
{
    // initializing experiment, sample and data
    initializeSample();
    initializeExperiment();
    initializeRealData();

    // setting up fitSuite
    m_fitSuite = new FitSuite();
    m_fitSuite->addFitParameter("*FormFactorCylinder/height", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*FormFactorCylinder/radius", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*FormFactorPrism3/half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*FormFactorPrism3/height", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorCylinder/height", 5.0001*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorCylinder/radius", 5.0001*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorPrism3/half_side", 5.0001*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorPrism3/height", 5.0001*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );

    // putting scans
    for(DataScan_t::iterator it=m_data_scans.begin(); it!= m_data_scans.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it));
    }

    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw(1) );

    m_fitSuite->runFit();

}


/* ************************************************************************* */
// initializing experiment
/* ************************************************************************* */
void TestFittingModule3::initializeExperiment()
{
    if( !m_sample ) {
        throw NullPointerException("TestFittingModule3::initializeExperiment() -> No sample defined");
    }
    delete m_experiment;
    m_experiment = new GISASExperiment(mp_options);
    m_experiment->setSample(*m_sample);
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,100 , 0.0*Units::degree, 2.0*Units::degree);
//    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 1, 0.01, 0.011);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    m_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    m_experiment->setBeamIntensity(1e10);

}


/* ************************************************************************* */
// initialize sample
/* ************************************************************************* */
void TestFittingModule3::initializeSample()
{
    delete m_sample;
    double cylinder_height = 5.0*Units::nanometer;
    double cylinder_radius = 5.0*Units::nanometer;
    double prism3_half_side = 5.0*Units::nanometer;
    double prism3_height = 5.0*Units::nanometer;
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
    ParticleDecoration particle_decoration;
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(cylinder_height, cylinder_radius)),0.0, 0.2);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(prism3_height, prism3_half_side)), 0.0, 0.8);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    m_sample = p_multi_layer;
}


/* ************************************************************************* */
// initializing real data
/* ************************************************************************* */
void TestFittingModule3::initializeRealData()
{
    if( !m_experiment || !m_sample ) throw NullPointerException("TestFittingModule3::initializeRealData() -> Error! No experiment o sample defined ");

    // generating 2D "real" data
    m_experiment->runSimulation();
    m_experiment->normalize();
    delete m_real_data;
    m_real_data = createNoisyData(*m_experiment->getOutputData());

    // setting up 1d scans by making slices on real data
    for(DataScan_t::iterator it=m_data_scans.begin(); it!= m_data_scans.end(); ++it) {
        delete (*it);
    }
    m_data_scans.clear();
    m_data_scans.push_back( OutputDataFunctions::selectRangeOnOneAxis(*m_real_data, "alpha_f", 0.012, 0.012) );
    m_data_scans.push_back( OutputDataFunctions::selectRangeOnOneAxis(*m_real_data, "phi_f", 0.011, 0.011) );

    // drawing data and scans
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,2);
    c1->cd(1); gPad->SetLogz();
    TH2D *hist1 = dynamic_cast<TH2D *>(IsGISAXSTools::getOutputDataTH123D( *m_real_data, "real_data"));
    hist1->Draw("COLZ");
    for(DataScan_t::iterator it=m_data_scans.begin(); it!= m_data_scans.end(); ++it) draw_scan_line(*(*it));

    int npad(2);
    for(DataScan_t::iterator it=m_data_scans.begin(); it!= m_data_scans.end(); ++it, ++npad) {
        c1->cd(npad);
        draw_scan_hist(*(*it));
    }

    c1->Update();
}


/* ************************************************************************* */
// drawing line representing scan
/* ************************************************************************* */
void TestFittingModule3::draw_scan_line(const OutputData<double> &data)
{
    TLine line;
    line.SetLineColor(kRed);
    line.SetLineStyle(1);
    line.SetLineWidth(2);
    double x1(0), x2(0), y1(0), y2(0);
    if( data.getAxis("alpha_f")->getSize() == 1) {
        // horizontal line
        x1 = dynamic_cast<const NamedVector<double >*>(data.getAxis("phi_f"))->getMin();
        x2 = dynamic_cast<const NamedVector<double >*>(data.getAxis("phi_f"))->getMax();
        y1 = y2 = dynamic_cast<const NamedVector<double >*>(data.getAxis("alpha_f"))->getMin();
    }else if( data.getAxis("phi_f")->getSize() == 1 ) {
        // it's vertical line
        x1 = x2 = dynamic_cast<const NamedVector<double >*>(data.getAxis("phi_f"))->getMin();
        y1 = dynamic_cast<const NamedVector<double >*>(data.getAxis("alpha_f"))->getMin();
        y2 = dynamic_cast<const NamedVector<double >*>(data.getAxis("alpha_f"))->getMax();
    } else {
        throw LogicErrorException("TestFittingModule3::draw_scan_line() -> Something wrong");
    }
    line.DrawLine(x1,y1,x2,y2);
}


/* ************************************************************************* */
// drawing histogram representing scan
/* ************************************************************************* */
void TestFittingModule3::draw_scan_hist(const OutputData<double> &data)
{
    TH2D *hist2 = dynamic_cast<TH2D *>(IsGISAXSTools::getOutputDataTH123D( data, "real_data"));
    TH1D *hist1(0);
    std::ostringstream ostr;
    if( !hist2) throw LogicErrorException("TestFittingModule3::draw_scan_hist() -> Something wrong");
    if( data.getAxis("alpha_f")->getSize() == 1) {
        hist1 = hist2->ProjectionX("proj_on_phi");
        ostr << "ProjOnPhi, alpha_f=" << dynamic_cast<const NamedVector<double >*>(data.getAxis("alpha_f"))->getMin();
    }else if( data.getAxis("phi_f")->getSize() == 1 ) {
        hist1 = hist2->ProjectionY("proj_on_alpha");
        ostr << "ProjOnAlpha, phi_f=" << dynamic_cast<const NamedVector<double >*>(data.getAxis("phi_f"))->getMin();
    } else {
        throw LogicErrorException("TestFittingModule3::draw_scan_hist() -> Something wrong");
    }
    hist1->SetTitle(ostr.str().c_str());
    hist1->DrawCopy();
    delete hist1;
    delete hist2;
}


/* ************************************************************************* */
// add noise to data
/* ************************************************************************* */
OutputData<double > *TestFittingModule3::createNoisyData(const OutputData<double> &exact_data, double noise_factor)
{
    OutputData<double > *real_data = exact_data.clone();
    OutputData<double>::iterator it = real_data->begin();
    while (it != real_data->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
//        *it = random;
        *it=current;
        ++it;
    }
    return real_data;
}


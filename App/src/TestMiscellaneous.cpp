// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestMiscellaneous.cpp
//! @brief     Implements class TestMiscellaneous.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMiscellaneous.h"
#include "SampleFactory.h"
#include "OutputData.h"
#include "SpecularMatrix.h"
#include "Units.h"
#include "FormFactors.h"
#include "DrawHelper.h"
#include "Simulation.h"
#include "IsGISAXSTools.h"
#include "Lattice.h"
#include "MesoCrystal.h"
#include "Crystal.h"
#include "LatticeBasis.h"
#include "MathFunctions.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"
#include "Types.h"
#include "MessageService.h"
#include "SampleBuilderFactory.h"
#include "SamplePrintVisitor.h"
#include "MaterialManager.h"
#include "BornAgainNamespace.h"
#include "FunctionalTestRegistry.h"
#include "Lattice2DIFParameters.h"
#include "InterferenceFunction2DLattice.h"
#include "Units.h"
#include "Types.h"
#include "FitSuite.h"
#include "AttLimits.h"

#include "TGraph.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TCanvas.h"
#include "TGraphPolar.h"
#include "TRandom.h"
#include "TBenchmark.h"
#include "TStyle.h"

TestMiscellaneous::TestMiscellaneous()
{
}

void TestMiscellaneous::execute()
{
    test_FunctionalTestRegistry();
    //test_PrintVisitor();
    //test_LogSystem();
    //test_OutputDataTo2DArray();
    //test_KVectorContainer();
    //test_OutputDataIOFactory();
    //test_FastSin();
    //test_FormFactor1();
    //test_FormFactor();
    //test_DrawMesocrystal();
    //test_SampleGeometry();
}


/* ************************************************************************* */
// test of hierarchical visitor
/* ************************************************************************* */
void TestMiscellaneous::test_FunctionalTestRegistry()
{
//    FunctionalTestRegistry tests;
//    tests.printCatalogue();

//    tests.getTest("isgisaxs01");
//    std::cout << Utils::FileSystem::GetReferenceDataDir() << std::endl;

    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    FormFactorFullSphere ff_cyl(5.0*Units::nanometer);
    Particle particle(particle_material, ff_cyl);

    ParticleDecoration particle_decoration;
    particle_decoration.addParticle(particle);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 2.0*M_PI/3.; // lattice angle
    lattice_params.m_xi = 0.0*Units::degree; // lattice orientation

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(10.0*Units::nanometer, 10.0*Units::nanometer);
    p_interference_function->setProbabilityDistribution(pdf);
    particle_decoration.addInterferenceFunction(p_interference_function);


    Layer air_layer(p_air_material);
    air_layer.setDecoration(particle_decoration);

    Layer substrate_layer(p_substrate_material, 0);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);


    Simulation *simulation = new Simulation();
    simulation->setDetectorParameters(100, -1.0*Units::degree, 1.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation->setSimulationParameters(sim_params);

    simulation->setSample(*multi_layer);

    // ----
    simulation->runSimulation();
    OutputData<double> *real_data = simulation->getIntensityData();
    double noise_factor(0.1);
    for(size_t i=0; i<real_data->getAllocatedSize(); ++i) {
        double amplitude = (*real_data)[i];
        double sigma = noise_factor*std::sqrt(amplitude);
        double noisy_amplitude = MathFunctions::GenerateNormalRandom(amplitude, sigma);
        if(noisy_amplitude < 0) noisy_amplitude = 0.0;
        (*real_data)[i] = noisy_amplitude;
    }

    FitSuite *fit_suite = new FitSuite();
    fit_suite->addSimulationAndRealData(*simulation, *real_data);
    fit_suite->initPrint(10);
//    fit_suite->addFitParameter("*2DLattice/length_*", 8.0*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01));
//    fit_suite->addFitParameter("*/FormFactorFullSphere/radius", 8.0*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01));
    fit_suite->addFitParameter("*2DLattice/length_*", 8.0*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(4., 12.));
    fit_suite->addFitParameter("*/FormFactorFullSphere/radius", 8.0*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(4., 12.));
    fit_suite->runFit();





}


/* ************************************************************************* */
// test of print visitor
/* ************************************************************************* */
void TestMiscellaneous::test_PrintVisitor()
{
    std::cout << "TestMiscellaneous::test_PrintVisitor() ->" << std::endl;
    SampleBuilderFactory factory;

    for(SampleBuilderFactory::iterator it = factory.begin(); it!= factory.end(); ++it) {
        ISample *sample = factory.createSample((*it).first);
        std::cout << std::endl << ">>> " << (*it).first << " <<<" << std::endl;
        sample->printSampleTree();
        delete sample;
    }

    for(SampleBuilderFactory::iterator it = factory.begin(); it!= factory.end(); ++it) {
        ISample *sample = factory.createSample((*it).first);
        std::cout << "xxxxx " << (*it).first << " " << sample->containsMagneticMaterial() << std::endl;
        delete sample;
    }


}


/* ************************************************************************* */
// test of log system
/* ************************************************************************* */
void TestMiscellaneous::test_LogSystem()
{
    std::cout << "TestMiscellaneous::test_LogSystem() -> Info" << std::endl;

    MSG::SetLevel(MSG::FATAL);

    msglog(MSG::VERBOSE) << "This is VERBOSE";
    msglog(MSG::DEBUG)   << "This is DEBUG";
    msglog(MSG::INFO)    << "This is INFO";
    msglog(MSG::WARNING) << "This is WARNING";
    msglog(MSG::ERROR)   << "This is ERROR";
    msglog(MSG::FATAL)   << "This is FATAL" << "and something" << 0;

    std::cout << "----" << std::endl;

    MSG::SetLevel(MSG::ERROR);
    msglog(MSG::VERBOSE) << "This is VERBOSE";
    msglog(MSG::DEBUG)   << "This is DEBUG";
    msglog(MSG::INFO)    << "This is INFO";
    msglog(MSG::WARNING) << "This is WARNING";
    msglog(MSG::ERROR)   << "This is ERROR";
    msglog(MSG::FATAL)   << "This is FATAL";

    std::cout << "----" << std::endl;

    MSG::SetLevel(MSG::INFO);
    msglog(MSG::VERBOSE) << "This is VERBOSE";
    msglog(MSG::DEBUG)   << "This is DEBUG";
    msglog(MSG::INFO)    << "This is INFO";
    msglog(MSG::WARNING) << "This is WARNING";
    msglog(MSG::ERROR)   << "This is ERROR";
    msglog(MSG::FATAL)   << "This is FATAL";


}

/* ************************************************************************* */
// test of OutputData export to 2D array
/* ************************************************************************* */
void TestMiscellaneous::test_OutputDataTo2DArray()
{
    // [axis0][axis1]
    int axis0_size = 2;
    int axis1_size = 4;
    OutputData<double> *p_output = new OutputData<double>;
    p_output->addAxis(BornAgain::PHI_AXIS_NAME, axis0_size, 0.0, double(axis0_size));
    p_output->addAxis(BornAgain::ALPHA_AXIS_NAME, axis1_size, 0.0, double(axis1_size));
    p_output->setAllTo(0.0);

    OutputData<double>::iterator it = p_output->begin();
    int nn=0;
    while (it != p_output->end())
    {
        size_t index0 = p_output->getIndexOfAxis(BornAgain::PHI_AXIS_NAME, it.getIndex());
        size_t index1 = p_output->getIndexOfAxis(BornAgain::ALPHA_AXIS_NAME, it.getIndex());
        std::cout << " index0:" << index0 << " index1:" << index1 << std::endl;
        *it = nn++;
        ++it;
    }
}

/* ************************************************************************* */
// test of reading of OutputData from ASCII file
/* ************************************************************************* */
void TestMiscellaneous::test_KVectorContainer()
{
    KVectorContainer cc;

    for(size_t i=0; i<100; ++i) {
        cc.push_back(kvector_t(i,0,0));
        cc.print();
    }
}

/* ************************************************************************* */
// test of reading of OutputData from ASCII file
/* ************************************************************************* */
void TestMiscellaneous::test_OutputDataIOFactory()
{
    std::string file_name = Utils::FileSystem::GetHomePath()
      +"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_qyqz.txt.gz";
    OutputData<double > *data = OutputDataIOFactory::readIntensityData(file_name);

    TCanvas *c1 = new TCanvas("c1","c1",800, 800);
    c1->cd(); gPad->SetRightMargin(0.14);
    gPad->SetLogz();

    TH2D *h2 = IsGISAXSTools::getOutputDataTH2D(*data, "xxx");
    h2->SetMinimum(100.);
    h2->Draw("CONT4 Z");
}


/* ************************************************************************* */
// test of fast sin function approximation
/* ************************************************************************* */
void TestMiscellaneous::test_FastSin()
{
    double xmin = -2*M_PI;
    double xmax = 2*M_PI;
    int npx(100);
    double dx = (xmax-xmin)/double(npx-1);
    for(int i=0; i<npx; ++i){
        double x = (xmin + dx*i);

        complex_t cx(x, x/2.);
        complex_t cs1 = std::sin(cx);
        complex_t cs2 = MathFunctions::FastSin(cx);
        std::cout << "xx:" << cx << " std::sin " << cs1 << " sine:" << cs2 << " diff:" << cs1-cs2 << std::endl;
    }
}

/* ************************************************************************* */
// opengl mesocrystal drawing
/* ************************************************************************* */
void TestMiscellaneous::test_DrawMesocrystal()
{
    MultiLayer *m_sample = dynamic_cast<MultiLayer *>(
            SampleFactory::createSample("MesoCrystal2"));
    DrawHelper::DrawMesoCrystal(m_sample);
}

/* ************************************************************************* */
// form factor as a function of qx,qy,qz
/* ************************************************************************* */
void TestMiscellaneous::test_FormFactor()
{

    FormFactorFullSphere ff_sphere(5.*Units::nanometer);
    FormFactorCylinder ff_cylinder(10.*Units::nanometer, 5.*Units::nanometer);

//    IFormFactor& ff = ff_cylinder;
    IFormFactor& ff = ff_sphere;

    double qmin(-4.0), qmax(4.0);
    int nbins(51);
    double dq = (qmax-qmin)/(nbins-1);

    TH1D *h1[3];
    h1[0] = new TH1D("h10","h10", nbins, qmin-dq/2., qmax+dq/2.);
    h1[1] = new TH1D("h11","h11", nbins, qmin-dq/2., qmax+dq/2.);
    h1[2] = new TH1D("h12","h12", nbins, qmin-dq/2., qmax+dq/2.);
    TH2D *h2 = new TH2D("h2","h2", nbins, qmin-dq/2., qmax+dq/2.,
            nbins, qmin-dq/2., qmax+dq/2.);
    TH3D *h3 = new TH3D("h3","h3", nbins, qmin-dq/2., qmax+dq/2.,
            nbins, qmin-dq/2., qmax+dq/2.,nbins, qmin-dq/2., qmax+dq/2.);


    std::vector<TH2D *> vh2_xy;
    std::vector<TH2D *> vh2_xz;
    std::vector<TH2D *> vh2_yz;

    vh2_xy.resize(nbins, 0);
    vh2_xz.resize(nbins, 0);
    vh2_yz.resize(nbins, 0);

    for(int i=0; i<nbins; ++i) {
        char str[128];
        sprintf(str, "h2_xy_z%d",i);
        vh2_xy[i] = new TH2D(str,str,nbins, qmin-dq/2., qmax+dq/2.,
                nbins, qmin-dq/2., qmax+dq/2.);
        vh2_xy[i]->GetXaxis()->SetTitle("x");
        vh2_xy[i]->GetYaxis()->SetTitle("y");

        sprintf(str, "h2_xz_y%d",i);
        vh2_xz[i] = new TH2D(str,str,nbins, qmin-dq/2., qmax+dq/2.,
                nbins, qmin-dq/2., qmax+dq/2.);
        vh2_xz[i]->GetXaxis()->SetTitle("x");
        vh2_xz[i]->GetYaxis()->SetTitle("z");

        sprintf(str, "h2_yz_x%d",i);
        vh2_yz[i] = new TH2D(str,str,nbins, qmin-dq/2., qmax+dq/2.,
                nbins, qmin-dq/2., qmax+dq/2.);
        vh2_yz[i]->GetXaxis()->SetTitle("y");
        vh2_yz[i]->GetYaxis()->SetTitle("z");
    }

    OutputData<double> *p_data = new OutputData<double>();
    p_data->addAxis(std::string("qx"), nbins, qmin, qmax);
    p_data->addAxis(std::string("qy"), nbins, qmin, qmax);
    p_data->addAxis(std::string("qz"), nbins, qmin, qmax);
    OutputData<double>::const_iterator it = p_data->begin();
    while (it != p_data->end()) {
        double x = p_data->getValueOfAxis("qx", it.getIndex());
        double y = p_data->getValueOfAxis("qy", it.getIndex());
        double z = p_data->getValueOfAxis("qz", it.getIndex());

        int ix = (int)p_data->getIndexOfAxis("qx", it.getIndex());
        int iy = (int)p_data->getIndexOfAxis("qy", it.getIndex());
        int iz = (int)p_data->getIndexOfAxis("qz", it.getIndex());

        cvector_t q(x,y,z);
        cvector_t q0(0.0,0.0,0.0);
        Bin1DCVector q0_bin(q0, q0);
        Bin1D zero_bin = { 0.0, 0.0 };
        double value = std::abs(ff.evaluate(q,q0_bin, zero_bin));
        if(iz==50) h2->Fill(x,y,std::abs(ff.evaluate(q,q0_bin, zero_bin)));

        h3->Fill(x,y,z,std::abs(ff.evaluate(q,q0_bin, zero_bin)));

        if(iy==0 && iz==0) {
            cvector_t kx(x,1.0,1.0);
            cvector_t ky(1.0,x,1.0);
            cvector_t kz(1.0,1.0,x);
            h1[0]->Fill(x, std::abs(ff.evaluate(kx,q0_bin, zero_bin)));
            h1[1]->Fill(x, std::abs(ff.evaluate(ky,q0_bin, zero_bin)));
            h1[2]->Fill(x, std::abs(ff.evaluate(kz,q0_bin, zero_bin)));
        }

        vh2_xy[iz] ->Fill(x,y,value);
        vh2_xz[iy] ->Fill(x,z,value);
        vh2_yz[ix] ->Fill(y,z,value);

        ++it;
    }

    TCanvas *c1_xy = new TCanvas("c1_xy","c1_xy",1024,768);
    DrawHelper::SetMagnifier(c1_xy);
    c1_xy->Divide(3,3);
    int ndiv=9;
    for(int i=0; i<ndiv; i++) {
        c1_xy->cd(i+1);
        int indx = i*int(nbins/ndiv);
        std::cout << indx << std::endl;
        vh2_xy[indx]->Draw("surf");
    }

    TCanvas *c1_xz = new TCanvas("c1_xz","c1_xz",1024,768);
    DrawHelper::SetMagnifier(c1_xz);
    c1_xz->Divide(3,3);
    for(int i=0; i<ndiv; i++) {
        c1_xz->cd(i+1);
        int indx = i*int(nbins/ndiv);
        vh2_xz[indx]->Draw("surf");
    }

    TCanvas *c1_yz = new TCanvas("c1_yz","c1_yz",1024,768);
    DrawHelper::SetMagnifier(c1_yz);
    c1_yz->Divide(3,3);
    for(int i=0; i<ndiv; i++) {
        c1_yz->cd(i+1);
        int indx = i*int(nbins/ndiv);
        vh2_yz[indx]->Draw("surf");
    }
}

/* ************************************************************************* */
// plots of form factor :
// contourplot (amp & phase or Re & Im) and log(|F|**2) vs. log(q)
/* ************************************************************************* */
void TestMiscellaneous::test_FormFactor1()
{
    FormFactorFullSphere ff_fullsphere(5.*Units::nanometer);

    FormFactorCylinder ff_cylinder(10.*Units::nanometer,
                                   5.*Units::nanometer);
   //   IFormFactor& ff = ff_cylinder;

    FormFactorParallelepiped ff_para(7.*Units::nanometer,
                                     6.*Units::nanometer);
   //   IFormFactor& ff = ff_para;

    FormFactorPyramid ff_pyramid(10.*Units::nanometer,
                                 5.*Units::nanometer,
                                 Units::deg2rad(54.73 ));
    IFormFactor& ff = ff_pyramid;

    FormFactorPrism3 ff_prism3(5.*Units::nanometer,
                              5.*Units::nanometer);
   //   IFormFactor& ff = ff_prism3;

    FormFactorSphere ff_sphere(5.*Units::nanometer,
                               5.*Units::nanometer);
   //   IFormFactor& ff = ff_sphere;

    FormFactorBox ff_box(5*Units::nanometer,
                         5*Units::nanometer,
                         5*Units::nanometer);
  //    IFormFactor& ff = ff_box;

    //IFormFactor& ff = ff_fullsphere;

    double qmin(-4.0), qmax(4.0);
    double lambda = 1.0;
    double alpha_i = 0.2*M_PI/180.0;
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);
    int nbins(101);
    double dq =(qmax-qmin)/(nbins-1);

    TH2D *vh2_xy = new TH2D("vh2_xy","vh2_xy;q_{x};q_{y};qz",nbins, qmin-dq/2.,
            qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.);

    OutputData<double> *p_data = new OutputData<double>();
    p_data->addAxis(std::string("qx"), nbins, qmin, qmax);
    p_data->addAxis(std::string("qy"), nbins, qmin, qmax);
    p_data->addAxis(std::string("qz"), 1, qmin, qmax);
    OutputData<double>::const_iterator it = p_data->begin();
    double z = p_data->getValueOfAxis("qz", it.getIndex());

    while (it != p_data->end()) {
        double x = p_data->getValueOfAxis("qx", it.getIndex());
        double y = p_data->getValueOfAxis("qy", it.getIndex());

        cvector_t q(x,y,z);
        cvector_t q0(0.0,0.0,0.0);
        Bin1DCVector q0_bin(q0, q0);
        Bin1D zero_bin = { 0.0, 0.0 };
        double value = std::abs(ff.evaluate(q,q0_bin, zero_bin));
        //double valuep = std::abs(ff.evaluate(q,q0_bin, zero_bin));
        //double valuer = std::abs(ff.evaluate(q,q0_bin, zero_bin));
        //double valuei = std::abs(ff.evaluate(q,q0_bin, zero_bin));

        vh2_xy->Fill(x,y,value);

        ++it;
    }

    TCanvas *c1_xy = new TCanvas("c1_xy","c1_xy",1024,768);
    DrawHelper::SetMagnifier(c1_xy);
    //c1_xy->Divide(2,2);
        c1_xy->cd(1);
                gPad->SetRightMargin(0.11);
                gPad->SetLogz();
                vh2_xy->GetXaxis()->SetNdivisions(510);
                vh2_xy->GetYaxis()->SetNdivisions(510);
                vh2_xy->SetContour(99);
                gStyle->SetPalette(1);
                gStyle->SetOptStat(0);
                vh2_xy->Draw("cont4 z");
                c1_xy->Print("test.eps");
}

void TestMiscellaneous::test_SampleGeometry()
{
    MultiLayer multi_layer;
    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    ParticleDecoration particle_decoration
        (new Particle(particle_material, new FormFactorFullSphere
                      (5*Units::nanometer)));

    air_layer.setDecoration(particle_decoration);

    multi_layer.addLayer(air_layer);

    Simulation simulation;
    simulation.setDetectorParameters(100, -2.0*Units::degree, 2.0*Units::degree,
            100, -2.0*Units::degree, 2.0*Units::degree);
    simulation.setBeamParameters(0.1*Units::nanometer, 0.2*Units::degree, 0.0);
    simulation.setSample(multi_layer);
    simulation.runSimulation();

    IsGISAXSTools::drawLogOutputData(*simulation.getIntensityData(),
            "c1_geom", "Sample geometry", "CONT4 Z", "Sample geometry");
}

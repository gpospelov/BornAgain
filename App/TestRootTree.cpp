// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestRootTree.cpp
//! @brief     Implements class TestRootTree.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestRootTree.h"
#include "MultiLayer.h"
#include "Materials.h"
#include "ParticleLayout.h"
#include "Particle.h"
#include "Simulation.h"
#include "FormFactors.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"
#include "SampleFactory.h"
#include "IsGISAXSTools.h"

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "IsGISAXSTools.h"
#include "TreeEventStructure.h"
#include "TestMesoCrystal1.h"

#include <vector>


void TestRootTree::execute()
{
    // example showing handling of tree with complex data structures
    complex_write();
//    complex_read();

    // example showing handling of tree with simple data structures
    //simple_write();
    //simple_read();

}

//! Example showing writing in the tree simple data structures.

void TestRootTree::complex_write()
{
    std::string root_file_name = "testmeso.root";
    std::string tree_name = "testmeso";

    // preparing root file for writing
    TFile *top = new TFile(root_file_name.c_str(),"RECREATE");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException(
            "TestRootTree::complex_write() -> "
            "Can't open file "+root_file_name+" for writing");
    }

    // creating new tree
    TTree *tree = new TTree(tree_name.c_str(),"Oh, my data");

    TreeEventOutputData *event = new TreeEventOutputData();
    tree->Branch("Event",&event,16000,2);

    // preparing set of meso parameters to simulate

    size_t n_phi_rotation_steps =100;
    size_t n_alpha_rotation_steps = 100;
    size_t n_np_size_steps = 10;
    double phi_step = 2*Units::PI/3.0/n_phi_rotation_steps;
    double alpha_step = 10*Units::degree/n_alpha_rotation_steps;
    double np_size_step = 0.5*Units::nanometer/n_np_size_steps;
    double np_size_start = 6.1*Units::nanometer -
        (n_np_size_steps/2)*np_size_step;

    TCanvas *c1 = new TCanvas("c1","c1");

    std::vector<MesoParSet > meso_parameters;
    for (size_t j=0; j<n_np_size_steps; ++j)
        meso_parameters.push_back( MesoParSet(np_size_start +
                                              j*np_size_step, 0, 0) );
    for (size_t j=0; j<n_phi_rotation_steps; ++j)
        meso_parameters.push_back( MesoParSet(np_size_start, j*phi_step, 0) );
    for (size_t j=0; j<n_alpha_rotation_steps; ++j)
        meso_parameters.push_back( MesoParSet(np_size_start, 0, j*alpha_step) );

    for (size_t ipar=0; ipar<meso_parameters.size(); ++ipar) {
        double meso_npR = meso_parameters[ipar].npR;
        double meso_phi = meso_parameters[ipar].phi;
        double meso_alpha = meso_parameters[ipar].alpha;
        initializeMesoCrystal(meso_alpha, meso_phi, meso_npR);
//        initializeMesoCrystal(0.0, 0.0, meso_npR);

        std::cout << " npR:" << meso_npR <<
            " meso_phi:" << meso_phi <<
            " meso_alpha:" << meso_alpha << std::endl;

        double alpha_i(0.4*Units::degree);
        double phi_i(0.0*Units::degree);
        int nphi_f(100), nalpha_f(100);
        double phi_f_min(0.3*Units::degree), phi_f_max(0.072);
        double alpha_f_min(-0.4*Units::degree), alpha_f_max(0.066);

        GISASSimulation simulation(mp_options);
        simulation.setSample(*mp_sample);
        simulation.setDetectorParameters(
            nphi_f, phi_f_min, phi_f_max,
            nalpha_f , alpha_f_min, alpha_f_max);
        simulation.setBeamParameters(1.77*Units::angstrom, alpha_i, phi_i);
        simulation.setBeamIntensity(1e7);
        simulation.runSimulation();
        //simulation.normalize();

        // saving experimental parameter in event structure
        event->alpha_i = Units::rad2deg(alpha_i);
        event->phi_i = Units::rad2deg(phi_i);
        event->nalpha_f = nalpha_f;
        event->alpha_f_min = Units::rad2deg(alpha_f_min);
        event->alpha_f_max = Units::rad2deg(alpha_f_max);
        event->nphi_f = nphi_f;
        event->phi_f_min = Units::rad2deg(phi_f_min);
        event->phi_f_max = Units::rad2deg(phi_f_max);
        // saving mesocrystal parameters
        event->npR = meso_npR;
        event->mphi = Units::rad2deg(meso_phi);
        event->malpha = Units::rad2deg(meso_alpha);
        // copying output data into event frame
        delete mp_data;
        mp_data = simulation.getDetectorIntensity();
        IsGISAXSTools::exportOutputDataInVectors2D(
            *mp_data, event->vi, event->vphi_f, event->valpha_f);

        // lets switch to degtrees
        for(size_t i=0; i<event->vphi_f.size(); i++){
            for(size_t j=0; j<event->vphi_f[i].size(); j++) {
                event->vphi_f[i][j] /= Units::degree;
                event->valpha_f[i][j] /= Units::degree;
            }
        }

        c1->cd(); gPad->SetLogz();
        c1->Clear();
        IsGISAXSTools::setMinimum(1.);
        IsGISAXSTools::drawOutputDataInPad(
            *mp_data, "CONT4 Z", "IsGisaxs pyramid FF");
        c1->Modified();
        c1->Update();

        tree->Fill();
        event->nframe++;
    }

    tree->Write();
    top->Close();
}

//! Example showing reading from the tree simple data structures.

void TestRootTree::complex_read()
{
    std::cout << "TestRootTree::complex_read() -> "
        "going to red tree back from file" << std::endl;

    std::string root_file_name = "mydata2.root";
    std::string tree_name = "mytree2";

    // preparing root file for reading
    TFile *top = new TFile(root_file_name.c_str(),"READ");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException(
            "TestRootTree::complex_read() -> "
            "Can't open file "+root_file_name+" for reading");
    }

    // getting existing tree
    TTree *tree = (TTree *)top->Get(tree_name.c_str());
    if( !tree ) {
        throw RuntimeErrorException(
            "TestRootTree::complex_read() -> "
            "Can't get tree with name '" + tree_name + "' from root file");
    }

    TreeEventOutputData *event = 0;

    tree->SetBranchAddress("Event", &event);

    // reading data from the tree
    for(int i=0; i<tree->GetEntries(); i++) {
        tree->GetEntry(i);
        std::cout << event->alpha_i << " " << " " << std::endl;
    }

    top->Close();
}

//! Example showing writing in the tree simple data structures.

void TestRootTree::simple_write()
{
    delete mp_simulation;
    delete mp_sample;
    delete mp_data;

    mp_sample = dynamic_cast<MultiLayer*>
        (SampleFactory::createSample("IsGISAXS9_Pyramid"));

    // setting simulation
    mp_simulation = new GISASSimulation(mp_options);
    mp_simulation->setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree);
    mp_simulation->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    mp_simulation->setSample(*mp_sample);

    // variables below will be written in the tree
    double intens1(0), intens2(0), alpha_i(0), phi_i(0), alpha_f(0), phi_f(0);
    int nev;
    //std::vector<double > *somevector;

    std::string root_file_name = "mydata.root";
    std::string tree_name = "mytree";

    // preparing root file for writing
    TFile *top = new TFile(root_file_name.c_str(),"RECREATE");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException(
            "TestRootTree::simple_write() -> "
            "Can't open file "+root_file_name+" for writing");
    }

    // creating new tree
    TTree *tree = new TTree(tree_name.c_str(),"Oh, my data");

    // pointing tree to local variables
    tree->Branch("intens1",&intens1, "intens1/D");
    tree->Branch("intens2",&intens2, "intens2/D");
    tree->Branch("alpha_i",&alpha_i, "alpha_i/D");
    tree->Branch("alpha_f",&alpha_f, "alpha_f/D");
    tree->Branch("phi_f",&phi_f, "phi_f/D");
    tree->Branch("nev",&nev, "nev/I");
    //somevector = new std::vector<double>;
    //tree->Branch("somevector","vector<double >", &somevector);

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);

    // our experiment begins here
    const int nTotalEvents = 10;
    TRandom mr(0);
    for(int i_ev=0; i_ev<nTotalEvents; i_ev++) {
        if(i_ev%10 ==0 ) std::cout << "nevent:" << i_ev << std::endl;

        alpha_i = 0.3 - 0.1*mr.Rndm(); // generating random alpha_i in the interval
        //phi_i = Units::PI*2.*mr.Rndm(); // generating random phi_i in the interval
        phi_i = 0;
        nev = i_ev;

        mp_simulation->setBeamParameters(
            1.0*Units::angstrom, alpha_i*Units::degree, phi_i);
        mp_simulation->runSimulation();

        mp_data = mp_simulation->getDetectorIntensity();
        // accessing to scattering data
        const IAxis *axis0 = mp_data->getAxis(0);
        const IAxis *axis1 = mp_data->getAxis(1);
        std::string axis0_name = axis0->getName();
        std::string axis1_name = axis1->getName();

        c1->cd(); gPad->SetLogz();
        c1->Clear();
        IsGISAXSTools::setMinimum(1.);
        IsGISAXSTools::drawOutputDataInPad(
            *mp_data, "CONT4 Z", "IsGisaxs pyramid FF");
        c1->Modified();
        c1->Update();
        c1->Write();

        OutputData<double>::const_iterator it = mp_data->begin();
        while (it != mp_data->end())
        {
            size_t index_phi_f = mp_data->getAxisBinIndex(it.getIndex(), axis0_name);
            size_t index_alpha_f = mp_data->getAxisBinIndex(it.getIndex(), axis1_name);
            phi_f = Units::rad2deg( (*axis0)[index_phi_f]);
            alpha_f = Units::rad2deg( (*axis1)[index_alpha_f] );
            //std::cout << phi_f << " " << alpha_f << std::endl;
            intens1 = *it++;
            tree->Fill();
        }
        delete mp_data;
    }

    tree->Write();
    top->Close();
    delete top;

    //delete somevector;

    std::string info;
    info += "Root file '" + root_file_name +
        "' has been successfully created. \n";
    info += "Hits for root session: \n";
    info += "root -l " + root_file_name + "\n";
    info += "TBrowser b; \n";
    info += "TTree *tree = (TTree *)_file0->Get(\"" + tree_name + "\"); \n";
    info += "gPad->SetLogz(); \n";
    info += "tree->Draw(\"alpha_i\"); \n";
    info += "tree->Draw(\"alpha_f:phi_f\"); \n";
    info += "tree->Draw(\"intens1:alpha_f:phi_f\",\"alpha_i>-0.2&&alpha_i<-0.1 \",\"prof CONT4 Z\"); \n";

    std::cout << info << std::endl;
}

//! Example showing reading from the tree simple data structures.

void TestRootTree::simple_read()
{
    std::cout << "TestRootTree::simple_read() -> "
        "going to read tree back from file" << std::endl;

    std::string root_file_name = "mydata.root";
    std::string tree_name = "mytree";

    // preparing root file for reading
    TFile *top = new TFile(root_file_name.c_str(),"READ");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException(
            "TestRootTree::simple_read() -> "
            "Can't open file "+root_file_name+" for reading");
    }

    // getting existing tree
    TTree *tree = (TTree *)top->Get(tree_name.c_str());
    if( !tree ) {
        throw RuntimeErrorException(
            "TestRootTree::simple_read() -> "
            "Can't get tree with name '" + tree_name + "' from root file");
    }

    TCanvas *c2 = new TCanvas("c2","reading tree back",1024, 768);
    c2->cd(); gPad->SetLogz();
    tree->Print();
    tree->Draw("intens1:alpha_f:phi_f","intens1>0","prof CONT4 Z");

    // now reading the tree in another way
    // variables below will be red from the tree
    double intens1(0), intens2(0), alpha_i(0), phi_i(0), alpha_f(0), phi_f(0);
    int nev;

    // pointing tree to local variables
    tree->SetBranchAddress("intens1",&intens1);
    tree->SetBranchAddress("intens2",&intens2);
    tree->SetBranchAddress("alpha_i",&alpha_i);
    tree->SetBranchAddress("alpha_f",&alpha_f);
    tree->SetBranchAddress("phi_f",&phi_f);
    tree->SetBranchAddress("nev",&nev);

    // loop over all records stored in the tree
    for(int i=0; i<tree->GetEntries(); i++) {
        tree->GetEntry(i);
        // at this point all local variables are filled with values from the tree
        std::cout <<
            "alpha_i:" << alpha_i << " phi_i:" << phi_i  <<
            " alpha_f:" << alpha_f << " phi_f:" << phi_f <<
            " intens:" << intens1 << std::endl;
        if(i>10) break;
    }

    top->Close();
}

//!

void TestRootTree::initializeMesoCrystal(double /* meso_alpha */, double /* meso_phi*/, double /*nanopart_radius*/)
{
//    (void)nanopart_radius;
//    delete mp_sample;
//    // create mesocrystal
//    double meso_radius = 300*Units::nanometer;
//    double surface_filling_ratio = 0.25;
//    double surface_density = surface_filling_ratio/Units::PI/meso_radius/meso_radius;
//    complex_t n_particle(1.0-1.55e-5, 1.37e-6);
//    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
//    complex_t n_avg = std::sqrt(surface_filling_ratio*avg_n_squared_meso +
//                                1.0 - surface_filling_ratio);
////    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
////    FormFactorCylinder ff_meso(meso_radius, 0.2*Units::micrometer);

//    // Create multilayer
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-7.57e-6, 1.73e-7);

//    HomogeneousMaterial air_material("Air", n_air);
//    HomogeneousMaterial average_layer_material("Averagelayer", n_avg);
//    HomogeneousMaterial substrate_material("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(air_material);
//    Layer avg_layer;
//    avg_layer.setMaterial(average_layer_material);
//    avg_layer.setThickness(0.2*Units::micrometer);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(substrate_material);
//    IInterferenceFunction *p_interference_funtion =
//        new InterferenceFunctionNone();
//    ParticleLayout particle_layout;

//    //double R = nanopart_radius;
//    RotationZ transform1(meso_phi);
//    RotationY transform2(meso_alpha);

//    particle_layout.setTotalParticleSurfaceDensity(surface_density);
//    particle_layout.addInterferenceFunction(p_interference_funtion);

//    avg_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(avg_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    mp_sample = p_multi_layer;

    throw Exceptions::NotImplementedException("Cleanup the code!");
}




#include "TestRootTree.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "NanoParticleDecoration.h"
#include "NanoParticle.h"
#include "LayerDecorator.h"
#include "GISASExperiment.h"
#include "FormFactors.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "IsGISAXSTools.h"
#include "TestEventStructure.h"


TestRootTree::TestRootTree() : m_sample(0), m_experiment(0), m_data(0)
{

}


TestRootTree::~TestRootTree()
{
    delete m_sample;
    delete m_experiment;
    delete m_data;
}


void TestRootTree::execute()
{

    // preparing some real data for tree playing
    prepare_experiment();

    // example showing handling of tree with simple data structures
    simple_write();
    simple_read();

    // example showing handling of tree with complex data structures
//    complex_write();
//    complex_read();
}


/* ************************************************************************* */
// example showing writing in the tree simple data structures
/* ************************************************************************* */
void TestRootTree::simple_write()
{
    // variables below will be written in the tree
    double intens1(0), intens2(0), alpha_i(0), phi_i(0), alpha_f(0), phi_f(0);
    int nev;
    //std::vector<double > *somevector;

    std::string root_file_name = "mydata.root";
    std::string tree_name = "mytree";

    // preparing root file for writing
    TFile *top = new TFile(root_file_name.c_str(),"RECREATE");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException("TestRootTree::simple_write() -> Can't open file "+root_file_name+" for writing");
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

        alpha_i = -0.3 + 0.1*mr.Rndm(); // generating random alpha_i in the interval
        //phi_i = M_PI*2.*mr.Rndm(); // generating random phi_i in the interval
        phi_i = 0;
        nev = i_ev;

        m_experiment->setBeamParameters(1.0*Units::angstrom, alpha_i*Units::degree, phi_i);
        m_experiment->runSimulation();

        m_data = m_experiment->getOutputDataClone();
        // accessing to scattering data
        NamedVector<double> *axis0 = dynamic_cast<NamedVector<double>*>(m_data->getAxes()[0]);
        NamedVector<double> *axis1 = dynamic_cast<NamedVector<double>*>(m_data->getAxes()[1]);
        std::string axis0_name = axis0->getName();
        std::string axis1_name = axis1->getName();

        c1->cd(); gPad->SetLogz();
        c1->Clear();
        IsGISAXSTools::setMinimum(1.);
        IsGISAXSTools::drawOutputDataInPad(*m_data, "CONT4 Z", "IsGisaxs pyramid FF");
        c1->Modified();
        c1->Update();
        c1->Write();

        m_data->resetIndex();
        while (m_data->hasNext())
        {
            size_t index_phi_f =  m_data->getCurrentIndexOfAxis(axis0_name.c_str());
            size_t index_alpha_f = m_data->getCurrentIndexOfAxis(axis1_name.c_str());
            phi_f = Units::rad2deg( (*axis0)[index_phi_f]);
            alpha_f = Units::rad2deg( (*axis1)[index_alpha_f] );
            //std::cout << phi_f << " " << alpha_f << std::endl;
            intens1 =m_data->next();
            tree->Fill();

        }

        delete m_data;
    }

    tree->Write();
    top->Close();
    delete top;

    //delete somevector;

    std::string info;
    info += "Root file '" + root_file_name + "' has been successfully created. \n";
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


/* ************************************************************************* */
// example showing reading from the tree simple data structures
/* ************************************************************************* */
void TestRootTree::simple_read()
{
    std::cout << "TestRootTree::simple_read() -> going to read tree back from file" << std::endl;

    std::string root_file_name = "mydata.root";
    std::string tree_name = "mytree";

    // preparing root file for reading
    TFile *top = new TFile(root_file_name.c_str(),"READ");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException("TestRootTree::simple_read() -> Can't open file "+root_file_name+" for reading");
    }

    // getting existing tree
    TTree *tree = (TTree *)top->Get(tree_name.c_str());
    if( !tree ) {
        throw RuntimeErrorException("TestRootTree::simple_read() -> Can't get tree with name '" + tree_name + "' from root file");
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
        std::cout << "alpha_i:" << alpha_i << " phi_i:" << phi_i  << " alpha_f:" << alpha_f << " phi_f:" << phi_f << " intens:" << intens1 << std::endl;
        if(i>10) break;
    }

    top->Close();

}



/* ************************************************************************* */
// example showing writing in the tree simple data structures
/* ************************************************************************* */
void TestRootTree::complex_write()
{

    std::string root_file_name = "mydata2.root";
    std::string tree_name = "mytree2";

    // preparing root file for writing
    TFile *top = new TFile(root_file_name.c_str(),"RECREATE");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException("TestRootTree::complex_write() -> Can't open file "+root_file_name+" for writing");
    }

    // creating new tree
    TTree *tree = new TTree(tree_name.c_str(),"Oh, my data");

    TestEventStructure *event = new TestEventStructure();
    tree->Branch("Event",&event,16000,2);

    // writing 10 events
    for(int i=0; i<10; i++) {
        event->alpha_i = i+1;
        event->alpha_f = i+10;
        event->vec.resize(10, 99.9);
        tree->Fill();
    }

    tree->Write();
    top->Close();
}


/* ************************************************************************* */
// example showing reading from the tree simple data structures
/* ************************************************************************* */
void TestRootTree::complex_read()
{
    std::cout << "TestRootTree::complex_read() -> going to red tree back from file" << std::endl;

    std::string root_file_name = "mydata2.root";
    std::string tree_name = "mytree2";

    // preparing root file for reading
    TFile *top = new TFile(root_file_name.c_str(),"READ");
    if( !top->IsOpen() ) {
        throw RuntimeErrorException("TestRootTree::complex_read() -> Can't open file "+root_file_name+" for reading");
    }

    // getting existing tree
    TTree *tree = (TTree *)top->Get(tree_name.c_str());
    if( !tree ) {
        throw RuntimeErrorException("TestRootTree::complex_read() -> Can't get tree with name '" + tree_name + "' from root file");
    }

    TestEventStructure *event = 0;
    tree->SetBranchAddress("Event", &event);

    // reading data from the tree
    for(int i=0; i<tree->GetEntries(); i++) {
        tree->GetEntry(i);
        std::cout << event->alpha_i << " " << event->alpha_f << " " << std::endl;
    }

    top->Close();

}



/* ************************************************************************* */
// prepare for calculations
/* ************************************************************************* */
void TestRootTree::prepare_experiment()
{
    if(m_sample) delete m_sample;
    m_sample=0;

    if(m_experiment) delete m_experiment;
    m_experiment = 0;

    if(m_data) delete m_data;
    m_data = 0;

    // making sample
    MultiLayer *multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer->addLayer(air_layer_decorator);
    multi_layer->addLayer(substrate_layer);

    m_sample = multi_layer;

    // setting experiment
    m_experiment = new GISASExperiment();
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    m_experiment->setSample(m_sample);

}



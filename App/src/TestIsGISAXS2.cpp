#include "TestIsGISAXS2.h"
#include "GISASExperiment.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "IsGISAXSTools.h"

#include "TCanvas.h"
#include "TGraph.h"


TestIsGISAXS2::TestIsGISAXS2()
{
    std::cout << "TestIsGISAXS2::TestIsGISAXS2() -> Info" << std::endl;
}


void TestIsGISAXS2::execute()
{

    // setting experiment
    double alpha_i = 0.2*Units::degree;
    double phi_i = 0.0*Units::degree;

    GISASExperiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -alpha_i, phi_i);

    kvector_t k_i = experiment.getBeam().getCentralK();
    double lambda = 2.0*M_PI/k_i.mag();

    OutputData<double> *output = experiment.getOutputDataClone();

    output->setAllTo(0.0);

    FormFactorCylinder m_ff(5*Units::nanometer, 5*Units::nanometer);

    output->resetIndex();
    while (output->hasNext())
    {
        double phi_f = output->getCurrentValueOfAxis<double>("phi_f");
        double alpha_f = output->getCurrentValueOfAxis<double>("alpha_f");
        //std::cout << " phi_f:" << phi_f << " alpha_f:" << alpha_f << std::endl;
        kvector_t k_f;
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        kvector_t q = k_f - k_i;
        if(phi_f==0) {
            std::cout << "   " << k_i << " " << k_f << " " << q << " " << q.mag() << std::endl;
        }
        output->next() = std::pow(std::abs(m_ff.evaluate(k_i, k_f)),2);
    }


    TCanvas *c1 = new TCanvas("c1","c1", 1024, 768);
    c1->Divide(2,2);

    c1->cd(1);
    IsGISAXSTools::drawOutputDataInPad(*output, "CONT4 Z", "IsGisaxs pyramid FF");

//    c1->cd(2);
//    TGraph *gr = new TGraph(100);
//    OutputData<double > *data = new OutputData<double >;
//    data->addAxis(std::string("qy"), 0.0, 2.5, 100);
//    data->resetIndex();
//    while (data->hasNext()) {
//        double qy = data->getCurrentValueOfAxis<double>("qy");
//        cvector_t q(0,qy,0);
//        std::cout << qy << " " << m_ff.evaluate(q) << std::endl;

//        data->next();
//    }


}


void TestIsGISAXS2::finalise()
{


}

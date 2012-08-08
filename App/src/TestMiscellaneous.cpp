#include "TestMiscellaneous.h"
#include "SampleFactory.h"
#include "OutputData.h"
#include "OpticalFresnel.h"
#include "Units.h"
#include "DoubleToComplexInterpolatingFunction.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TGraphPolar.h"
#include "TSystem.h"

TestMiscellaneous::TestMiscellaneous()
{
}




void TestMiscellaneous::execute()
{

    test_DoubleToComplexInterpolatingFunction();

}


void TestMiscellaneous::test_DoubleToComplexInterpolatingFunction()
{


    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("MultilayerOffspecTestcase1a"));

    OutputData<double > *data_alpha = new OutputData<double >;
    data_alpha->addAxis(std::string("alpha_f"), 0.0*Units::degree, 2.0*Units::degree, 200);

    OpticalFresnel fresnelCalculator;

    const NamedVector<double> *p_alpha_axis = dynamic_cast<const NamedVector<double> *>(data_alpha->getAxis("alpha_f"));
    std::map<double, OpticalFresnel::MultiLayerCoeff_t> fresnel_coeff_map;
    for (size_t i=0; i<p_alpha_axis->getSize(); ++i) {
        double angle = (*p_alpha_axis)[i];
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(1.4*Units::angstrom, angle, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        fresnelCalculator.execute(*sample, kvec, coeffs);
        fresnel_coeff_map[angle] = coeffs;
    }

    std::vector<DoubleToComplexInterpolatingFunction *> m_TT;
    std::vector<DoubleToComplexInterpolatingFunction *> m_RR;
    m_TT.resize(sample->getNumberOfInterfaces(), 0);
    m_RR.resize(sample->getNumberOfInterfaces(), 0);

    for(size_t i_layer=0; i_layer<sample->getNumberOfLayers(); ++i_layer) {
        std::map<double, complex_t> T_map;
        std::map<double, complex_t> R_map;
        for (std::map<double, OpticalFresnel::MultiLayerCoeff_t>::const_iterator it=fresnel_coeff_map.begin();
                it!=fresnel_coeff_map.end(); ++it) {
            double angle = (*it).first;
            complex_t T = (*it).second[i_layer].T;
            complex_t R = (*it).second[i_layer].R;
            T_map[angle] = T;
            R_map[angle] = R;
        }
        DoubleToComplexInterpolatingFunction T_function(T_map);
        DoubleToComplexInterpolatingFunction R_function(R_map, DoubleToComplexInterpolatingFunction::Nearest);

        m_TT[i_layer] = T_function.clone();
        m_RR[i_layer] = R_function.clone();
    }

    double alpha_min(0), alpha_max(2.0*Units::degree);
    int npoints = 200*2;

    TGraph *gr1_exact = new TGraph(npoints);
    TGraph *gr2_interp = new TGraph(npoints);
    TGraph *gr3_diff = new TGraph(npoints);

    for(int i_point=0; i_point < npoints; i_point++){
        int i_layer_sel = 0;
        double angle = alpha_min + i_point*(alpha_max-alpha_min)/double(npoints-1);
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(1.4*Units::angstrom, angle, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        fresnelCalculator.execute(*sample, kvec, coeffs);
        complex_t R = m_RR[i_layer_sel]->evaluate(angle);
        std::cout << i_point << " " << angle << " true R:" << coeffs[i_layer_sel].R << " interp:" << R << " " << std::abs(R - coeffs[i_layer_sel].R) << std::endl;
        complex_t r = coeffs[i_layer_sel].R;
//        std::cout << "RRR " << r << " abs:" << std::abs(r) << " arg:" << std::arg(r) << " " << Units::rad2deg(std::arg(r)) << std::endl << std::endl;
        gr1_exact->SetPoint(i_point, angle, std::abs(coeffs[i_layer_sel].R) );
        gr2_interp->SetPoint(i_point, angle, std::abs(R) );
        gr3_diff->SetPoint(i_point, angle, std::abs(R) - std::abs(coeffs[i_layer_sel].R) );
    }


    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,2);

    c1->cd(1);
    gr1_exact->SetTitle("exact");
    gr1_exact->Draw("apl");
    c1->cd(2);
    gr2_interp->SetTitle("interpolated");
    gr2_interp->Draw("apl");
    c1->cd(3);
    gr3_diff->SetTitle("difference");
    gr3_diff->Draw("apl");

}

//std::abs(coeffs[i_layer].R)

//    //MultiLayer *ml = dynamic_cast<MultiLayer *>(SampleFactory::createSample("IsGISAXS9_RotatedPyramid"));
//    MultiLayer *ml = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MesoCrystal1"));
//    std::cout << *ml << std::endl;
//    std::cout << "------------------------------------" << std::endl;
//    ml->walk_and_print();
//    std::cout << "------------------------------------" << std::endl;
//    ParameterPool *pool = ml->createParameterTree();
//    std::cout << *pool << std::endl;
//    std::cout << pool->setMatchedParametersValue("/*NanoParticleInfo*/depth",99);
//    ml->walk_and_print();
//    return;

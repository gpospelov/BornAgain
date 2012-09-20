#include "TestMiscellaneous.h"
#include "SampleFactory.h"
#include "OutputData.h"
#include "OpticalFresnel.h"
#include "Units.h"
#include "DoubleToComplexInterpolatingFunction.h"
#include "FormFactors.h"
#include "DrawHelper.h"
#include "GISASExperiment.h"
#include "IsGISAXSTools.h"
#include "Lattice.h"
#include "LayerDecorator.h"
#include "MesoCrystal.h"
#include "Crystal.h"
#include "LatticeBasis.h"

#include "TGraph.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TCanvas.h"
#include "TGraphPolar.h"

TestMiscellaneous::TestMiscellaneous()
{
}




void TestMiscellaneous::execute()
{

    test_DoubleToComplexInterpolatingFunction();
    //test_FormFactor();
    //test_DrawMesocrystal();
}


/* ************************************************************************* */
// test double to complex interpolating function
/* ************************************************************************* */
void TestMiscellaneous::test_DrawMesocrystal()
{

    MultiLayer *m_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("MesoCrystal2"));

    DrawHelper::instance().DrawMesoCrystal(m_sample);

//    GISASExperiment experiment;
//    experiment.setSample(m_sample);
//    experiment.setDetectorParameters(100, 0.3*Units::degree, 0.073 , 100 , -0.4*Units::degree, 0.066);
//    experiment.setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
//    experiment.setBeamIntensity(1e7);
//    experiment.runSimulation();
//    experiment.normalize();
//    OutputData<double> *mp_intensity_output = experiment.getOutputDataClone();
//    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_meso_crystal", "mesocrystal","CONT4 Z");

}



/* ************************************************************************* */
// test double to complex interpolating function
/* ************************************************************************* */
void TestMiscellaneous::test_FormFactor()
{

    FormFactorFullSphere ff_sphere(5.*Units::nanometer);
    FormFactorCylinder ff_cylinder(10.*Units::nanometer, 5.*Units::nanometer);

//    IFormFactor &ff = ff_cylinder;
    IFormFactor &ff = ff_sphere;

    double qmin(-4.0), qmax(4.0);
    int nbins(51);
    double dq = (qmax-qmin)/(nbins-1);

    TH1D *h1[3];
    h1[0] = new TH1D("h10","h10", nbins, qmin-dq/2., qmax+dq/2.);
    h1[1] = new TH1D("h11","h11", nbins, qmin-dq/2., qmax+dq/2.);
    h1[2] = new TH1D("h12","h12", nbins, qmin-dq/2., qmax+dq/2.);
    TH2D *h2 = new TH2D("h2","h2", nbins, qmin-dq/2., qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.);
    TH3D *h3 = new TH3D("h3","h3", nbins, qmin-dq/2., qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.,nbins, qmin-dq/2., qmax+dq/2.);


    std::vector<TH2D *> vh2_xy;
    std::vector<TH2D *> vh2_xz;
    std::vector<TH2D *> vh2_yz;

    vh2_xy.resize(nbins, 0);
    vh2_xz.resize(nbins, 0);
    vh2_yz.resize(nbins, 0);

    for(int i=0; i<nbins; ++i) {
        char str[128];
        sprintf(str, "h2_xy_z%d",i);
        vh2_xy[i] = new TH2D(str,str,nbins, qmin-dq/2., qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.);
        vh2_xy[i]->GetXaxis()->SetTitle("x");
        vh2_xy[i]->GetYaxis()->SetTitle("y");

        sprintf(str, "h2_xz_y%d",i);
        vh2_xz[i] = new TH2D(str,str,nbins, qmin-dq/2., qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.);
        vh2_xz[i]->GetXaxis()->SetTitle("x");
        vh2_xz[i]->GetYaxis()->SetTitle("z");

        sprintf(str, "h2_yz_x%d",i);
        vh2_yz[i] = new TH2D(str,str,nbins, qmin-dq/2., qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.);
        vh2_yz[i]->GetXaxis()->SetTitle("y");
        vh2_yz[i]->GetYaxis()->SetTitle("z");
    }


    OutputData<double > *data1 = new OutputData<double >;
    data1->addAxis(std::string("qx"), qmin, qmax, nbins);
    data1->addAxis(std::string("qy"), qmin, qmax, nbins);
    data1->addAxis(std::string("qz"), qmin, qmax, nbins);
    data1->resetIndex();
    while (data1->hasNext()) {
        double x = data1->getCurrentValueOfAxis<double>("qx");
        double y = data1->getCurrentValueOfAxis<double>("qy");
        double z = data1->getCurrentValueOfAxis<double>("qz");

        int ix = data1->getCurrentIndexOfAxis("qx");
        int iy = data1->getCurrentIndexOfAxis("qy");
        int iz = data1->getCurrentIndexOfAxis("qz");

        cvector_t q(x,y,z);
        cvector_t q0(0,0,0);
        double value = std::abs(ff.evaluate(q,q0, 0.0, 0.0));
//        complex_t qz(z,0.0);
//        std::cout << q << " " << std::abs(ff.evaluate(q,q0)) << std::endl;
        if(iz==50) h2->Fill(x,y,std::abs(ff.evaluate(q,q0, 0.0, 0.0)));
        //if(iy==0) h2->Fill(x,z,std::abs(ff.evaluate(q,q0)));
        //if(ix==0) h2->Fill(z,y,std::abs(ff.evaluate(q,q0)));

        h3->Fill(x,y,z,std::abs(ff.evaluate(q,q0, 0.0, 0.0)));

        if(iy==0 && iz==0) {
            cvector_t kx(x,1.0,1.0);
            cvector_t ky(1.0,x,1.0);
            cvector_t kz(1.0,1.0,x);
            h1[0]->Fill(x, std::abs(ff.evaluate(kx,q0, 0.0, 0.0)));
            h1[1]->Fill(x, std::abs(ff.evaluate(ky,q0, 0.0, 0.0)));
            h1[2]->Fill(x, std::abs(ff.evaluate(kz,q0, 0.0, 0.0)));
        }

        vh2_xy[iz] ->Fill(x,y,value);
        vh2_xz[iy] ->Fill(x,z,value);
        vh2_yz[ix] ->Fill(y,z,value);

        data1->next();
    }



//    TCanvas *c1 = new TCanvas("c1","c1",1024,768);
//    c1->Divide(2,2);
//    gStyle->SetPalette(1);

//    c1->cd(1);
//    gPad->SetLogz();
//    h2->Draw("surf2");
////    h3->Draw("iso");

//    for(int i=0; i<3; i++){
//        c1->cd(2+i);
//        h1[i]->Draw();
//    }

    TCanvas *c1_xy = new TCanvas("c1_xy","c1_xy",1024,768);
    DrawHelper::instance().SetMagnifier(c1_xy);
    c1_xy->Divide(3,3);
    int ndiv=9;
    for(int i=0; i<ndiv; i++) {
        c1_xy->cd(i+1);
        int indx = i*int(nbins/ndiv);
        std::cout << indx << std::endl;
        vh2_xy[indx]->Draw("surf");
    }

    TCanvas *c1_xz = new TCanvas("c1_xz","c1_xz",1024,768);
    DrawHelper::instance().SetMagnifier(c1_xz);
    c1_xz->Divide(3,3);
    for(int i=0; i<ndiv; i++) {
        c1_xz->cd(i+1);
        int indx = i*int(nbins/ndiv);
        vh2_xz[indx]->Draw("surf");
    }

    TCanvas *c1_yz = new TCanvas("c1_yz","c1_yz",1024,768);
    DrawHelper::instance().SetMagnifier(c1_yz);
    c1_yz->Divide(3,3);
    for(int i=0; i<ndiv; i++) {
        c1_yz->cd(i+1);
        int indx = i*int(nbins/ndiv);
        vh2_yz[indx]->Draw("surf");
    }


}


/* ************************************************************************* */
// test double to complex interpolating function
/* ************************************************************************* */
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

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
#include "OpticalFresnel.h"
#include "Units.h"
#include "DoubleToComplexInterpolatingFunction.h"
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
    test_PrintVisitor();
    //test_LogSystem();
    //test_OutputDataTo2DArray();
    //test_KVectorContainer();
    //test_OutputDataIOFactory();
    //test_FastSin();
    //test_DoubleToComplexInterpolatingFunction();
    //test_FormFactor1();
    //test_FormFactor();
    //test_DrawMesocrystal();
}


/* ************************************************************************* */
// test of log system
/* ************************************************************************* */
void TestMiscellaneous::test_PrintVisitor()
{
    std::cout << "TestMiscellaneous::test_PrintVisitor() ->" << std::endl;
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs04_2DDL");
    //std::cout << (*sample) << std::endl;

    SamplePrintVisitor visitor;
    sample->accept(&visitor);
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
    p_output->addAxis("phi_f", axis0_size, 0.0, double(axis0_size));
    p_output->addAxis("alpha_f", axis1_size, 0.0, double(axis1_size));
    p_output->setAllTo(0.0);

    OutputData<double>::iterator it = p_output->begin();
    int nn=0;
    while (it != p_output->end())
    {
        size_t index0 = p_output->getIndexOfAxis("phi_f", it.getIndex());
        size_t index1 = p_output->getIndexOfAxis("alpha_f", it.getIndex());
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
    std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_qyqz.txt.gz";
    OutputData<double > *data = OutputDataIOFactory::getOutputData(file_name);

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
//        std::cout << x << " " << std::sin(x) << " " << MathFunctions::FastSin<double, true>(x) << std::endl;
//        std::cout << "x:" << x << " std::sin " << std::sin(x) << " sine:" << sine(y) << " FastSin:" << MathFunctions::FastSin<double, true>(y) << std::endl;
        //std::cout << "xx:" << x << " std::sin " << std::sin(x) << " sine:" << sine1(mod_pi(x))  << std::endl;
//        double s1 = std::sin(x);
//        double s2 = sine2(x);
//        double s2 = MathFunctions::FastSin(x);
//        std::cout << "xx:" << x << " std::sin " << s1 << " sine:" << s2 << " diff:" << s1-s2 << std::endl;

        complex_t cx(x, x/2.);
        complex_t cs1 = std::sin(cx);
        complex_t cs2 = MathFunctions::FastSin(cx);
        std::cout << "xx:" << cx << " std::sin " << cs1 << " sine:" << cs2 << " diff:" << cs1-cs2 << std::endl;
    }

//    const int nevents = 1000000000;
////    TRandom mr;
////    mr.SetSeed(1);

//    TBenchmark mb;
//    mb.Start("sin");
//    for(int i=0; i<nevents; i++){
////        double x = mr.Rndm();
//        //double y = std::sin(1.0) + std::sin(2.0);
//        //double y = MathFunctions::FastSin(1.0)+MathFunctions::FastSin(2.0);
//        complex_t x(1.0,-.5);
//        //complex_t y = std::sin(x);
//        complex_t y = MathFunctions::FastComplexSin(x);
//        (void)y;
//    }
//    mb.Stop("sin");

//    mb.Show("sin");

}

/* ************************************************************************* */
// opengl mesocrystal drawing
/* ************************************************************************* */
void TestMiscellaneous::test_DrawMesocrystal()
{
    MultiLayer *m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MesoCrystal2"));
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
        cvector_t q0(0,0,0);
        Bin1DCVector q0_bin(q0, q0);
        double value = std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0));
        if(iz==50) h2->Fill(x,y,std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0)));

        h3->Fill(x,y,z,std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0)));

        if(iy==0 && iz==0) {
            cvector_t kx(x,1.0,1.0);
            cvector_t ky(1.0,x,1.0);
            cvector_t kz(1.0,1.0,x);
            h1[0]->Fill(x, std::abs(ff.evaluate(kx,q0_bin, 0.0, 0.0)));
            h1[1]->Fill(x, std::abs(ff.evaluate(ky,q0_bin, 0.0, 0.0)));
            h1[2]->Fill(x, std::abs(ff.evaluate(kz,q0_bin, 0.0, 0.0)));
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
   //   IFormFactor& ff = ff_pyramid;

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

    IFormFactor& ff = ff_fullsphere;

    double qmin(-4.0), qmax(4.0);
    double lambda = 1.0;
    double alpha_i = 0.2*M_PI/180.0;
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);
    //double phi_fmin(-4.0), phi_fmax(4.0), alpha_fmin(-4.), alpha_fmax(4.);
    int nbins(101);
    double dq =(qmax-qmin)/(nbins-1);
    //double dphi_f = (phi_fmax-phi_fmin)/(nbins-1);
    //double dalpha_f = (alpha_fmax-alpha_fmin)/(nbins-1);

    TH2D *vh2_xy = new TH2D("vh2_xy","vh2_xy;q_{x};q_{y};qz",nbins, qmin-dq/2., qmax+dq/2., nbins, qmin-dq/2., qmax+dq/2.);

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
        cvector_t q0(0,0,0);
        Bin1DCVector q0_bin(q0, q0);
        double value = std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0));
        //double valuep = std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0));
        //double valuer = std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0));
        //double valuei = std::abs(ff.evaluate(q,q0_bin, 0.0, 0.0));

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




    /*
    OutputData<double>::iterator it = mp_intensity_output->begin();
    const IAxis *p_y_axis = mp_intensity_output->getAxis("detector y-axis");
    const IAxis *p_z_axis = mp_intensity_output->getAxis("detector z-axis");
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);
    while (it != mp_intensity_output->end())
    {
        size_t index_y = mp_intensity_output->getIndexOfAxis("detector y-axis", it.getIndex());
        size_t index_z = mp_intensity_output->getIndexOfAxis("detector z-axis", it.getIndex());
        double phi_f = M_PI*(*p_y_axis)[index_y]/180.0;
        double alpha_f = M_PI*(*p_z_axis)[index_z]/180.0;
        cvector_t k_f;
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        Bin1DCVector k_f_zero_bin(k_f, k_f);
        *it = std::pow(std::abs(m_ff.evaluate(k_i, k_f_zero_bin, alpha_i, alpha_f)),2);
        ++it;
    }

    const IAxis *p_y_axis = mp_intensity_output->getAxis("detector y-axis");
    const IAxis *p_z_axis = mp_intensity_output->getAxis("detector z-axis");
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0];
    double y_end = (*p_y_axis)[y_size-1];
    double z_start = (*p_z_axis)[0];
    double z_end = (*p_z_axis)[z_size-1];
    p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle("phi_f");
    p_hist2D->GetYaxis()->SetTitle("alpha_f");
*/

    /*
    c1->Divide(2,2);

    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::setMinimum(hmin);
    if(hmax>0) IsGISAXSTools::setMaximum(hmax);

    TH1 *hist(0);
    hist = IsGISAXSTools::getOutputDataTH2D(output, "p_hist1D");
    if( hasMinimum() ) hist->SetMinimum(m_hist_min);
    if( hasMaximum() ) hist->SetMaximum(m_hist_max);
    hist->SetTitle(histogram_title.c_str());
    hist->DrawCopy(draw_options.c_str());

    // dealing with masks
    if(output.getMask()) {
        TPolyMarker *poly = new TPolyMarker();
        const IAxis *p_axis0 = output.getAxis(0);
        const IAxis *p_axis1 = output.getAxis(1);
        int i_point(0);
        for(OutputData<double>::const_iterator it = output.begin();
            it!= output.end(); ++it) {
            size_t axis0_index = output.toCoordinate(it.getIndex(), 0);
            size_t axis1_index = output.toCoordinate(it.getIndex(), 1);
            double axis0_value = (*p_axis0)[axis0_index];
            double axis1_value = (*p_axis1)[axis1_index];
            poly->SetPoint(i_point++, axis0_value, axis1_value);
        }
        poly->Draw("same");
    }
*/

}

/* ************************************************************************* */
// test double to complex interpolating function
/* ************************************************************************* */
void TestMiscellaneous::test_DoubleToComplexInterpolatingFunction()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MultilayerOffspecTestcase1a"));

    OutputData<double > *data_alpha = new OutputData<double >;
    data_alpha->addAxis("alpha_f", 200, 0.0*Units::degree, 2.0*Units::degree);

    OpticalFresnel FresnelCalculator;

    const IAxis *p_alpha_axis = data_alpha->getAxis("alpha_f");
    std::map<double, OpticalFresnel::MultiLayerCoeff_t> Fresnel_coeff_map;
    for (size_t i=0; i<p_alpha_axis->getSize(); ++i) {
        double angle = (*p_alpha_axis)[i];
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(1.4*Units::angstrom, angle, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        FresnelCalculator.execute(*sample, kvec, coeffs);
        Fresnel_coeff_map[angle] = coeffs;
    }

    std::vector<DoubleToComplexInterpolatingFunction *> m_TT;
    std::vector<DoubleToComplexInterpolatingFunction *> m_RR;
    m_TT.resize(sample->getNumberOfInterfaces(), 0);
    m_RR.resize(sample->getNumberOfInterfaces(), 0);

    for(size_t i_layer=0; i_layer<sample->getNumberOfLayers(); ++i_layer) {
        std::map<double, complex_t> T_map;
        std::map<double, complex_t> R_map;
        for (std::map<double, OpticalFresnel::MultiLayerCoeff_t>::const_iterator it=Fresnel_coeff_map.begin();
                it!=Fresnel_coeff_map.end(); ++it) {
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
        FresnelCalculator.execute(*sample, kvec, coeffs);
        complex_t R = m_RR[i_layer_sel]->evaluate(angle);
        std::cout << i_point << " " << angle << " true R:" << coeffs[i_layer_sel].R << " interp:" << R << " " << std::abs(R - coeffs[i_layer_sel].R) << std::endl;
//        complex_t r = coeffs[i_layer_sel].R;
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




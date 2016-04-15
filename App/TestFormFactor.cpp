// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFormFactor.cpp
//! @brief     Implements class TestFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFormFactor.h"
#include "Types.h"
#include "DrawHelper.h"
#include "FixedBinAxis.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"
#include "BornAgainNamespace.h"

#include <cmath>
#include <iostream>


TestFormFactor::TestFormFactor()
    : m_ff(50.0, 50.0)
{
    mp_intensity_output = new OutputData<double>();
    FixedBinAxis y_axis(std::string("detector y-axis"), 200, -4.0, 4.0);
    FixedBinAxis z_axis(std::string("detector z-axis"), 200, 0.0, 4.0);
    mp_intensity_output->addAxis(y_axis);
    mp_intensity_output->addAxis(z_axis);
}

TestFormFactor::~TestFormFactor()
{
    delete mp_intensity_output;
}

void TestFormFactor::execute()
{
    throw NotImplementedException("TestFormFactor::execute() -> Not implemeted");
//    OutputData<double>::iterator it = mp_intensity_output->begin();
//    const IAxis *p_y_axis = mp_intensity_output->getAxis("detector y-axis");
//    const IAxis *p_z_axis = mp_intensity_output->getAxis("detector z-axis");
//    double lambda = 1.0;
//    double alpha_i = 0.2*Units::PI/180.0;
//    cvector_t k_i;
//    k_i.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);
//    while (it != mp_intensity_output->end())
//    {
//        size_t index_y = mp_intensity_output->getAxisBinIndex(it.getIndex(), "detector y-axis");
//        size_t index_z = mp_intensity_output->getAxisBinIndex(it.getIndex(), "detector z-axis");
//        double phi_f = Units::PI*(*p_y_axis)[index_y]/180.0;
//        Bin1D alpha_f_bin_degrees = p_z_axis->getBin(index_z);
//        Bin1D alpha_f_bin(Units::PI*alpha_f_bin_degrees.m_lower/180.0,
//                              Units::PI*alpha_f_bin_degrees.m_upper/180.0);
//        double alpha_f = alpha_f_bin.getMidPoint();
//        cvector_t k_f;
//        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
//        Bin1DCVector k_f_zero_bin(k_f, k_f);
//        *it = std::pow(std::abs(m_ff.evaluate(k_i, k_f_zero_bin, alpha_f_bin)),2);
//        ++it;
//    }
//    draw4();
}


void TestFormFactor::draw4()
{
    TCanvas *c1_xy = new TCanvas("c1_test_formfactor", "Cylinder Formfactor", 1024, 768);
    gPad->SetRightMargin(0.11);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    DrawHelper::SetMagnifier(c1_xy);
     c1_xy->Divide(2,2);

    const IAxis *p_y_axis = mp_intensity_output->getAxis("detector y-axis");
    const IAxis *p_z_axis = mp_intensity_output->getAxis("detector z-axis");
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0];
    double y_end = (*p_y_axis)[y_size-1];
    double z_start = (*p_z_axis)[0];
    double z_end = (*p_z_axis)[z_size-1];

    std::vector<TH2D *> p_hist2Da;
    p_hist2Da.resize(4, 0);
   /* p_hist2Da[0] = new TH2D("p_hist2D", "Cylinder Formfactor Ampl", (int)y_size,
                           y_start, y_end, (int)z_size, z_start, z_end);
    p_hist2Da[1] = new TH2D("p_hist2D", "Cylinder Formfactor Re", (int)y_size,
                           y_start, y_end, (int)z_size, z_start, z_end);
    p_hist2Da[2] = new TH2D("p_hist2D", "Cylinder Formfactor Im", (int)y_size,
                           y_start, y_end, (int)z_size, z_start, z_end);*/

    for (int i=0; i<4;i++) {
        //p_hist2Da[i]->UseCurrentStyle();
        p_hist2Da[i] = new TH2D("p_hist2D", "Cylinder Formfactor", (int)y_size,
                                   y_start, y_end, (int)z_size, z_start, z_end);
        p_hist2Da[i]->GetXaxis()->SetTitle("phi_{f} (rad)");
        p_hist2Da[i]->GetYaxis()->SetTitle("alpha_{f} (rad)");
    }

    TH2D *p_hist2D = new TH2D("p_hist2D", "Cylinder Formfactor",
            (int)y_size, y_start, y_end, (int)z_size, z_start, z_end);
    //p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle("phi_{f} (rad)");
    p_hist2D->GetYaxis()->SetTitle("alpha_{f} (rad)");

    OutputData<double>::const_iterator it = mp_intensity_output->begin();
    //OutputData<double>::const_iterator it = mp_intensity_output->begin();
    while (it != mp_intensity_output->end())
    {
        size_t index_y = mp_intensity_output->getAxisBinIndex(it.getIndex(), "detector y-axis");
        size_t index_z = mp_intensity_output->getAxisBinIndex(it.getIndex(), "detector z-axis");
        double x_value = (*p_y_axis)[index_y];
        double y_value = (*p_z_axis)[index_z];
        double z_value = std::log(*it + 1.0);
        p_hist2D->Fill(x_value, y_value, z_value);
        p_hist2Da[0]->Fill(x_value, y_value, z_value);
        ++it;
    }

     c1_xy->cd(1);
     p_hist2D->SetContour(50);
     p_hist2D->Draw("CONT4 z");

     c1_xy->cd(2);

     p_hist2Da[0]->SetContour(99);
     p_hist2Da[0]->Draw("cont4 z");
}


void TestFormFactor::draw()
{
    // creation of 2D histogram from calculated intensities
    TCanvas *c1 = new TCanvas("c1_test_formfactor", "Cylinder Formfactor", 0, 0, 1024, 768);
    (void)c1;

    const IAxis *p_y_axis = mp_intensity_output->getAxis("detector y-axis");
    const IAxis *p_z_axis = mp_intensity_output->getAxis("detector z-axis");
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0];
    double y_end = (*p_y_axis)[y_size-1];
    double z_start = (*p_z_axis)[0];
    double z_end = (*p_z_axis)[z_size-1];
    TH2D *p_hist2D = new TH2D("p_hist2D", "Cylinder Formfactor", (int)y_size,
            y_start, y_end, (int)z_size, z_start, z_end);
    p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle("phi_f");
    p_hist2D->GetYaxis()->SetTitle("alpha_f");

    OutputData<double>::const_iterator it = mp_intensity_output->begin();
    while (it != mp_intensity_output->end())
    {
        size_t index_y = mp_intensity_output->getAxisBinIndex(it.getIndex(), "detector y-axis");
        size_t index_z = mp_intensity_output->getAxisBinIndex(it.getIndex(), "detector z-axis");
        double x_value = (*p_y_axis)[index_y];
        double y_value = (*p_z_axis)[index_z];
        double z_value = std::log(*it);
        p_hist2D->Fill(x_value, y_value, z_value);
        ++it;
    }
    p_hist2D->SetContour(50);
    gStyle->SetPalette(51);
    gStyle->SetOptStat(0);
    p_hist2D->Draw("CONT4");
}

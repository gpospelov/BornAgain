/*
 * TestDWBAFormFactor.cpp
 *
 *  Created on: May 2, 2012
 *      Author: herck
 */

#include "TestDWBAFormFactor.h"
#include "Types.h"

#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

#include <cmath>
#include <iostream>
#include <fstream>



TestDWBAFormFactor::TestDWBAFormFactor()
    : m_dwba_ff(new FormFactorCylinder(50.0, 50.0))
{
    m_dwba_ff.setReflectionFunction(new DoubleToComplexFunctionWrapper(reflection_fresnel));
    m_dwba_ff.setTransmissionFunction(new DoubleToComplexFunctionWrapper(transmission_fresnel));
    mp_intensity_output = new OutputData<double>();
    NamedVectorBase *p_y_axis = new NamedVector<double>(std::string("detector y-axis"), 0.0, 2.0, 100);
    NamedVectorBase *p_z_axis = new NamedVector<double>(std::string("detector z-axis"), 0.0, 2.0, 100);
    mp_intensity_output->addAxis(p_y_axis);
    mp_intensity_output->addAxis(p_z_axis);
}

TestDWBAFormFactor::~TestDWBAFormFactor()
{
    delete mp_intensity_output;
}

void TestDWBAFormFactor::execute()
{
    MultiIndex& index = mp_intensity_output->getIndex();
    NamedVector<double> *p_y_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector y-axis"));
    NamedVector<double> *p_z_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector z-axis"));
    double lambda = 1.0;
    double alpha_i = 0.2*M_PI/180.0;
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);
    while (!index.endPassed())
    {
        size_t index_y = index.getCoordinate("detector y-axis");
        size_t index_z = index.getCoordinate("detector z-axis");
        double phi_f = M_PI*(*p_y_axis)[index_y]/180.0;
        double alpha_f = M_PI*(*p_z_axis)[index_z]/180.0;
        kvector_t k_f;
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        mp_intensity_output->currentValue() = std::pow(std::abs(m_dwba_ff.evaluate(k_i, k_f)),2);
        ++index;
    }
    draw();
    write();
}

void TestDWBAFormFactor::draw()
{
    // creation of 2D histogram from calculated intensities
    TCanvas *c1 = new TCanvas("c1_test_dwba_formfactor", "Cylinder Formfactor", 0, 0, 1024, 768);
    (void)c1;

    MultiIndex& index = mp_intensity_output->getIndex();
    index.reset();
    NamedVector<double> *p_y_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector y-axis"));
    NamedVector<double> *p_z_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector z-axis"));
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0];
    double y_end = (*p_y_axis)[y_size-1];
    double z_start = (*p_z_axis)[0];
    double z_end = (*p_z_axis)[z_size-1];
    TH2D *p_hist2D = new TH2D("p_hist2D", "Cylinder DWBA Formfactor", y_size, y_start, y_end, z_size, z_start, z_end);
    //p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle("phi_f");
    p_hist2D->GetYaxis()->SetTitle("alpha_f");

    while (!index.endPassed())
    {
        size_t index_y = index.getCoordinate("detector y-axis");
        size_t index_z = index.getCoordinate("detector z-axis");
        double x_value = (*p_y_axis)[index_y];
        double y_value = (*p_z_axis)[index_z];
        double z_value = mp_intensity_output->currentValue();
        p_hist2D->Fill(x_value, y_value, z_value);
        ++index;
    }
    p_hist2D->SetContour(50);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    gPad->SetLogz();
    p_hist2D->SetMinimum(1e5);
    p_hist2D->Draw("CONT4");
}

void TestDWBAFormFactor::write()
{
    std::ofstream file;
    file.open("dwbacyl.ima", std::ios::out);
    mp_intensity_output->resetIndex();
    size_t row_length = mp_intensity_output->getAxes()[0]->getSize();
    int counter = 1;
    while(mp_intensity_output->hasNext()) {
        double z_value = mp_intensity_output->next();
        file << z_value << "    ";
        if(counter%row_length==0) {
            file << std::endl;
        }
        ++counter;
    }
}

complex_t reflection_fresnel(double alpha_i)
{
    complex_t refraction_index(1.0-6e-6, +2e-8);
    complex_t cos_alpha_0_squared = std::cos(alpha_i)*std::cos(alpha_i);
    complex_t f0 = std::sqrt(complex_t(1.0, 0.0) - cos_alpha_0_squared);
    complex_t f1 = std::sqrt(refraction_index*refraction_index - cos_alpha_0_squared);
    return (f0 - f1)/(f0 + f1);
}

complex_t transmission_fresnel(double alpha_i)
{
    (void)alpha_i;
    return complex_t(1.0, 0.0);
}

#include "TestFormFactor.h"
#include "Types.h"

#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

#include <cmath>
#include <iostream>


TestFormFactor::TestFormFactor()
    : m_ff(50.0, 50.0)
{
    mp_intensity_output = new OutputData<double>();
    NamedVectorBase *p_y_axis = new NamedVector<double>(std::string("detector y-axis"), -4.0, 4.0, 200);
    NamedVectorBase *p_z_axis = new NamedVector<double>(std::string("detector z-axis"), 0.0, 4.0, 200);
    mp_intensity_output->addAxis(p_y_axis);
    mp_intensity_output->addAxis(p_z_axis);
}

TestFormFactor::~TestFormFactor()
{
    delete mp_intensity_output;
}

void TestFormFactor::execute()
{
    OutputData<double>::iterator it = mp_intensity_output->begin();
    const NamedVector<double> *p_y_axis = dynamic_cast<const  NamedVector<double>*>(mp_intensity_output->getAxis("detector y-axis"));
    const NamedVector<double> *p_z_axis = dynamic_cast<const  NamedVector<double>*>(mp_intensity_output->getAxis("detector z-axis"));
    double lambda = 1.0;
    double alpha_i = 0.2*M_PI/180.0;
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
        *it = std::pow(std::abs(m_ff.evaluate(k_i, k_f, alpha_i, alpha_f)),2);
        ++it;
    }
    draw();
}

void TestFormFactor::draw()
{
    // creation of 2D histogram from calculated intensities
    TCanvas *c1 = new TCanvas("c1_test_formfactor", "Cylinder Formfactor", 0, 0, 1024, 768);
    (void)c1;

    const NamedVector<double> *p_y_axis = dynamic_cast<const NamedVector<double>*>(mp_intensity_output->getAxis("detector y-axis"));
    const NamedVector<double> *p_z_axis = dynamic_cast<const NamedVector<double>*>(mp_intensity_output->getAxis("detector z-axis"));
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0];
    double y_end = (*p_y_axis)[y_size-1];
    double z_start = (*p_z_axis)[0];
    double z_end = (*p_z_axis)[z_size-1];
    TH2D *p_hist2D = new TH2D("p_hist2D", "Cylinder Formfactor", (int)y_size, y_start, y_end, (int)z_size, z_start, z_end);
    p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle("phi_f");
    p_hist2D->GetYaxis()->SetTitle("alpha_f");

    OutputData<double>::const_iterator it = mp_intensity_output->begin();
    while (it != mp_intensity_output->end())
    {
        size_t index_y = mp_intensity_output->getIndexOfAxis("detector y-axis", it.getIndex());
        size_t index_z = mp_intensity_output->getIndexOfAxis("detector z-axis", it.getIndex());
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

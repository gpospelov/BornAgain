#include "TestFormFactor.h"
#include "Types.h"

#include "TGraph2D.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TStyle.h"

#include <cmath>
#include <iostream>

TestFormFactor::TestFormFactor()
    : m_ff(50.0, 50.0)
{
    mp_intensity_output = new OutputData<double>();
    NamedVectorBase *p_y_axis = new NamedVector<double>(std::string("detector y-axis"), 0.0, 1.0, 50);
    NamedVectorBase *p_z_axis = new NamedVector<double>(std::string("detector z-axis"), 0.0, 1.0, 50);
    mp_intensity_output->addAxis(p_y_axis);
    mp_intensity_output->addAxis(p_z_axis);
}

TestFormFactor::~TestFormFactor()
{
    delete mp_intensity_output;
}

void TestFormFactor::execute()
{
    MultiIndex& index = mp_intensity_output->getIndex();
    NamedVector<double> *p_y_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector y-axis"));
    NamedVector<double> *p_z_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector z-axis"));
    double lambda = 1.0;
    double alpha_i = 0.003;
    double D = 30.0;
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, 0.0);
    while (!index.endPassed())
    {
        size_t index_y = index.getCoordinate("detector y-axis");
        size_t index_z = index.getCoordinate("detector z-axis");
        // std::cout << "index y: " << index_y << "   index z: " << index_z << std::endl;
        double phi_f = std::atan((*p_y_axis)[index_y]/D);
        double alpha_f = std::atan((*p_z_axis)[index_z]*std::cos(phi_f)/D);
        kvector_t k_f;
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        kvector_t q = k_f - k_i;
        mp_intensity_output->currentValue() = std::pow(std::abs(m_ff.evaluate(q)),2);
        ++index;
    }
    draw();
}

void TestFormFactor::draw()
{
    // creation TGraph2D from calcualted intensities
    TCanvas *c1 = new TCanvas("c1", "Formfactor cylinder", 0, 0, 600, 400);
    TGraph2D *p_graph = new TGraph2D();

    MultiIndex& index = mp_intensity_output->getIndex();
    index.reset();
    NamedVector<double> *p_y_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector y-axis"));
    NamedVector<double> *p_z_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("detector z-axis"));
    int point_index = 0;
    while (!index.endPassed())
    {
        size_t index_y = index.getCoordinate("detector y-axis");
        size_t index_z = index.getCoordinate("detector z-axis");
        double x_value = (*p_y_axis)[index_y];
        double y_value = (*p_z_axis)[index_z];
        double z_value = std::log(mp_intensity_output->currentValue());
        p_graph->SetPoint(point_index, x_value, y_value, z_value);
        ++index;
        ++point_index;
    }
    std::cout << point_index << "TGraph2D initilialized" << std::endl;
    //gStyle->SetPalette(1);
    p_graph->Draw("CONT4Z");
}

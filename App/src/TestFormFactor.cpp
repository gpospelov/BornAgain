#include "TestFormFactor.h"
#include "Types.h"

#include <cmath>

TestFormFactor::TestFormFactor()
    : m_ff(1.0, 0.3)
{
    mp_intensity_output = new OutputData<double>();
    NamedVectorBase *p_y_axis = new NamedVector<double>(std::string("detector y-axis"), -1.0, 0.02, 100);
    NamedVectorBase *p_z_axis = new NamedVector<double>(std::string("detector z-axis"), 0.0, 0.02, 100);
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
    double alpha_i = 0.0;
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, 0.0);
    while (index.getPosition()<index.getSize())
    {
        size_t index_y = index.getCoordinate("detector y-axis");
        size_t index_z = index.getCoordinate("detector z-axis");
        double phi_f = std::atan((*p_y_axis)[index_y]);
        double alpha_f = std::atan((*p_z_axis)[index_z]*std::cos(phi_f));
        kvector_t k_f;
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        kvector_t q = k_f - k_i;
        mp_intensity_output->currentValue() = std::abs(m_ff.evaluate(q));
        ++index;
    }
}

void TestFormFactor::draw()
{

}

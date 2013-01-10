#include "LayerDWBASimulation.h"

LayerDWBASimulation::LayerDWBASimulation()
    : mp_kz_function(0)
    , mp_RT_function(0)
{
}

LayerDWBASimulation::~LayerDWBASimulation()
{
    delete mp_kz_function;
    delete mp_RT_function;
}

void LayerDWBASimulation::setKzFunction(const IDoubleToComplexMap& kz_function)
{
    delete mp_kz_function;
    mp_kz_function = kz_function.clone();
}

void LayerDWBASimulation::setReflectionTransmissionFunction(const IDoubleToPairOfComplexMap &rt_function)
{
    delete mp_RT_function;
    mp_RT_function = rt_function.clone();
}

void LayerDWBASimulation::setKzAndRTFunctions(const IDoubleToComplexMap &kz_function, const IDoubleToPairOfComplexMap &rt_map)
{
    setKzFunction(kz_function);
    setReflectionTransmissionFunction(rt_map);
}

Bin1DCVector LayerDWBASimulation::getKfBin(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    assert(mp_kz_function != NULL);
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    k_f_bin.m_q_lower.setZ(mp_kz_function->evaluate(alpha_bin.m_lower));
    k_f_bin.m_q_upper.setZ(mp_kz_function->evaluate(alpha_bin.m_upper));
    return k_f_bin;
}

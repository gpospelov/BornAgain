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

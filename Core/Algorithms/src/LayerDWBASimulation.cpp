#include "LayerDWBASimulation.h"

LayerDWBASimulation::LayerDWBASimulation()
: mp_kz_function(0)
, mp_T_function(0)
, mp_R_function(0)
{
}

LayerDWBASimulation::~LayerDWBASimulation()
{
    delete mp_kz_function;
    delete mp_T_function;
    delete mp_R_function;
}

void LayerDWBASimulation::setKzFunction(
        const IDoubleToComplexFunction& kz_function)
{
    mp_kz_function = kz_function.clone();
}

void LayerDWBASimulation::setTFunction(
        const IDoubleToComplexFunction& T_function)
{
    mp_T_function = T_function.clone();
}

void LayerDWBASimulation::setRFunction(
        const IDoubleToComplexFunction& R_function)
{
    mp_R_function = R_function.clone();
}

void LayerDWBASimulation::setKzTAndRFunctions(
        const IDoubleToComplexFunction& kz_function,
        const IDoubleToComplexFunction& T_function,
        const IDoubleToComplexFunction& R_function)
{
    setKzFunction(kz_function);
    setTFunction(T_function);
    setRFunction(R_function);
}

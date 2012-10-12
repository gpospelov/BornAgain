#include "LayerDWBASimulation.h"

LayerDWBASimulation::LayerDWBASimulation()
//: mp_kz_function(0)
//, mp_T_function(0)
//, mp_R_function(0)
    : mp_kz_function(0)
    , mp_RT_function(0)
{
}

LayerDWBASimulation::~LayerDWBASimulation()
{
//    delete mp_kz_function;
//    delete mp_T_function;
//    delete mp_R_function;
    delete mp_kz_function;
    delete mp_RT_function;
}


//void LayerDWBASimulation::setKzFunction(
//        const IDoubleToComplexFunction& kz_function)
//{
//    delete mp_kz_function;
//    mp_kz_function = kz_function.clone();
//}

//void LayerDWBASimulation::setTFunction(
//        const IDoubleToComplexFunction& T_function)
//{
//    delete mp_T_function;
//    mp_T_function = T_function.clone();
//}

//void LayerDWBASimulation::setRFunction(
//        const IDoubleToComplexFunction& R_function)
//{
//    delete mp_R_function;
//    mp_R_function = R_function.clone();
//}

//void LayerDWBASimulation::setKzTAndRFunctions(
//        const IDoubleToComplexFunction& kz_function,
//        const IDoubleToComplexFunction& T_function,
//        const IDoubleToComplexFunction& R_function)
//{
//    setKzFunction(kz_function);
//    setTFunction(T_function);
//    setRFunction(R_function);
//}


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

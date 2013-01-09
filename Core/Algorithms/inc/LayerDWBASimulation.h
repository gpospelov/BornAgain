#ifndef LAYERDWBASIMULATION_H_
#define LAYERDWBASIMULATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LayerDWBASimulation.h
//! @brief  Definition of LayerDWBASimulation class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 25, 2012

#include "DWBASimulation.h"
#include "IDoubleToComplexFunction.h"

class LayerDWBASimulation : public DWBASimulation
{
public:
   LayerDWBASimulation();
   virtual ~LayerDWBASimulation();

   void setKzFunction(const IDoubleToComplexMap &kz_function);
   void setReflectionTransmissionFunction(const IDoubleToPairOfComplexMap &rt_map);
   void setKzAndRTFunctions(const IDoubleToComplexMap &kz_function, const IDoubleToPairOfComplexMap &rt_map);

protected:
   Bin1DCVector getKfBin(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin) const;
   IDoubleToComplexMap *mp_kz_function;
   IDoubleToPairOfComplexMap *mp_RT_function;

private:
   //! copy constructor and assignment operator are hidden
   LayerDWBASimulation(const LayerDWBASimulation &);
   LayerDWBASimulation &operator=(const LayerDWBASimulation &);
};

#endif /* LAYERDWBASIMULATION_H_ */

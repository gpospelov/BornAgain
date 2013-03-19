// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/LayerDWBASimulation.h
//! @brief     Defines class LayerDWBASimulation.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef LAYERDWBASIMULATION_H_
#define LAYERDWBASIMULATION_H_

#include "DWBASimulation.h"
#include "IDoubleToComplexFunction.h"

//! ?

class LayerDWBASimulation : public DWBASimulation
{
public:
   LayerDWBASimulation();
   virtual ~LayerDWBASimulation();

   LayerDWBASimulation *clone() const {  throw NotImplementedException("ISimulation::clone() -> Error: not implemented exception."); }

   void setKzFunction(const IDoubleToComplexMap &kz_function);
   void setReflectionTransmissionFunction(const IDoubleToPairOfComplexMap &rt_map);
   void setKzAndRTFunctions(const IDoubleToComplexMap &kz_function, const IDoubleToPairOfComplexMap &rt_map);

protected:
   Bin1DCVector getKfBin(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin) const;
   IDoubleToComplexMap *mp_kz_function;
   IDoubleToPairOfComplexMap *mp_RT_function;
};

#endif /* LAYERDWBASIMULATION_H_ */

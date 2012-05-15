#ifndef DWBADIFFUSEREFLECTION_H
#define DWBADIFFUSEREFLECTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DWBADiffuseReflection.h
//! @brief  Definition of DWBADiffuseReflection class for multi-layers
//! @author Scientific Computing Group at FRM II
//! @date   02.05.2012

#include "ISimulation.h"
#include "Units.h"
#include "MultiLayer.h"


//- -------------------------------------------------------------------
//! @class DWBADiffuseReflection
//! @brief Calculation of diffuse (aka off-specular) reflection from multilayers.
//- -------------------------------------------------------------------
class DWBADiffuseReflection : public ISimulation
{
public:
    DWBADiffuseReflection();


    static double execute(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf);

};

#endif // DWBADIFFUSEREFLECTION_H

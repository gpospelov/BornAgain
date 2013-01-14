#ifndef DETECTORPARAMETERS_H_
#define DETECTORPARAMETERS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DetectorParameters.h
//! @brief  Definition of DetectorParameters class
//! @author Scientific Computing Group at FRM II
//! @date   Dec 12, 2012

#include "TRange.h"

//- -------------------------------------------------------------------
//! @class AxisParameters
//! @brief Definition of AxisParameters class to store parameters
//! for specifying an axis' data
//- -------------------------------------------------------------------
struct AxisParameters
{
    AxisParameters();
    std::string m_name;
    TSampledRange<double> m_range;
    enum {
        E_DEFAULT,
        E_ISGISAXS,
    } m_sample_method;
};

inline AxisParameters::AxisParameters()
: m_name("")
, m_range(0, 0.0, 0.0)
, m_sample_method(AxisParameters::E_DEFAULT)
{
}

//- -------------------------------------------------------------------
//! @class DetectorParameters
//! @brief Definition of DetectorParameters class to store parameters
//! for specifying a 2D detector
//- -------------------------------------------------------------------
struct DetectorParameters
{
    AxisParameters m_phi_params;
    AxisParameters m_alpha_params;
};

#endif /* DETECTORPARAMETERS_H_ */


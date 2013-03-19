// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/DetectorParameters.h
//! @brief     Defines struct AxisParameters and struct DetectorParameters.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef DETECTORPARAMETERS_H_
#define DETECTORPARAMETERS_H_

#include "TRange.h"

//! Store parameters for specifying one axis

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

//! Store parameters for specifying a 2D detector.

struct DetectorParameters
{
    AxisParameters m_phi_params;
    AxisParameters m_alpha_params;
};

#endif /* DETECTORPARAMETERS_H_ */

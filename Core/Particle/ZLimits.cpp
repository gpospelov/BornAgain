// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/ZLimits.cpp
//! @brief     Defines class ZLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "ZLimits.h"


ZLimits::ZLimits(ZLimits::Type type, double ref)
    : m_type(type)
    , m_min(ref)
    , m_max {}
{}

ZLimits::ZLimits(double min, double max)
    : m_type(FINITE)
    , m_min(min)
    , m_max(max)
{}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitProgressInfo.cpp
//! @brief     Implements class FitProgressInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitProgressInfo.h"

FitProgressInfo::FitProgressInfo()
    : m_chi2(0.0)
    , m_iteration_count(0)
{

}

//! Copy constructor is reimplemented as required by Qt's meta-object system

FitProgressInfo::FitProgressInfo(const FitProgressInfo &other)
{
    m_chi2 = other.m_chi2;
    m_iteration_count = other.m_iteration_count;
    m_values = other.m_values;
}

//! Destructor is reimplemented as required by Qt's meta-object system

FitProgressInfo::~FitProgressInfo()
{

}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterItem.cpp
//! @brief     Implements class FitParameterItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterItem.h"

const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";
const QString FitParameterItem::P_VALUE = "Value";
const QString FitParameterItem::P_USE = "Use";

FitParameterItem::FitParameterItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterType, parent)
{
    registerProperty(P_NAME, Constants::FitParameterType);
    registerProperty(P_MIN, 0.0);
    registerProperty(P_MAX, 10.0);
    registerProperty(P_VALUE, 5.0);
    registerProperty(P_USE, true);
}

void FitParameterItem::setParNames(QStringList par_names)
{
    m_par_names = par_names;
}

QStringList FitParameterItem::getParNames()
{
    return m_par_names;
}



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

#include "ObsoleteFitParameterItem.h"

const QString ObsoleteFitParameterItem::P_MIN = "Min";
const QString ObsoleteFitParameterItem::P_MAX = "Max";
const QString ObsoleteFitParameterItem::P_VALUE = "Value";
const QString ObsoleteFitParameterItem::P_USE = "Use";

ObsoleteFitParameterItem::ObsoleteFitParameterItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterType, parent)
{
    setItemName(Constants::FitParameterType);
    addToValidChildren(Constants::FitParameterType);
    registerProperty(P_MIN, 0.0);
    registerProperty(P_MAX, 10.0);
    registerProperty(P_VALUE, 5.0);
    registerProperty(P_USE, true);
}

void ObsoleteFitParameterItem::setParNames(QStringList par_names)
{
    m_par_names = par_names;
}

QStringList ObsoleteFitParameterItem::getParNames()
{
    return m_par_names;
}



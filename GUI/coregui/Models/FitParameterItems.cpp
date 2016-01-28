// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.cpp
//! @brief     Implements class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterItems.h"


const QString FitParameterItem::P_USE = "use";
const QString FitParameterItem::P_INIT = "init";
const QString FitParameterItem::P_MIN = "min";
const QString FitParameterItem::P_MAX = "max";

FitParameterItem::FitParameterItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterType, parent)
{
    registerProperty(P_NAME, Constants::FitParameterType);
    registerProperty(P_USE, false);
    registerProperty(P_INIT, 5.0);
    registerProperty(P_MIN, 0.0);
    registerProperty(P_MAX, 10.0);
    addToValidChildren(Constants::FitParameterLinkType);
}

const QString FitParameterLinkItem::P_LINK = "link";

FitParameterLinkItem::FitParameterLinkItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterLinkType, parent)
{
    registerProperty(P_LINK, Constants::FitParameterLinkType);
}


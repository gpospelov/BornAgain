// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterItems.cpp
//! @brief     Implements class FitParameterItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterItems.h"
#include "ComboProperty.h"

FitParameterContainerItem::FitParameterContainerItem()
    : SessionItem(Constants::FitParameterContainerType)
{
    const QString T_DATA = "Data tag";
    registerTag(T_DATA, 0, -1, QStringList() << Constants::FitParameterType);
    setDefaultTag(T_DATA);
}


const QString FitParameterItem::P_USE = "Use";
const QString FitParameterItem::P_INIT = "Starting Value";
const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";

FitParameterItem::FitParameterItem()
    : SessionItem(Constants::FitParameterType)
{
    addProperty(P_USE, true);
    addProperty(P_INIT, 0.0);
    addProperty(P_MIN, 0.0);
    addProperty(P_MAX, 0.0);
    const QString T_LINK = "Link tag";
    registerTag(T_LINK, 0, -1, QStringList() << Constants::FitParameterLinkType);
    setDefaultTag(T_LINK);
}

const QString FitParameterLinkItem::P_LINK = "Link";

FitParameterLinkItem::FitParameterLinkItem()
    : SessionItem(Constants::FitParameterLinkType)
{
    addProperty(P_LINK, "");
}


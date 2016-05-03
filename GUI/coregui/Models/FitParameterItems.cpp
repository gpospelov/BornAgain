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

// ----------------------------------------------------------------------------

const QString FitParameterLinkItem::P_LINK = "Link";
const QString FitParameterLinkItem::P_DOMAIN = "Domain";

FitParameterLinkItem::FitParameterLinkItem()
    : SessionItem(Constants::FitParameterLinkType)
{
    addProperty(P_LINK, "");
    addProperty(P_DOMAIN, "");
}

// ----------------------------------------------------------------------------

const QString FitParameterItem::P_USE = "Use";
const QString FitParameterItem::P_START_VALUE = "Starting Value";
const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";
const QString FitParameterItem::T_LINK = "Link tag";

FitParameterItem::FitParameterItem()
    : SessionItem(Constants::FitParameterType)
{
    addProperty(P_USE, true);
    addProperty(P_START_VALUE, 0.0);
    addProperty(P_MIN, 0.0);
    addProperty(P_MAX, 0.0);
    registerTag(T_LINK, 0, -1, QStringList() << Constants::FitParameterLinkType);
    setDefaultTag(T_LINK);
}

// ----------------------------------------------------------------------------

const QString FitParameterContainerItem::T_FIT_PARAMETERS = "Data tag";

FitParameterContainerItem::FitParameterContainerItem()
    : SessionItem(Constants::FitParameterContainerType)
{
    registerTag(T_FIT_PARAMETERS, 0, -1, QStringList() << Constants::FitParameterType);
    setDefaultTag(T_FIT_PARAMETERS);
}

//! returns FitParameterItem for given link (path in model)
FitParameterItem *FitParameterContainerItem::getFitParameterItem(const QString &link)
{
    foreach(SessionItem *item, getItems(T_FIT_PARAMETERS)) {
        foreach(SessionItem *linkItem, item->getItems(FitParameterItem::T_LINK)) {
            if(link == linkItem->getItemValue(FitParameterLinkItem::P_LINK)) {
                return dynamic_cast<FitParameterItem *>(item);
            }
        }
    }
    return nullptr;
}

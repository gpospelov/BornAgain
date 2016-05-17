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
#include "ModelPath.h"
#include "SessionModel.h"
#include <QDebug>

namespace
{

QStringList getFitParTypeTooltips()
{
    QStringList result;
    result.append(QStringLiteral("Fixed at given value"));
    result.append(QStringLiteral("Limited in the range [min, max]"));
    result.append(QStringLiteral("Limited at lower bound [min, inf]"));
    result.append(QStringLiteral("Limited at upper bound [-inf, max]"));
    result.append(QStringLiteral("No limits imposed to parameter value"));
    return result;
}

}


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

const QString FitParameterItem::P_TYPE = "Type";
const QString FitParameterItem::P_START_VALUE = "Value";
const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";
const QString FitParameterItem::T_LINK = "Link tag";

FitParameterItem::FitParameterItem()
    : SessionItem(Constants::FitParameterType)
{
    ComboProperty partype;
    partype << Constants::FITPAR_FIXED << Constants::FITPAR_LIMITED
            << Constants::FITPAR_LOWERLIMITED
            << Constants::FITPAR_UPPERLIMITED << Constants::FITPAR_FREE;
    partype.setValue(Constants::FITPAR_LIMITED);
    partype.setToolTips(getFitParTypeTooltips());

    addProperty(P_TYPE, partype.getVariant());
    addProperty(P_START_VALUE, 0.0);
    addProperty(P_MIN, 0.0);
    addProperty(P_MAX, 0.0)->setEnabled(false);
    registerTag(T_LINK, 0, -1, QStringList() << Constants::FitParameterLinkType);
    setDefaultTag(T_LINK);

    mapper()->setOnPropertyChange(
                [this](const QString &name) {
        if(name == P_TYPE)
            onTypeChange();
    });

    onTypeChange();
}

//! init value, min, max from given ParameterItem

//void FitParameterItem::initFromParameterItem(ParameterItem *parItem)
//{


//}

//! Enables/disables min, max properties on FitParameterItem's type

void FitParameterItem::onTypeChange()
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    if(partype.getValue() == Constants::FITPAR_FIXED) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, false);
    }

    else if(partype.getValue() == Constants::FITPAR_LIMITED) {
        setLimitEnabled(P_MIN, true);
        setLimitEnabled(P_MAX, true);
    }

    else if(partype.getValue() == Constants::FITPAR_LOWERLIMITED) {
        setLimitEnabled(P_MIN, true);
        setLimitEnabled(P_MAX, false);
    }

    else if(partype.getValue() == Constants::FITPAR_UPPERLIMITED) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, true);
    }

    else if(partype.getValue() == Constants::FITPAR_FREE) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, false);
    }
}

//! Set limit property with given name to the enabled state

void FitParameterItem::setLimitEnabled(const QString &name, bool enabled)
{
    if(isTag(name)) {
        SessionItem *propertyItem = getItem(name);
        Q_ASSERT(propertyItem);
        propertyItem->setEnabled(enabled);
        propertyItem->setEditable(enabled);
    }
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

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterItems.cpp
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
#include "GUIHelpers.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"
#include <cmath>

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

const double range_factor = 0.5;

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

//! Inits P_MIN and P_MAX taking into account current value and external limits

void FitParameterItem::initMinMaxValues(const RealLimits &limits)
{
    double value = getItemValue(P_START_VALUE).toDouble();

    double dr(0);
    if(value == 0.0) {
        dr = 1.0*range_factor;
    } else {
        dr = std::abs(value)*range_factor;
    }

    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    if(partype.getValue() == Constants::FITPAR_LIMITED) {
        double min = value - dr;
        double max = value + dr;
        if(limits.hasLowerLimit() && min <limits.getLowerLimit()) min = limits.getLowerLimit();
        if(limits.hasUpperLimit() && max >limits.getUpperLimit()) max = limits.getUpperLimit();
        setItemValue(P_MIN, min);
        setItemValue(P_MAX, max);
    }
}

//! Constructs Limits correspodning to current GUI settings.

AttLimits FitParameterItem::getAttLimits()
{
    if(isFixed()) {
        return AttLimits::fixed();
    }

    else if(isLimited()) {
        return AttLimits::limited(getItemValue(P_MIN).toDouble(), getItemValue(P_MAX).toDouble());
    }

    else if(isLowerLimited()) {
        return AttLimits::lowerLimited(getItemValue(P_MIN).toDouble());
    }

    else if(isUpperLimited()) {
        return AttLimits::upperLimited(getItemValue(P_MAX).toDouble());
    }

    else if(isFree()) {
        return AttLimits::limitless();
    }

    else {
        throw GUIHelpers::Error("FitParameterItem::getLimits() -> Error. Unknown limit type");
    }
}

//! Enables/disables min, max properties on FitParameterItem's type

void FitParameterItem::onTypeChange()
{
    if(isFixed()) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, false);
    }

    else if(isLimited()) {
        setLimitEnabled(P_MIN, true);
        setLimitEnabled(P_MAX, true);
    }

    else if(isLowerLimited()) {
        setLimitEnabled(P_MIN, true);
        setLimitEnabled(P_MAX, false);
    }

    else if(isUpperLimited()) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, true);
    }

    else if(isFree()) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, false);
    }
}

//! Set limit property with given name to the enabled state

void FitParameterItem::setLimitEnabled(const QString &name, bool enabled)
{
    if(isTag(name)) {
        SessionItem* propertyItem = getItem(name);
        Q_ASSERT(propertyItem);
        propertyItem->setEnabled(enabled);
        propertyItem->setEditable(enabled);
    }
}

bool FitParameterItem::isLimited() const
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    return partype.getValue() == Constants::FITPAR_LIMITED;
}

bool FitParameterItem::isFree() const
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    return partype.getValue() == Constants::FITPAR_FREE;
}

bool FitParameterItem::isLowerLimited() const
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    return partype.getValue() == Constants::FITPAR_LOWERLIMITED;
}

bool FitParameterItem::isUpperLimited() const
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    return partype.getValue() == Constants::FITPAR_UPPERLIMITED;
}

bool FitParameterItem::isFixed() const
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    return partype.getValue() == Constants::FITPAR_FIXED;
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
FitParameterItem* FitParameterContainerItem::getFitParameterItem(const QString &link)
{
    foreach(SessionItem* item, getItems(T_FIT_PARAMETERS)) {
        foreach(SessionItem* linkItem, item->getItems(FitParameterItem::T_LINK)) {
            if(link == linkItem->getItemValue(FitParameterLinkItem::P_LINK)) {
                return dynamic_cast<FitParameterItem*>(item);
            }
        }
    }
    return nullptr;
}

QVector<FitParameterItem*> FitParameterContainerItem::fitParameterItems()
{
    QVector<FitParameterItem*> result;
    foreach(SessionItem* parItem, getItems(T_FIT_PARAMETERS))
        result.push_back(dynamic_cast<FitParameterItem*>(parItem));
    return result;
}

bool FitParameterContainerItem::isEmpty()
{
    return getItems(T_FIT_PARAMETERS).isEmpty();
}

//! Propagate values to the corresponding parameter tree items of parameterContainer.

void FitParameterContainerItem::setValuesInParameterContainer(
    const QVector<double> &values, ParameterContainerItem* parameterContainer)
{
    Q_ASSERT(parameterContainer);

    QVector<SessionItem*> fitPars = getItems(FitParameterContainerItem::T_FIT_PARAMETERS);

    if(fitPars.size() != values.size())
        throw GUIHelpers::Error(" FitParameterContainerItem::setValuesInParameterContainer() -> "
                                "Error. Wrong size of value vector.");

    for(int i=0; i<fitPars.size(); ++i) {
        foreach(SessionItem* linkItem, fitPars[i]->getItems(FitParameterItem::T_LINK)) {
            QString parPath = linkItem->getItemValue(FitParameterLinkItem::P_LINK).toString();
            SessionItem* itemInTuningTree = ModelPath::getItemFromPath(parPath, parameterContainer);
            Q_ASSERT(itemInTuningTree);
            itemInTuningTree->setValue(values[i]);
        }
    }
}

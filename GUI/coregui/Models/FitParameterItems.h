// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterItems.h
//! @brief     Defines class FitParameterItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#ifndef FITPARAMETERITEMS_H
#define FITPARAMETERITEMS_H

#include "SessionItem.h"
#include "AttLimits.h"

//! FitParameterItems is a collection of items to define fit parameters in GUI.

//! The FitParameterLinkItem class holds a link to ParameterItem in tuning tree.

class BA_CORE_API_ FitParameterLinkItem : public SessionItem
{

public:
    static const QString P_LINK;
    static const QString P_DOMAIN;
    explicit FitParameterLinkItem();
};

//! The FitParameterItem class represents a fit parameter in GUI. Contains links to corresponding
//! ParameterItem's in a tuning tree.

class BA_CORE_API_ FitParameterItem : public SessionItem
{

public:
    static const QString P_TYPE;
    static const QString P_START_VALUE;
    static const QString P_MIN;
    static const QString P_MAX;
    static const QString T_LINK;
    explicit FitParameterItem();

    void initMinMaxValues(const RealLimits &limits);

    AttLimits getAttLimits();

private:
    void onTypeChange();
    void setLimitEnabled(const QString &name, bool enabled);
    bool isLimited() const;
    bool isFree() const;
    bool isLowerLimited() const;
    bool isUpperLimited() const;
    bool isFixed() const;
};

//! The FitParameterContainerItem class is a collection of all defined fit parameters in JobItem.

class BA_CORE_API_ FitParameterContainerItem : public SessionItem
{

public:
    static const QString T_FIT_PARAMETERS;
    explicit FitParameterContainerItem();
    FitParameterItem *getFitParameterItem(const QString &link);
    QVector<FitParameterItem *> fitParameterItems();
    bool isEmpty();
    void setValuesInParameterContainer(const QVector<double> &values,
                                       class ParameterContainerItem *parameterContainer);
};

#endif // FITPARAMETERITEMS_H

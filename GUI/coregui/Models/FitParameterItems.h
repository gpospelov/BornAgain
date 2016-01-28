// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef FITPARAMETERITEMS_H
#define FITPARAMETERITEMS_H

#include "ParameterizedItem.h"

class BA_CORE_API_ FitParameterSettings : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit FitParameterSettings(ParameterizedItem *parent=0);
};

class BA_CORE_API_ FitParameterItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_USE;
    static const QString P_INIT;
    static const QString P_MIN;
    static const QString P_MAX;
    explicit FitParameterItem(ParameterizedItem *parent=0);
};


class BA_CORE_API_ FitParameterLinkItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LINK;
    explicit FitParameterLinkItem(ParameterizedItem *parent=0);
};

#endif

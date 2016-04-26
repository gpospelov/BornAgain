// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterItems.h
//! @brief     Declares class FitParameterItems
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

class BA_CORE_API_ FitParameterContainerItem : public SessionItem
{

public:
    explicit FitParameterContainerItem();
};

class BA_CORE_API_ FitParameterItem : public SessionItem
{

public:
    static const QString P_USE;
    static const QString P_INIT;
    static const QString P_MIN;
    static const QString P_MAX;
    explicit FitParameterItem();
};


class BA_CORE_API_ FitParameterLinkItem : public SessionItem
{

public:
    static const QString P_LINK;
    explicit FitParameterLinkItem();
};

#endif

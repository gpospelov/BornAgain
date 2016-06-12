// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ObsoleteFitParameterItems.h
//! @brief     Declares class ObsoleteFitParameterItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#ifndef OBSOLETEFITPARAMETERITEMS_H
#define OBSOLETEFITPARAMETERITEMS_H

#include "SessionItem.h"

class BA_CORE_API_ ObsoleteFitParameterContainer : public SessionItem
{

public:
    explicit ObsoleteFitParameterContainer();
};

class BA_CORE_API_ ObsoleteFitParameterItem : public SessionItem
{

public:
    static const QString P_USE;
    static const QString P_INIT;
    static const QString P_MIN;
    static const QString P_MAX;
    explicit ObsoleteFitParameterItem();
};


class BA_CORE_API_ ObsoleteFitParameterLinkItem : public SessionItem
{

public:
    static const QString P_LINK;
    explicit ObsoleteFitParameterLinkItem();
};


class BA_CORE_API_ ObsoleteFitSelectionItem : public SessionItem
{

public:
    static const QString P_SAMPLE;
    static const QString P_INSTRUMENT;
    explicit ObsoleteFitSelectionItem();
};

class BA_CORE_API_ ObsoleteMinimizerSettingsItem : public SessionItem
{

public:
    static const QString P_ALGO;
    explicit ObsoleteMinimizerSettingsItem();
};

class BA_CORE_API_ ObsoleteInputDataItem : public SessionItem
{

public:
    static const QString P_PATH;
    explicit ObsoleteInputDataItem();
};

#endif

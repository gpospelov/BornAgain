// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/AxesItems.h
//! @brief     Defines various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef AXESITEMS_H
#define AXESITEMS_H

#include "ParameterizedItem.h"
#include "item_constants.h"

class BA_CORE_API_  BasicAxisItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_IS_VISIBLE;
    static const QString P_NBINS;
    static const QString P_MIN;
    static const QString P_MAX;
    static const QString P_TITLE;
    explicit BasicAxisItem(const QString &type=Constants::BasicAxisType, ParameterizedItem *parent=0);

    virtual ~BasicAxisItem(){}
protected:
    void register_basic_properties();
};

class BA_CORE_API_  AmplitudeAxisItem : public BasicAxisItem
{
    Q_OBJECT
public:
    static const QString P_IS_LOGSCALE;
    static const QString P_LOCK_MIN_MAX;
    explicit AmplitudeAxisItem(ParameterizedItem *parent=0);
    virtual ~AmplitudeAxisItem(){}
};

#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/AxesItems.h
//! @brief     Declares various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef AXESITEMS_H
#define AXESITEMS_H

#include "SessionItem.h"
#include "item_constants.h"

class BA_CORE_API_  BasicAxisItem : public SessionItem
{
public:
    static const QString P_IS_VISIBLE;
    static const QString P_NBINS;
    static const QString P_MIN;
    static const QString P_MAX;
    static const QString P_TITLE;
//    static const QString P_TITLE_IS_VISIBLE;
    explicit BasicAxisItem(const QString &type=Constants::BasicAxisType);

//    bool isAxisLabelVisible() const;

    virtual ~BasicAxisItem(){}
protected:
    void register_basic_properties();
};

class BA_CORE_API_  AmplitudeAxisItem : public BasicAxisItem
{
public:
    static const QString P_IS_LOGSCALE;
    static const QString P_LOCK_MIN_MAX;
    explicit AmplitudeAxisItem();
    virtual ~AmplitudeAxisItem(){}
};

#endif // AXESITEMS_H

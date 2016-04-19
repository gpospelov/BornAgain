// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RefractiveIndexItem.h
//! @brief     Declares class RefractiveIndexItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REFRACTIVEINDEXITEM_H
#define REFRACTIVEINDEXITEM_H

#include "SessionItem.h"

class BA_CORE_API_ RefractiveIndexItem : public SessionItem
{

public:
    static const QString P_DELTA;
    static const QString P_BETA;
    explicit RefractiveIndexItem();
    virtual ~RefractiveIndexItem(){}
    virtual QString itemLabel() const;

    double getDelta() const;
    void setDelta(double delta);

    double getBeta() const;
    void setBeta(double beta);
};

#endif

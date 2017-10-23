// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RefractiveIndexItem.h
//! @brief     Defines class RefractiveIndexItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALDATAITEM_H
#define MATERIALDATAITEM_H

#include "SessionItem.h"

class BA_CORE_API_ MaterialDataItem : public SessionItem
{

public:
    static const QString P_REAL;
    static const QString P_IMAG;
    explicit MaterialDataItem();
    virtual ~MaterialDataItem(){}
    virtual QString itemLabel() const;

    double getReal() const;
    void setReal(double real);

    double getImag() const;
    void setImag(double imag);
};

#endif // MATERIALDATAITEM_H

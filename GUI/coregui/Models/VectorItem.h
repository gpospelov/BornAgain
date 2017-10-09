// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/VectorItem.h
//! @brief     Defines class VectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef VECTORITEM_H
#define VECTORITEM_H

#include "SessionItem.h"
#include "Vectors3D.h"

class BA_CORE_API_  VectorItem : public SessionItem
{

public:
    static const QString P_X;
    static const QString P_Y;
    static const QString P_Z;
    VectorItem();
    virtual QString itemLabel() const;

    kvector_t getVector() const;
};

#endif // VECTORITEM_H


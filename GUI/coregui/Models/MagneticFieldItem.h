// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MagneticFieldItem.h
//! @brief     Defines class MagneticFieldItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MAGNETICFIELDITEM_H
#define MAGNETICFIELDITEM_H


#include "SessionItem.h"

class BA_CORE_API_ MagneticFieldItem : public SessionItem
{

public:
    static const QString P_BX;
    static const QString P_BY;
    static const QString P_BZ;
    explicit MagneticFieldItem();
    virtual ~MagneticFieldItem() {}
    virtual QString itemLabel() const;
};



#endif


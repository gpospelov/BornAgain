// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/VectorItem.h
//! @brief     Defines class VectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef VECTORITEM_H
#define VECTORITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_  VectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_X;
    static const QString P_Y;
    static const QString P_Z;
    explicit VectorItem(ParameterizedItem *parent=0);
    ~VectorItem(){}
    QString itemLabel() const;
};

#endif


// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformationItem.h
//! @brief     Defines class TransformationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMATIONITEM_H
#define TRANSFORMATIONITEM_H

#include "SessionGraphicsItem.h"
#include <QVector>

class TransformationItem : public SessionGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_ROT;
    explicit TransformationItem();
    virtual ~TransformationItem(){}
};


#endif // TRANSFORMATIONITEM_H


// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/CylinderItem.h
//! @brief     Defines class CylinderItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CYLINDERITEM_H
#define CYLINDERITEM_H

#include "ParameterizedItem.h"

class CylinderItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit CylinderItem(ParameterizedItem *parent=0);
    ~CylinderItem();
};

#endif // CYLINDERITEM_H


// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/FormFactorItems.h
//! @brief     Defines FormFactorItem classes.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORITEMS_H
#define FORMFACTORITEMS_H

#include "ParameterizedItem.h"

class CylinderItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit CylinderItem(ParameterizedItem *parent=0);
    ~CylinderItem();
};

class FullSphereItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit FullSphereItem(ParameterizedItem *parent=0);
    ~FullSphereItem();
};

#endif // FORMFACTORITEMS_H


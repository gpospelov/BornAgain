// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SphericalDetectorItem.h
//! @brief     Defines class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTORITEM_H
#define SPHERICALDETECTORITEM_H

#include "ParameterizedItem.h"

class SphericalDetectorItem : public ParameterizedItem
{
public:
    static const QString P_PHI_AXIS;
    static const QString P_ALPHA_AXIS;
    static const QString P_RESOLUTION_FUNCTION;
    explicit SphericalDetectorItem(ParameterizedItem *parent=0);
};

#endif

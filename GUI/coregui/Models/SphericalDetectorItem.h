// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SphericalDetectorItem.h
//! @brief     Defines class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTORITEM_H
#define SPHERICALDETECTORITEM_H

#include "DetectorItems.h"

class BA_CORE_API_ SphericalDetectorItem : public DetectorItem
{
public:
    static const QString P_PHI_AXIS;
    static const QString P_ALPHA_AXIS;
    static const QString P_RESOLUTION_FUNCTION;
    SphericalDetectorItem();

    std::unique_ptr<IDetector2D> createDetector() const;
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction();
};

#endif // SPHERICALDETECTORITEM_H

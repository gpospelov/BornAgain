// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RectangularDetectorItem.h
//! @brief     Defines class RectangularDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTORITEM_H
#define RECTANGULARDETECTORITEM_H

#include "SessionItem.h"
#include "Vectors3D.h"

class IDetector2D;
class IResolutionFunction2D;


class BA_CORE_API_ RectangularDetectorItem : public SessionItem
{
public:
    static const QString P_X_AXIS;
    static const QString P_Y_AXIS;
    static const QString P_RESOLUTION_FUNCTION;
    static const QString P_ALIGNMENT;
    static const QString P_NORMAL;
    static const QString P_DIRECTION;
    static const QString P_U0;
    static const QString P_V0;
    static const QString P_DBEAM_U0;
    static const QString P_DBEAM_V0;
    static const QString P_DISTANCE;

    explicit RectangularDetectorItem();

    std::unique_ptr<IDetector2D> createDetector() const;
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction();

    void setDetectorAlignment(const QString &alignment);

private:
    void update_properties_appearance();

    kvector_t getNormalVector() const;
    kvector_t getDirectionVector() const;

    bool m_is_constructed;
};

#endif // RECTANGULARDETECTORITEM_H

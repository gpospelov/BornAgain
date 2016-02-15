// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RectangularDetectorItem.h
//! @brief     Defines class RectangularDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTORITEM_H
#define RECTANGULARDETECTORITEM_H

#include "ParameterizedItem.h"
#include "Types.h"
#include <memory>

class IDetector2D;
class IResolutionFunction2D;


class RectangularDetectorItem : public ParameterizedItem
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

    explicit RectangularDetectorItem(ParameterizedItem *parent=0);

    virtual void onPropertyChange(const QString &name);

    std::unique_ptr<IDetector2D> createDetector() const;
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction();

    void setDetectorAlignment(const QString &alignment);

private:
    void update_properties_appearance();

    kvector_t getNormalVector() const;
    kvector_t getDirectionVector() const;

    bool m_is_constructed;
};

#endif

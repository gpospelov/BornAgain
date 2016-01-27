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

class RectangularDetectorItem : public ParameterizedItem
{
public:
    static const QString P_X_AXIS;
    static const QString P_Y_AXIS;
    static const QString P_RESOLUTION_FUNCTION;
    static const QString P_ALIGNMENT;
    static const QString P_NORMAL;
    static const QString P_DIRECTION;
    static const QString P_UV;
    static const QString P_UV_DPOS;
    static const QString P_DISTANCE;

    explicit RectangularDetectorItem(ParameterizedItem *parent=0);

    virtual void onPropertyChange(const QString &name);

private:
    void update_properties_appearance();
    bool m_is_constructed;
};

#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapBin.h
//! @brief     Declares class ColorMapBin
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPBIN_H
#define COLORMAPBIN_H

#include <QString>
#include "WinDllMacros.h"

//! The ColorMapBin class contains parameters of intensity data bin under current mouse position.

class BA_CORE_API_ ColorMapBin {
public:
    ColorMapBin()
        : in_axes_range(false), m_nx(0), m_ny(0), m_x(0), m_y(0), m_value(0) {}

    void reset() {
        in_axes_range = false;
        m_nx = m_ny = 0;
        m_x = m_y = m_value = 0.0;
    }

    QString statusString() {
        QString result = QString(" [x: %1, y: %2]    [binx: %3, biny:%4]    [value: %5]")
                     .arg(QString::number(m_x, 'f', 4))
                     .arg(QString::number(m_y, 'f', 4), 2)
                     .arg(m_nx, 2)
                     .arg(m_ny, 2)
                     .arg(QString::number(m_value, 'f', 2));

        return result;
    }

    bool inAxesRange() const { return in_axes_range; }

    bool in_axes_range;
    int m_nx, m_ny;
    double m_x, m_y, m_value;
};

#endif // COLORMAPBIN_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/Ellipse.h
//! @brief     Declares class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "IShape2D.h"

namespace Geometry {


//! @class Ellipse
//! @ingroup tools
//! @brief Ellipse shape

class  BA_CORE_API_ Ellipse : public IShape2D {
public:
    //! Ellipse constructor
    //! @param xcenter x-coordinate of Ellipse's center
    //! @param ycenter y-coordinate of Ellipse's center
    //! @param xradius Radius along x-axis
    //! @param yradius Radius along y-axis
    //! @param theta Angle of Ellipse rotation in radians
    Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta = 0.0);

    Ellipse *clone() const;

    //! Returns true if given point is inside or on border of ellipse
    bool contains(double x, double y) const;

    //! Returns true if area defined by two bins is inside or on border of ellipse.
    //! More precisely, if mid point of two bins satisfy this condition.
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

    double getCenterX() const;
    double getCenterY() const;
    double getRadiusX() const;
    double getRadiusY() const;
    double getTheta() const;

private:
    Ellipse(const Ellipse& other);
    double m_xc, m_yc, m_xr, m_yr, m_theta;
};

} // namespace Geometry

#endif // ELLIPSE_H

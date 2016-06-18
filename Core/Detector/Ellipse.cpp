// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/Ellipse.cpp
//! @brief     Implements class Ellipse.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Bin.h"
#include "Ellipse.h"

namespace Geometry {

Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta)
    : m_xc(xcenter)
    , m_yc(ycenter)
    , m_xr(xradius)
    , m_yr(yradius)
    , m_theta(theta)
{
    if(xradius <= 0.0 || yradius <= 0.0) {
        std::ostringstream message;
        message <<
            "Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius) "
            "-> Error. Radius can't be negative\n";
        throw Exceptions::LogicErrorException(message.str());
    }
}

Ellipse *Ellipse::clone() const
{
    return new Ellipse(*this);
}

bool Ellipse::contains(double x, double y) const
{
    double u = std::cos(m_theta)*(x-m_xc) + std::sin(m_theta)*(y-m_yc);
    double v = -std::sin(m_theta)*(x-m_xc) + std::cos(m_theta)*(y-m_yc);
    double d = (u/m_xr)*(u/m_xr) + (v/m_yr)*(v/m_yr);
    return (d<=1 ? true : false);
}

bool Ellipse::contains(const Bin1D &binx, const Bin1D &biny) const
{
    return contains(binx.getMidPoint(), biny.getMidPoint());
}

double Ellipse::getCenterX() const
{
    return m_xc;
}

double Ellipse::getCenterY() const
{
    return m_yc;
}

double Ellipse::getRadiusX() const
{
    return m_xr;
}

double Ellipse::getRadiusY() const
{
    return m_yr;
}

double Ellipse::getTheta() const
{
    return m_theta;
}

Ellipse::Ellipse(const Ellipse &other)
    : m_xc(other.m_xc)
    , m_yc(other.m_yc)
    , m_xr(other.m_xr)
    , m_yr(other.m_yr)
    , m_theta(other.m_theta)
{
}

} // namespace Geometry

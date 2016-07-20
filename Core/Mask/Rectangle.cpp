// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Rectangle.cpp
//! @brief     Implements class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Rectangle.h"
#include "Bin.h"

namespace Geometry {

Rectangle::Rectangle(double xlow, double ylow, double xup, double yup)
{
    if(xup <= xlow) {
        std::ostringstream message;
        message << "Rectangle(double xlow, double ylow, double xup, double yup) -> Error. ";
        message << " xup <= xlow" << std::endl;
        throw Exceptions::LogicErrorException(message.str());
    }
    if(yup <= ylow) {
        std::ostringstream message;
        message << "Rectangle(double xlow, double ylow, double xup, double yup) -> Error. ";
        message << " yup <= ylow" << std::endl;
        throw Exceptions::LogicErrorException(message.str());
    }
    m_xlow = xlow;
    m_ylow = ylow;
    m_xup = xup;
    m_yup = yup;
}

Rectangle *Rectangle::clone() const
{
    return new Rectangle(*this);
}

bool Rectangle::contains(double x, double y) const
{
    if(x <= m_xup && x >= m_xlow && y <= m_yup && y >= m_ylow) return true;
    return false;
}

bool Rectangle::contains(const Bin1D &binx, const Bin1D &biny) const
{
    return contains(binx.getMidPoint(), biny.getMidPoint());
}

double Rectangle::getArea() const
{
    return (m_xup-m_xlow)*(m_yup-m_ylow);
}

double Rectangle::getXlow() const
{
    return m_xlow;
}

double Rectangle::getYlow() const
{
    return m_ylow;
}

double Rectangle::getXup() const
{
    return m_xup;
}

double Rectangle::getYup() const
{
    return m_yup;
}

Rectangle::Rectangle(const Rectangle &other)
    : m_xlow(other.m_xlow)
    , m_ylow(other.m_ylow)
    , m_xup(other.m_xup)
    , m_yup(other.m_yup)
{

}

} // namespace Geometry

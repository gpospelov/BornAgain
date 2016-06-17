// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Geometry/Line.h
//! @brief     Declares class Line.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LINE_H
#define LINE_H

#include "IShape2D.h"

namespace Geometry {


//! @class Line
//! @ingroup tools
//! @brief The line segment

class  BA_CORE_API_ Line : public IShape2D {
public:
    //! Line segment constructor
    Line(double x1, double y1, double x2, double y2);

    Line *clone() const;

    //! Returns true if given point is on this line segment
    bool contains(double x, double y) const;

    //! Returns true if the line crosses the area defined by two given bins
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

private:
    Line(const Line& other);
    double m_x1, m_y1, m_x2, m_y2;
};

//! @class VerticalLine
//! @ingroup tools
//! @brief Vertical infinite line

class BA_CORE_API_ VerticalLine : public IShape2D {
public:
    //! Infinite vertical line constructor
    //! @param x The value at which it crosses x-axes
    VerticalLine(double x);

    VerticalLine *clone() const;

    //! Returns true if given point is on this line segment (y is unused)
    bool contains(double x, double y) const;

    //! Returns true if the line crosses the area defined by two given bins
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

    double getXpos() const;

private:
    VerticalLine(const VerticalLine& other);
    double m_x;
};

//! @class HorizontalLine
//! @ingroup tools
//! @brief Horizontal infinite line

class BA_CORE_API_ HorizontalLine : public IShape2D {
public:
    //! Infinite vertical line constructor
    //! @param y The value at which it crosses y-axes
    HorizontalLine(double y);

    HorizontalLine *clone() const;

    //! Returns true if given point is on this line segment
    bool contains(double x, double y) const;

    //! Returns true if the line crosses the area defined by two given bins
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

    double getYpos() const;

private:
    HorizontalLine(const HorizontalLine& other);
    double m_y;
};


} // namespace Geometry

#endif // LINE_H
